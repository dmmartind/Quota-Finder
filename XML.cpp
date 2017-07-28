//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: XML Class Code 

//****************************************************************************************

#include "stdafx.h"
#include "XML.h"
using namespace System::Windows::Forms;

// ----------------------------------------------------------------
//  Name:           xmlOverRide
//	Class:			NONE
//  Description:    override XmlSerializer
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
XmlSerializer^ xmlOverRide()
{
	try
	{
   // Creating XmlAttributeOverrides and XmlAttributes objects.
   XmlAttributeOverrides^ xOver = gcnew XmlAttributeOverrides; //override object
   XmlAttributes^ xAttrs = gcnew XmlAttributes;//attribute object

   // Add an override for the XmlArray.    
   XmlArrayAttribute^ xArray = gcnew XmlArrayAttribute( "User" );
   xArray->Namespace = "http://";//set up namespace
   xAttrs->XmlArray = xArray;//set the array attributes to the attributes object
   xOver->Add( xmlObject::typeid, "User", xAttrs );//add attributes object to the override object
   return gcnew XmlSerializer( xmlObject::typeid,xOver );//return override object 
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return nullptr;
	}
}


// ----------------------------------------------------------------
//  Name:           _XMLFactory
//	Class:			_XMLFactory
//  Description:    constructor
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

_XMLFactory::_XMLFactory()//constructor
	{
		
			
	}

// ----------------------------------------------------------------
//  Name:           _XMLFactory
//	Class:			_XMLFactory
//  Description:    deconstructor 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

_XMLFactory::~_XMLFactory()//destructor
	{
		

	}

// ----------------------------------------------------------------
//  Name:           output
//	Class:			_XMLFactory
//  Description:    creates an XML file from all the user's WMI data 
//  Arguments:      NONE
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool _XMLFactory::output(String^ file_name,MyList<_userInfo>^ list)//output all to an xml file
	  {
		  int counter=0;//list counter		
		  try
		  {
			  XmlSerializer^ mySerializer = xmlOverRide();//create an xml serializer with the override as the constructor
			  TextWriter^ writer = gcnew StreamWriter( file_name );//create text writer and open xml file
		      xmlObject^ xmlObj = gcnew xmlObject;//create xml class object
		      xmlFormat^ UI = gcnew xmlFormat();//set the xml class that holds the data to be serialized
		      xmlObj->xmlArray = gcnew array<xmlFormat^>(list->getListCounter() + 1);//set xml array to object
		  
		  
		  
		  
			  //create a new instance of the array inside the xml class with the array size the same as the list + 1
   
				for each (ListNode<_userInfo>^ node in (MyList<_userInfo>^)list)//iterate through the list
				{
					//fill data into the xml data class
					UI->DiskSpaceLimit= node->item._diskSpaceLimit;
					UI->DiskSpaceUsed = node->item._diskSpaceUsed;
					UI->Domain = node->item._domain;
					UI->QuotaVolume = node->item._QuotaVolume;
					UI->Status = node->item._status;
					UI->UserName = node->item._username;
					UI->UserNumber = node->item._userNum;
					UI->WarningLimit = node->item._warningLimit;
					xmlObj->xmlArray[counter] = UI;///add the data to the array
					UI = nullptr;//set the xml data object to null to detach from the original address
					UI = gcnew xmlFormat;//create new xml data object

					
			
			counter++;//increment the counter

				}
		  

  
   mySerializer->Serialize( writer, xmlObj );//send the xml class to the serializer
   writer->Close();//close file
		  }
		  catch(FormatException^ e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
				return false;
			}
		
		  return true;
		
      }

// ----------------------------------------------------------------
//  Name:           output
//	Class:			_XMLFactory
//  Description:    writing a single record to an XML file 
//  Arguments:      user number, file name
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool _XMLFactory::output(int input, String^ file_name,MyList<_userInfo>^ list)//output the currently selected user
	  {
   try
   {
	int counter=0;//list counter
	XmlSerializer^ mySerializer = xmlOverRide();//create instance of the xml serializer with the xml override function as the constructor
	TextWriter^ writer = gcnew StreamWriter( file_name );//create stream writer
	xmlObject^ xmlObj = gcnew xmlObject;//create xml class object to be serialized
	xmlFormat^ UI = gcnew xmlFormat();//xml data object
	xmlObj->xmlArray = gcnew array<xmlFormat^>(1);//create instance of xml array with the size of 1
    
		for each (ListNode<_userInfo>^ node in (MyList<_userInfo>^)list)//iterate through the list
		{
			if(counter == input)//if the counter matches the selected index
			{
				//fill data into the xml data object from each list node
				UI->DiskSpaceLimit= node->item._diskSpaceLimit;
				UI->DiskSpaceUsed = node->item._diskSpaceUsed;
				UI->Domain = node->item._domain;
				UI->QuotaVolume = node->item._QuotaVolume;
				UI->Status = node->item._status;
				UI->UserName = node->item._username;
				UI->UserNumber = node->item._userNum;
				UI->WarningLimit = node->item._warningLimit;
				xmlObj->xmlArray[0] = UI;//set the xml data from each node of the list to each index of the array
				UI = nullptr;//set the xml data object to null to detach from the original address
				UI = gcnew xmlFormat;//create new xml data object
			}
				counter++;//increment the counter


		}

  
   mySerializer->Serialize( writer, xmlObj );//send the xml class to the serializer
   writer->Close();//close file
   }
   catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return false;
    }
   return true;
}
