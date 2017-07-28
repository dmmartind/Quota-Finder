//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: XML Class Header 

//****************************************************************************************

#include "WMI.h"
#include "User.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Xml::Serialization;

// ----------------------------------------------------------------
//  Name:           xmlFormat
//	Class:			xmlFormat
//  Description:    class to create instance for holding WMI data
//  Arguments:      None.
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class xmlFormat//xml format object
{
public:
    Decimal UserNumber;
	String^ UserName;
	String^ Domain;
	String^ DiskSpaceUsed;
	String^ DiskSpaceLimit;
	String^ QuotaVolume;
	String^ Status;
	String^ WarningLimit;


};

// ----------------------------------------------------------------
//  Name:           xmlObject
//	Class:			xmlObjectt
//  Description:    class to send the xml data to the serializer
//  Arguments:      None.
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class xmlObject//xml format object
	{
	public:
		array<xmlFormat^>^xmlArray;//array to dump the main list to
	};


// ----------------------------------------------------------------
//  Name:           _XMLFactory
//	Class:			_XMLFactory
//  Description:    class to create an XML file with the WMI data 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

public ref class _XMLFactory//creates the XML file
{	
public:
	_XMLFactory();//constructor
	~_XMLFactory();//destructor
	bool output(String^ file_name,MyList<_userInfo>^ list);//output all to an xml file
//output all to an xml file
	bool output(int input, String^ file_name,MyList<_userInfo>^ list);//output the currently selected user
	// Return an XmlSerializer used for overriding. 
	
	
};
