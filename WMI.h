//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: WMI Class Header

//****************************************************************************************

#define _WIN32_DCOM //"Virtual Server" COM
#include <comdef.h>//library to define _bstr_t
#include <Wbemidl.h>//WMI lib


#include "List.h"
# pragma comment(lib, "wbemuuid.lib")//include wbemuuid.lib
#include <vcclr.h>//clr lib
#include <msclr/gcroot.h> // required for gcroot
#include "string.h"//string library
using namespace System::Windows;

//forward class and struct definitions
value struct _userInfo;
ref class _userInfoInterface;





// ----------------------------------------------------------------
//  Name:           WMI
//	Class:			WMI
//  Description:    class to set up the WMI connection and query information from the service
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WMI
{
	//methods
	public:
		WMI();//constructor
		~WMI();//destructor
		bool Select(char* sql,char* sqlComm);//select function to query data from WMI
		bool initCOM();//initializes COM thread
		bool initCOMSecurity();//sets the default security attributes
		bool initWMILocator();//get the pointer to the WMI namespace
		bool connectWMI();//connect DCOM to the WMI namespace
		bool setProxySecurity();//sets authentication for connection
		IWbemServices *getProxyService();//get the WMI interface
		IEnumWbemClassObject* recieveEnumerator();//get WMI ennumerator
		void setEnumerator(IEnumWbemClassObject* input);//set WMI ennumerator
		IWbemLocator *getLocator();//get WMI namespace pointer
		void setLocator(IWbemLocator* input);//set WMI namespace pointer
		gcroot<MyList<_userInfo>^> getList();//get the managed list
		char* WMI::extractHostNames(char* input,char* type);//extracts the domain and username
		bool clearList();

	//attributes
	public:
		IWbemLocator *_WMILocator;//WMI namespace pointer
		IWbemServices *_ProxyService;//WMI interface
		IEnumWbemClassObject* _Enumerator;//WMI ennumerator
		IWbemClassObject *pclsObj;//WMI interface
		HRESULT result;//result variable for capturing errors
		gcroot<MyList<_userInfo>^> int_list;//managed list.
		gcroot<_userInfoInterface^> _UII;//managed userinfo struct object
		int size;//size of list
		
		
};






