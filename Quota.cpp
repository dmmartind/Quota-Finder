//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: Startup Code 

//****************************************************************************************
// Quota.cpp : main project file.

#include "stdafx.h"
#include "QuotaMain.h"

using namespace Quota;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	try
	{
	// enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// create the main window and run it
	Application::Run(gcnew QuotaMain());
	return 0;
	}
	catch (Exception ^e)//catch unforeseen error and display error
	{
		MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
		return 0;
	}
}
