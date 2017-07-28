//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: WMI Class Code 

//****************************************************************************************

#include "stdafx.h"//empty file include
#include "WMI.h"//
#include "User.h"
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;


// ----------------------------------------------------------------
//  Name:           WMI
//	Class:			WMI
//  Description:    Constructor
//  Arguments:      None.
//  Return Value:   VOID.
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
WMI::WMI()
{
	try
	{
		_WMILocator = NULL;
		_ProxyService = NULL;
		result = NULL;
		initCOM();
		initCOMSecurity();
		initWMILocator();
		connectWMI();
		setProxySecurity();
		_Enumerator=NULL;
		pclsObj=NULL;
		int_list = gcnew MyList<_userInfo>();
		size = 0;
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
	}
	
}





// ----------------------------------------------------------------
//  Name:           ~WMI
//	Class:			WMI
//  Description:    Deonstructor
//  Arguments:      None.
//  Return Value:   VOID.
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

WMI::~WMI()
{

	try
	{
		if(_ProxyService)
			_ProxyService->Release();
		if(_WMILocator)
			_WMILocator->Release();
		if(_Enumerator)
			_Enumerator->Release();
		if(pclsObj)
			pclsObj->Release();
		CoUninitialize();
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
	MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
	}
}

// ----------------------------------------------------------------
//  Name:           Select
//	Class:			WMI
//  Description:    query on the WMI object using the arguments supplied
//  Arguments:      query type,query.
//  Return Value:   VOID.
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::Select(char* sql,char* sqlComm)
{
	try
	{
		HRESULT hres;//result var
		setEnumerator(NULL);//set the enumerator var to null
		IEnumWbemClassObject* tempEnumerator = NULL;//temp enumerator
		tempEnumerator=recieveEnumerator();//set the temporary enumerator to the current
		String^ temp_sql = gcnew String(sql,0,strlen(sql));//convert char to managed string
		String^ temp_sqlComm = gcnew String(sqlComm,0,strlen(sqlComm));//convert to managed string
		IntPtr  t_sql=Marshal::StringToBSTR(temp_sql);//convert from managed string to managed pointer
		IntPtr  t_sqlComm=Marshal::StringToBSTR(temp_sqlComm);//convert from managed string to managed pointer
		BSTR _sql = static_cast<BSTR>(t_sql.ToPointer());//convert from managed pointer to BSTR
		BSTR _sqlComm = static_cast<BSTR>(t_sqlComm.ToPointer());//convert from managed pointer to BSTR
	
		hres = getProxyService()->ExecQuery(//execute query on WMI
				_sql, //sql type
				_sqlComm,//query command
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, //return forward enumerator immediately
				NULL,&tempEnumerator);//return to temp var

		

				if (FAILED(hres))//if query failed
				{
					MessageBox::Show("Query for operating system name failed.","ERROR",Forms::MessageBoxButtons::OK);
					getProxyService()->Release();
					getLocator()->Release();
					CoUninitialize();
					return false;            // function has failed.
				}
	
		setEnumerator(tempEnumerator);//set the enumerator returned
		ULONG uReturn = 0;//set the var for holding whether nor not enumerator is returned
		int user_counter = 0;//set the user counter var to 0
		VARIANT vtProp;//variant struct for capturing enumerator data
	

		while (recieveEnumerator())//while current node is not null
		{
			
				HRESULT hr = recieveEnumerator()->Next(WBEM_INFINITE, 1, 
					&pclsObj, &uReturn);//get net node from the enumerator

					if(0 == uReturn)//if the no node is available
					{
						break;
					}
			

			_UII= gcnew _userInfoInterface(); //create a new user_info struct interface class

			VariantClear(&vtProp);//clear the struct object
			// Get the value of the Name property
			_UII->setUserNum(user_counter);//set the user number
			VariantClear(&vtProp);//clear the struct object
			hr = pclsObj->Get(L"DiskSpaceUsed", 0, &vtProp, 0, 0);//get disk space used
			_UII->setDiskSpaceUsed(vtProp.bstrVal);//set disk space used
			VariantClear(&vtProp);//clear the struct object
			hr = pclsObj->Get(L"Limit", 0, &vtProp, 0, 0);//get disk space limit
			_UII->setDiskSpaceLimit(vtProp.bstrVal);//set disk space limit
			VariantClear(&vtProp);//clear the struct object
			hr = pclsObj->Get(L"QuotaVolume", 0, &vtProp, 0, 0);//get the quota volume
			_UII->setQuotaVolume(vtProp.bstrVal);//set the quota volume
			VariantClear(&vtProp);//clear the struct object
			hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);//get the status
			
			if((vtProp.boolVal) == 0)//if the status is 0
				_UII->setStatus("OK");//the status is OK
			else if((vtProp.boolVal) == 1)//if the status is 1
				_UII->setStatus("Warning");//the status is warning
			else if((vtProp.boolVal) == 2)//if the status is 2
				_UII->setStatus("Exceeded");//the status is exceeded
		
		VariantClear(&vtProp);//clear the struct object
		hr = pclsObj->Get(L"WarningLimit", 0, &vtProp, 0, 0);//get warning limit
		_UII->setWarningLimit(vtProp.bstrVal);//set warning limit
		VariantClear(&vtProp);//clear the struct object
		hr = pclsObj->Get(L"User", 0, &vtProp, 0, 0);//get user data
		////////////////////////////////////////////////////
		LPCTSTR userLP= (LPCTSTR)vtProp.bstrVal;//cast it to a long pointer string
		char* hostNP=(char*)malloc(sizeof(char*)*255);//create host buffer
		sprintf_s(hostNP,255,"%S",userLP);//print to host buffer
		char* _domain=extractHostNames(hostNP,"domain");//extract host name
		char* _user_name=extractHostNames(hostNP,"username");//extract username
		String^ _user_nametemp= gcnew String(_user_name,0,strlen(_user_name));
		String^ _domainTemp = gcnew String(_domain,0,strlen(_domain));
		_UII->setUserID(_user_nametemp);//set the user name from the extraction
		_UII->setDomain(_domainTemp);//set he host name from the extraction
		VariantClear(&vtProp);//clear the struct object
		
			if(!int_list->Add(_UII->getStruct()))//add struct to the node
				return false;
			user_counter++;//increment user counter
		
		///////////////////Memory Cleanup////////////////////////////
		
			free(hostNP);//free up buffer
			free(_user_name);
			free(_domain);
			_UII=nullptr;
			_domain = NULL;
			_user_name = NULL;
		
		
		
		////////////////////Memory Cleanup///////////////////////////
		}
		
  

	size = user_counter;//set the size
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
	}
	return true;
}

// ----------------------------------------------------------------
//  Name:           initCOM
//	Class:			WMI
//  Description:    Initializes the COM library
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::initCOM()
{
	try
	{

	result =  CoInitializeEx(0, COINIT_MULTITHREADED); //Initializes the COM library 
    
	if(result == S_FALSE)
	{
		MessageBox::Show("instance already initialized","Warning",Forms::MessageBoxButtons::OK);
	}
	else if((result != S_OK) && (result != RPC_E_CHANGED_MODE))
	{
		MessageBox::Show("Failed to initialize COM library.","Error",Forms::MessageBoxButtons::OK);
		return false;                  // Program has failed.
	}
	return true;
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
	}

}

// ----------------------------------------------------------------
//  Name:           initCOMSecurity
//	Class:			WMI
//  Description:    Registers security and sets the default security attributes
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::initCOMSecurity()
{ 
	try
	{
		result =  CoInitializeSecurity(//Registers security and sets the default security values 
			NULL, 
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
        );

	
		
		if(result == RPC_E_NO_GOOD_SECURITY_PACKAGES)
			MessageBox::Show("Security packages could not be registered","ERROR",Forms::MessageBoxButtons::OK);
		else if((result != S_OK) && (result != RPC_E_TOO_LATE))//if failed
		{
			MessageBox::Show("Failed to initialize security.","ERROR",Forms::MessageBoxButtons::OK);
			CoUninitialize();
			return false;                    // Program has failed.
		}

	return true;//success
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
	}
	
}

// ----------------------------------------------------------------
//  Name:           initWMILocator
//	Class:			WMI
//  Description:    Creates a single uninitialized object 
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::initWMILocator()
{
    try
	{
		result = CoCreateInstance(//Creates a single uninitialized object of the class associated with a specified CLSID
			CLSID_WbemLocator, //COM identifier            
			0, //not part of an aggregate
			CLSCTX_INPROC_SERVER, //load on separate process
			IID_IWbemLocator, (LPVOID *) &_WMILocator);//class and result pointer
 
		if (FAILED(result))//if failed
		{
			MessageBox::Show("Failed to create IWbemLocator object.","ERROR",Forms::MessageBoxButtons::OK);
			CoUninitialize();//kill COM
			return false;                 // Program has failed.
		}
	
	
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
	}

	return true;//success
}



// ----------------------------------------------------------------
//  Name:           connectWMI
//	Class:			WMI
//  Description:    creates connection through DCOM to a WMI namespace 
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::connectWMI()
{

	try
	{
			result = _WMILocator->ConnectServer(
				_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
				NULL,                    // User name. NULL = current user
				NULL,                    // User password. NULL = current
				0,                       // Locale. NULL indicates current
				NULL,                    // Security flags.
				0,                       // Authority (e.g. Kerberos)
				0,                       // Context object 
				&_ProxyService           // pointer to IWbemServices proxy
				);
    
			if (FAILED(result))//if failed
			{
				MessageBox::Show("Could not connect.","ERROR",Forms::MessageBoxButtons::OK);
				if(_WMILocator != NULL)
				_WMILocator->Release(); //release result pointer    
				CoUninitialize();			//kill COM
				return false;                // Program has failed.
			}
	
	
	

	}
		catch (Exception ^e)//catch unforeseen error and display error
		{
			MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
			return false;
		}	
		return true;//success

}


// ----------------------------------------------------------------
//  Name:           setProxySecurity
//	Class:			WMI
//  Description:    Sets the authentication information on a specified proxy 
//  Arguments:      NONE
//  Return Value:   int
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::setProxySecurity()
{
	try
	{
		result = CoSetProxyBlanket(
		_ProxyService,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
       RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
       NULL,                        // Server principal name 
       RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
       RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
       NULL,                        // client identity
       EOAC_NONE                    // proxy capabilities 
		);

    if (FAILED(result))//if failed
    {
		MessageBox::Show("Could not set WMI proxy.","ERROR",Forms::MessageBoxButtons::OK);
        if(_ProxyService != NULL)//if proxy is not NULL
			_ProxyService->Release();//release proxy
        if(_WMILocator != NULL)//if result pointer is not NULL
			_WMILocator->Release(); //release    
        CoUninitialize();//kill COM
        return false;               // Program has failed.
    }

	
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
	}
	return true;//success
}

// ----------------------------------------------------------------
//  Name:           getProxyService
//	Class:			WMI
//  Description:    get WMI interface  
//  Arguments:      NONE
//  Return Value:   IWbemServices
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////


IWbemServices *WMI::getProxyService()
{
	return _ProxyService;
}

// ----------------------------------------------------------------
//  Name:           extractHostNames
//	Class:			WMI
//  Description:    get host name or user name based on arguments supplied  
//  Arguments:      buffer,type either "username" or "hostname"
//  Return Value:   char*
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* WMI::extractHostNames(char* input,char* type)
{
	try
	{
		if((strcmp(type,"domain")) == 0)//if the domain is needed
			{
				char* domainFirstPTR=strchr(input,'=');//move the pointer to after the first equal sign and return it
				domainFirstPTR=strchr(domainFirstPTR+1,'"');//move the pointer to after the first quote and return it
				char* domainLastPtr=strchr(domainFirstPTR+1,'"');//move the pointer to the last quote
				char domainOut[255] = {0};//create a output character array
				strncat_s(domainOut,255,domainFirstPTR+1,(domainLastPtr-1)-domainFirstPTR);//copy the portion from the first pointer to the last pointer and return it to the array
				char* return_domain=(char*)malloc(strlen(domainOut)+1);//create an character string with the size of the array
				strcpy_s(return_domain,strlen(domainOut)+1,domainOut);//copy character array to string
				/////////////////Memory Cleanup////////////////////////////////////
				domainFirstPTR=NULL;
				domainLastPtr=NULL;
				/////////////////Memory Cleanup///////////////////////////////////

				return return_domain;//return character string
			}
	
		if((strcmp(type,"username"))== 0)//if username is needed
			{
				char* userFirstPTR=strchr(input,'=');//move the pointer to after the first equal sign and return
				userFirstPTR=strchr(userFirstPTR+2,'=');//move the pointer to the next equal sign and return
				userFirstPTR= strchr(userFirstPTR+1,'"');//move pointer to the first found quote and return
				char* userLastPTR= strrchr(userFirstPTR,'"');//move the pointer to the last quote and return
				char userOut[255] = {0};//character array
				//copy string form the first pointer to the last pointer and return it to the character array
				strncat_s(userOut,255,userFirstPTR+1,(userLastPTR-1)-userFirstPTR);
				char* return_user=(char*)malloc(strlen(userOut)+1);//create character pointer
				strcpy_s(return_user,strlen(userOut)+1,userOut);//copy character array to the string pointer

			/////////////////Memory Cleanup////////////////////////////////////
			userFirstPTR=NULL;
			userLastPTR=NULL;
			/////////////////Memory Cleanup///////////////////////////////////
				return return_user;//return string

			}

	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return NULL;
	}
		return NULL;
	
}



// ----------------------------------------------------------------
//  Name:           recieveEnumerator
//	Class:			WMI
//  Description:    get enumerator interface
//  Arguments:      None
//  Return Value:   IEnumWbemClassObject*
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

IEnumWbemClassObject *WMI::recieveEnumerator()
{
	try
	{
	if(!_Enumerator != 0x0)//if the enumerator is not valid
		return NULL;//return null for fail
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
	}

	return _Enumerator;
	}


// ----------------------------------------------------------------
//  Name:           setEnumerator
//	Class:			WMI
//  Description:    set enumerator interface
//  Arguments:      IEnumWbemClassObject*
//  Return Value:   void
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WMI::setEnumerator(IEnumWbemClassObject* input)
{
	_Enumerator=input;
}

// ----------------------------------------------------------------
//  Name:           getLocator
//	Class:			WMI
//  Description:    get the WMI namespace pointer
//  Arguments:      None
//  Return Value:   IWbemLocator*
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
IWbemLocator* WMI::getLocator()
{
	return _WMILocator;
}

// ----------------------------------------------------------------
//  Name:           getLocator
//	Class:			WMI
//  Description:    set the WMI namespace pointer
//  Arguments:      IWbemLocator*
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WMI::setLocator(IWbemLocator* input)
{
	_WMILocator = input;
}


// ----------------------------------------------------------------
//  Name:           getList
//	Class:			WMI
//  Description:    get managed list
//  Arguments:      None
//  Return Value:   gcroot<MyList<_userInfo>^> 
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

gcroot<MyList<_userInfo>^> WMI::getList()
{
	return int_list;
}

// ----------------------------------------------------------------
//  Name:           clearList
//	Class:			WMI
//  Description:    clear the WMI list
//  Arguments:      None
//  Return Value:   bool 
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WMI::clearList()
	{
		try
		{
		if(!int_list->RemoveAll())//remove all the nodes
			return false;			
		}
		catch (Exception ^e)//catch unforeseen error and display error
		{
			MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		}
		return true;
	}

