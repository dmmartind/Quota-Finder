//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: UserInfo Class Code 

//****************************************************************************************

#include "stdafx.h"
#include "User.h"



// ----------------------------------------------------------------
//  Name:           _userInfoInterface
//	Class:			_userInfoInterface
//  Description:    constructor
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

_userInfoInterface::_userInfoInterface()//constructor
		{
			clear();

		}

// ----------------------------------------------------------------
//  Name:           ~_userInfoInterface
//	Class:			_userInfoInterface
//  Description:    deconstructor
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		_userInfoInterface::~_userInfoInterface()//deconstructor
		{
			clear();
			
		}


// ----------------------------------------------------------------
//  Name:           ~_userInfoInterface
//	Class:			_userInfoInterface
//  Description:    deconstructor
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void _userInfoInterface::clear()//constructor
{
			user_info._userNum = 0;
			user_info._username=nullptr;
			user_info._domain=nullptr;
			user_info._diskSpaceUsed = nullptr;
			user_info._diskSpaceLimit = nullptr;
			user_info._QuotaVolume = nullptr;
			user_info._status = nullptr;
			user_info._warningLimit = nullptr;
}

// ----------------------------------------------------------------
//  Name:           setUserNum
//	Class:			_userInfoInterface
//  Description:	set user number
//  Arguments:      int
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void _userInfoInterface::setUserNum(int input)//set the user number
		{
			user_info._userNum = input;
		}


// ----------------------------------------------------------------
//  Name:			setUserID
//	Class:			_userInfoInterface
//  Description:    set username
//  Arguments:      char*
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void _userInfoInterface::setUserID(String^ input)//set the username
		{
			
			user_info._username = input;
		}

// ----------------------------------------------------------------
//  Name:           setDomain
//	Class:			_userInfoInterface
//  Description:    set hostname
//  Arguments:      char*
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////


		void _userInfoInterface::setDomain(String^ input)//set the hostname
		{
			user_info._domain=input;
		}

// ----------------------------------------------------------------
//  Name:           setDiskSpaceUsed
//	Class:			_userInfoInterface
//  Description:    set disk space used by the user
//  Arguments:      BSTR
//  Return Value:   void
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////


		void _userInfoInterface::setDiskSpaceUsed(BSTR input)//set the disk space used
		{
			int length = SysStringByteLen(input)/2;
			String^ changedInput= gcnew String(input,0,length);
			user_info._diskSpaceUsed = changedInput;

		}

// ----------------------------------------------------------------
//  Name:           ~_userInfoInterface
//	Class:			_userInfoInterface
//  Description:    set disk space limit
//  Arguments:      BSTR
//  Return Value:   void
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void _userInfoInterface::setDiskSpaceLimit(BSTR input)//set the disk space limit
		{
			int length = SysStringByteLen(input)/2;
			String^ changedInput= gcnew String(input,0,length);
			user_info._diskSpaceLimit = changedInput;
		}
		

// ----------------------------------------------------------------
//  Name:           setQuotaVolume
//	Class:			_userInfoInterface
//  Description:    set quota volume for specific user
//  Arguments:      BSTR
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void _userInfoInterface::setQuotaVolume(BSTR input)//set the quota volume letter
		{
			int length = SysStringByteLen(input)/2;//get length of input
			String^ changedInput = gcnew String(input,0,length);//change input to managed string
			user_info._QuotaVolume = changedInput;//set quota volume
		}

// ----------------------------------------------------------------
//  Name:           setStatus
//	Class:			_userInfoInterface
//  Description:    set the status for the user
//  Arguments:      char*
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////


		void _userInfoInterface::setStatus(char* input)
		{
			String^ inputtemp = gcnew String(input,0,strlen(input)); //change input to managed string
			user_info._status = inputtemp;//set status
		}

// ----------------------------------------------------------------
//  Name:           setWarningLimit
//	Class:			_userInfoInterface
//  Description:    set the warning limit
//  Arguments:      BSTR
//  Return Value:   VOID
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void _userInfoInterface::setWarningLimit(BSTR input)
		{
			int length = SysStringByteLen(input)/2;//get length of input
			String^ changedInput= gcnew String(input,0,length);//change input to managed string
			user_info._warningLimit = changedInput;//set the warning limit
		}

// ----------------------------------------------------------------
//  Name:			getStruct
//	Class:			_userInfoInterface
//  Description:    get the structure
//  Arguments:      NONE
//  Return Value:   _userInfo
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
		_userInfo _userInfoInterface::getStruct()
		{
			return user_info;
		}



