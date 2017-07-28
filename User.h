//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: UserInfo Class Header

//****************************************************************************************

#include "stdafx.h"
#include "WTypes.h"
#include "OLEAuto.h"
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows;




// ----------------------------------------------------------------
//  Name:           _userInfo
//	Structure:		_userInfo
//  Description:    structure to hold WMI data 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

public value struct _userInfo//managed user info struct
{

	int _userNum;//user number
	String^ _username;//user name
	String^ _domain;//host name
	String^ _diskSpaceUsed;//disk spaced used
	String^ _diskSpaceLimit;//size limit set for the user
	String^ _QuotaVolume;//volume drive letter
	String^  _status;//status of the user
	String^ _warningLimit;//size limit set where the user will receive a size warning
};


// ----------------------------------------------------------------
//  Name:         _userInfoInterface
//	Class:		  _userInfoInterface
//  Description:    interface to the _userinfo struct 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

public ref class _userInfoInterface//interface class to access the userinfo struct
{
	public:
		_userInfoInterface();//constructor
		~_userInfoInterface();//deconstructor
		void clear();
		void setUserNum(int input);//set the user number
		void setUserID(String^ input);//set the username
		void setDomain(String^ input);//set the hostname
		void setDiskSpaceUsed(BSTR input);//set the disk space used
		void setDiskSpaceLimit(BSTR input);//set the disk space limit
		void setQuotaVolume(BSTR input);//set the quota volume letter
		void setStatus(char* input);//set the status for the user
		void setWarningLimit(BSTR input);//set the warning limit
		_userInfo getStruct();//get the structure
		
private:
		_userInfo user_info;//userinfo object
		


};
