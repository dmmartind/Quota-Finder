//*********** (C) Copyright 2010 David Martin All rights reserved. **********
// Purpose: QuotaMain Class Code 

//****************************************************************************************


#pragma once
#include "XML.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;

using namespace System::Data;
using namespace System::Drawing;


namespace Quota {//GUI namespace

	/// <summary>
	/// Summary for QuotaMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>



// ----------------------------------------------------------------
//  Name:           QuotaMain
//	Class:			QuotaMain
//  Description:	CLASS 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public ref class QuotaMain : public System::Windows::Forms::Form
	{
	public:
// ----------------------------------------------------------------
//  Name:           QuotaMain
//	Class:			QuotaMain
//  Description:	Constructor 
//  Arguments:      VOID
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		QuotaMain(void)
		{
			InitializeComponent();
			GUI_WMI = new WMI();//wmi instance
			
		}

	protected:
// ----------------------------------------------------------------
//  Name:           ~QuotaMain
//	Class:			QuotaMain
//  Description:	Deconstructor 
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		~QuotaMain()
		{
			try
			{
				if (components)//if GUI components is valid
				{
					delete components;//then delete
				}
			if(GUI_WMI)//if wmi object is valid
				delete GUI_WMI;//then delete
			}
			catch (Exception ^e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////

		
//attributes
	private: System::Windows::Forms::ComboBox^  user_name_sel;
	protected: 
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Panel^  user_panel;
	private: System::Windows::Forms::TextBox^  WarningLimitBox;

	private: System::Windows::Forms::TextBox^  DiskSpaceUsed;

	private: System::Windows::Forms::TextBox^  StatusBox;

	private: System::Windows::Forms::TextBox^  QuotaVolumeText;

	private: System::Windows::Forms::TextBox^  LimitBox;

	private: System::Windows::Forms::TextBox^  UserNumberText;
	private: System::Windows::Forms::Label^  WarningLimitLabel;

	private: System::Windows::Forms::Label^  DiskSpaceUsedLabel;

	private: System::Windows::Forms::Label^  StatusLabel;
	private: System::Windows::Forms::Label^  QuotaVolumeLabel;



	private: System::Windows::Forms::Label^  LimitLabel;
	private: System::Windows::Forms::Label^  UserNumLabel;
	private: System::Windows::Forms::Label^  UserNameLabel;
	private: System::Windows::Forms::Label^  ProcessLabel;
	private: System::Windows::Forms::Button^  UpdateUserList;
	private: System::Windows::Forms::Button^  SaveAllButton;
	private: System::Windows::Forms::Button^  SaveCurrentButton;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

// ----------------------------------------------------------------
//  Name:           InitializeComponent
//	Class:			Form1
//  Description:	Creates all the instances of all the components
//  Arguments:      VOID
//  Return Value:   NONE
// ----------------------------------------------------------------
	void InitializeComponent(void)
		{
			this->user_name_sel = (gcnew System::Windows::Forms::ComboBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->user_panel = (gcnew System::Windows::Forms::Panel());
			this->UpdateUserList = (gcnew System::Windows::Forms::Button());
			this->SaveAllButton = (gcnew System::Windows::Forms::Button());
			this->SaveCurrentButton = (gcnew System::Windows::Forms::Button());
			this->WarningLimitLabel = (gcnew System::Windows::Forms::Label());
			this->DiskSpaceUsedLabel = (gcnew System::Windows::Forms::Label());
			this->StatusLabel = (gcnew System::Windows::Forms::Label());
			this->QuotaVolumeLabel = (gcnew System::Windows::Forms::Label());
			this->LimitLabel = (gcnew System::Windows::Forms::Label());
			this->UserNumLabel = (gcnew System::Windows::Forms::Label());
			this->WarningLimitBox = (gcnew System::Windows::Forms::TextBox());
			this->DiskSpaceUsed = (gcnew System::Windows::Forms::TextBox());
			this->StatusBox = (gcnew System::Windows::Forms::TextBox());
			this->QuotaVolumeText = (gcnew System::Windows::Forms::TextBox());
			this->LimitBox = (gcnew System::Windows::Forms::TextBox());
			this->UserNumberText = (gcnew System::Windows::Forms::TextBox());
			this->UserNameLabel = (gcnew System::Windows::Forms::Label());
			this->ProcessLabel = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->user_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// user_name_sel
			// 
			this->user_name_sel->FormattingEnabled = true;
			this->user_name_sel->Location = System::Drawing::Point(85, 14);
			this->user_name_sel->Name = L"user_name_sel";
			this->user_name_sel->Size = System::Drawing::Size(200, 21);
			this->user_name_sel->TabIndex = 0;
			this->user_name_sel->SelectedIndexChanged += gcnew System::EventHandler(this, &QuotaMain::user_name_sel_SelectedIndexChanged);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(459, 12);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(236, 23);
			this->progressBar1->TabIndex = 1;
			// 
			// user_panel
			// 
			this->user_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->user_panel->Controls->Add(this->UpdateUserList);
			this->user_panel->Controls->Add(this->SaveAllButton);
			this->user_panel->Controls->Add(this->SaveCurrentButton);
			this->user_panel->Controls->Add(this->WarningLimitLabel);
			this->user_panel->Controls->Add(this->DiskSpaceUsedLabel);
			this->user_panel->Controls->Add(this->StatusLabel);
			this->user_panel->Controls->Add(this->QuotaVolumeLabel);
			this->user_panel->Controls->Add(this->LimitLabel);
			this->user_panel->Controls->Add(this->UserNumLabel);
			this->user_panel->Controls->Add(this->WarningLimitBox);
			this->user_panel->Controls->Add(this->DiskSpaceUsed);
			this->user_panel->Controls->Add(this->StatusBox);
			this->user_panel->Controls->Add(this->QuotaVolumeText);
			this->user_panel->Controls->Add(this->LimitBox);
			this->user_panel->Controls->Add(this->UserNumberText);
			this->user_panel->Location = System::Drawing::Point(0, 56);
			this->user_panel->Name = L"user_panel";
			this->user_panel->Size = System::Drawing::Size(711, 206);
			this->user_panel->TabIndex = 2;
			// 
			// UpdateUserList
			// 
			this->UpdateUserList->Location = System::Drawing::Point(600, 170);
			this->UpdateUserList->Name = L"UpdateUserList";
			this->UpdateUserList->Size = System::Drawing::Size(95, 23);
			this->UpdateUserList->TabIndex = 14;
			this->UpdateUserList->Text = L"Update User List";
			this->UpdateUserList->UseVisualStyleBackColor = true;
			this->UpdateUserList->Click += gcnew System::EventHandler(this, &QuotaMain::UpdateUserList_Click);
			// 
			// SaveAllButton
			// 
			this->SaveAllButton->Location = System::Drawing::Point(321, 170);
			this->SaveAllButton->Name = L"SaveAllButton";
			this->SaveAllButton->Size = System::Drawing::Size(95, 23);
			this->SaveAllButton->TabIndex = 13;
			this->SaveAllButton->Text = L"Save All";
			this->SaveAllButton->UseVisualStyleBackColor = true;
			this->SaveAllButton->Click += gcnew System::EventHandler(this, &QuotaMain::SaveAllButton_Click);
			// 
			// SaveCurrentButton
			// 
			this->SaveCurrentButton->Location = System::Drawing::Point(12, 170);
			this->SaveCurrentButton->Name = L"SaveCurrentButton";
			this->SaveCurrentButton->Size = System::Drawing::Size(95, 23);
			this->SaveCurrentButton->TabIndex = 12;
			this->SaveCurrentButton->Text = L"Save Current";
			this->SaveCurrentButton->UseVisualStyleBackColor = true;
			this->SaveCurrentButton->Click += gcnew System::EventHandler(this, &QuotaMain::SaveCurrentButton_Click);
			// 
			// WarningLimitLabel
			// 
			this->WarningLimitLabel->AutoSize = true;
			this->WarningLimitLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->WarningLimitLabel->Location = System::Drawing::Point(417, 109);
			this->WarningLimitLabel->Name = L"WarningLimitLabel";
			this->WarningLimitLabel->Size = System::Drawing::Size(68, 20);
			this->WarningLimitLabel->TabIndex = 11;
			this->WarningLimitLabel->Text = L"Warning Limit";
			// 
			// DiskSpaceUsedLabel
			// 
			this->DiskSpaceUsedLabel->AutoSize = true;
			this->DiskSpaceUsedLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->DiskSpaceUsedLabel->Location = System::Drawing::Point(409, 65);
			this->DiskSpaceUsedLabel->Name = L"DiskSpaceUsedLabel";
			this->DiskSpaceUsedLabel->Size = System::Drawing::Size(80, 20);
			this->DiskSpaceUsedLabel->TabIndex = 10;
			this->DiskSpaceUsedLabel->Text = L"Disk Space Used";
			// 
			// StatusLabel
			// 
			this->StatusLabel->AutoSize = true;
			this->StatusLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->StatusLabel->Location = System::Drawing::Point(449, 19);
			this->StatusLabel->Name = L"StatusLabel";
			this->StatusLabel->Size = System::Drawing::Size(36, 20);
			this->StatusLabel->TabIndex = 9;
			this->StatusLabel->Text = L"Status";
			// 
			// QuotaVolumeLabel
			// 
			this->QuotaVolumeLabel->AutoSize = true;
			this->QuotaVolumeLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->QuotaVolumeLabel->Location = System::Drawing::Point(11, 107);
			this->QuotaVolumeLabel->Name = L"QuotaVolumeLabel";
			this->QuotaVolumeLabel->Size = System::Drawing::Size(67, 20);
			this->QuotaVolumeLabel->TabIndex = 8;
			this->QuotaVolumeLabel->Text = L"Quota Volume";
			// 
			// LimitLabel
			// 
			this->LimitLabel->AutoSize = true;
			this->LimitLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LimitLabel->Location = System::Drawing::Point(12, 63);
			this->LimitLabel->Name = L"LimitLabel";
			this->LimitLabel->Size = System::Drawing::Size(28, 20);
			this->LimitLabel->TabIndex = 7;
			this->LimitLabel->Text = L"Limit";
			// 
			// UserNumLabel
			// 
			this->UserNumLabel->AutoSize = true;
			this->UserNumLabel->Font = (gcnew System::Drawing::Font(L"Agency FB", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->UserNumLabel->Location = System::Drawing::Point(12, 19);
			this->UserNumLabel->Name = L"UserNumLabel";
			this->UserNumLabel->Size = System::Drawing::Size(67, 20);
			this->UserNumLabel->TabIndex = 6;
			this->UserNumLabel->Text = L"User Number";
			// 
			// WarningLimitBox
			// 
			this->WarningLimitBox->Location = System::Drawing::Point(495, 109);
			this->WarningLimitBox->Name = L"WarningLimitBox";
			this->WarningLimitBox->ReadOnly = true;
			this->WarningLimitBox->Size = System::Drawing::Size(200, 20);
			this->WarningLimitBox->TabIndex = 5;
			// 
			// DiskSpaceUsed
			// 
			this->DiskSpaceUsed->Location = System::Drawing::Point(495, 65);
			this->DiskSpaceUsed->Name = L"DiskSpaceUsed";
			this->DiskSpaceUsed->ReadOnly = true;
			this->DiskSpaceUsed->Size = System::Drawing::Size(200, 20);
			this->DiskSpaceUsed->TabIndex = 4;
			// 
			// StatusBox
			// 
			this->StatusBox->Location = System::Drawing::Point(495, 21);
			this->StatusBox->Name = L"StatusBox";
			this->StatusBox->ReadOnly = true;
			this->StatusBox->Size = System::Drawing::Size(200, 20);
			this->StatusBox->TabIndex = 3;
			// 
			// QuotaVolumeText
			// 
			this->QuotaVolumeText->Location = System::Drawing::Point(85, 109);
			this->QuotaVolumeText->Name = L"QuotaVolumeText";
			this->QuotaVolumeText->ReadOnly = true;
			this->QuotaVolumeText->Size = System::Drawing::Size(200, 20);
			this->QuotaVolumeText->TabIndex = 2;
			// 
			// LimitBox
			// 
			this->LimitBox->Location = System::Drawing::Point(85, 65);
			this->LimitBox->Name = L"LimitBox";
			this->LimitBox->ReadOnly = true;
			this->LimitBox->Size = System::Drawing::Size(200, 20);
			this->LimitBox->TabIndex = 1;
			// 
			// UserNumberText
			// 
			this->UserNumberText->Location = System::Drawing::Point(85, 21);
			this->UserNumberText->Name = L"UserNumberText";
			this->UserNumberText->ReadOnly = true;
			this->UserNumberText->Size = System::Drawing::Size(200, 20);
			this->UserNumberText->TabIndex = 0;
			// 
			// UserNameLabel
			// 
			this->UserNameLabel->AutoSize = true;
			this->UserNameLabel->Font = (gcnew System::Drawing::Font(L"Tw Cen MT Condensed", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->UserNameLabel->Location = System::Drawing::Point(12, 13);
			this->UserNameLabel->Name = L"UserNameLabel";
			this->UserNameLabel->Size = System::Drawing::Size(62, 19);
			this->UserNameLabel->TabIndex = 3;
			this->UserNameLabel->Text = L"User Name";
			// 
			// ProcessLabel
			// 
			this->ProcessLabel->AutoSize = true;
			this->ProcessLabel->Font = (gcnew System::Drawing::Font(L"Tw Cen MT Condensed", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ProcessLabel->Location = System::Drawing::Point(363, 13);
			this->ProcessLabel->Name = L"ProcessLabel";
			this->ProcessLabel->Size = System::Drawing::Size(90, 19);
			this->ProcessLabel->TabIndex = 4;
			this->ProcessLabel->Text = L"Current Progress";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"XML|*.xml";
			// 
			// QuotaMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(707, 261);
			this->Controls->Add(this->ProcessLabel);
			this->Controls->Add(this->UserNameLabel);
			this->Controls->Add(this->user_panel);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->user_name_sel);
			this->Name = L"QuotaMain";
			this->Text = L"Quota Finder";
			this->user_panel->ResumeLayout(false);
			this->user_panel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


// ----------------------------------------------------------------
//  Name:           PopulateLists
//	Class:			Form1
//  Description:	Creates all the instances of all the components
//  Arguments:      NONE
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			void PopulateLists()
        {

			int userCounter=0,max_users=0;//init user counter and max users var
			float progress_multiplyer=0;//progress bar multiplier

           	if(!GUI_WMI->clearList())//clear WMI list
			{
				MessageBox::Show("Could not clear WMI memory ", "ERROR" ,System::Windows::Forms::MessageBoxButtons::OK);
				Application::Exit();
			}

				if(!GUI_WMI->Select("WQL","SELECT * FROM Win32_DiskQuota"))//send SQL command to WMI and send the result to the list
				{
					MessageBox::Show("Could send WMI command" , "ERROR" , System::Windows::Forms::MessageBoxButtons::OK);
					Application::Exit();

				}
			max_users = GUI_WMI->size;//set the max user var 
			array<String^>^ userName = gcnew array<String^>(max_users);//create an string array with the size of the max amount of users
			 
			userCounter=0;//set the user counter to 0
			progress_multiplyer=float(100)/float(max_users);//set the progress bar multiplier
			try
			{

				for each (ListNode<_userInfo>^ node in (MyList<_userInfo>^)GUI_WMI->getList())//iterate through the list
				{
					//create new string with the user name and set it to the current index of the array
					userName[userCounter] = node->item._username;			
					userCounter++;//increment user counter
					progressBar1->Value=int(progress_multiplyer * float(userCounter));//progress bar increment

				
				}
			
			Sleep(500);
			progressBar1->Value = 0;//reset
			user_name_sel->Items->AddRange(userName);//add array to the combobox
			}
			catch (Exception ^e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
				Application::Exit();
			}
		}

// ----------------------------------------------------------------
//  Name:           user_name_sel_SelectedIndexChanged
//	Class:			Form1
//  Description:	action for the combo box index change
//  Arguments:      System::Object^,System::EventArgs^
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	private: System::Void user_name_sel_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
				int userCounter=0;//init user counter
			 int selectedIndex = user_name_sel->SelectedIndex;//get the selected index from the combo box
			//create a temporary string and allocate an index of 10
			try
			{
				char* userNumTemp = (char*)malloc(10);//create temporary string
			
				for each (ListNode<_userInfo>^ node in (MyList<_userInfo>^)GUI_WMI->getList())//iterate through the list
				{
					if(userCounter == selectedIndex)//if the selected index matches the current node
					{
					
						//convert the number into a string
						_itoa_s(node->item._userNum,userNumTemp, sizeof(userNumTemp),10);
						//convert native string into managed string
						String^ tempText = gcnew String(userNumTemp,0,strlen(userNumTemp));
						UserNumberText->Text = tempText;//set the string to the textbox
						LimitBox->Text = node->item._diskSpaceLimit;
						QuotaVolumeText->Text = node->item._QuotaVolume;//set the string to the textbox
						StatusBox->Text = node->item._status;//set the string to the textbox
						DiskSpaceUsed->Text = node->item._diskSpaceUsed;//set the string to the textbox
						String^ warningLimitTemp = node->item._warningLimit;//set the string to the textbox
						WarningLimitBox->Text = warningLimitTemp;//set the string to the textbox


					}
					userCounter++;//increment counter
				}

			///////////////Memory Cleanup///////////////////////////
			free(userNumTemp);
			////////////////////////////////////////////////////////
			}
			catch (Exception ^e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
				Application::Exit();
			}
		}

// ----------------------------------------------------------------
//  Name:           SaveCurrentButton_Click
//	Class:			Form1
//  Description:	action for the update user list button
//  Arguments:      System::Object^,System::EventArgs^
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: System::Void SaveCurrentButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 try
			 {
				 saveFileDialog1->ShowDialog();//show save dialog
				//get filename and directory path from the user
				String^ file_name=gcnew String(saveFileDialog1->FileName);
				int selectedIndex = user_name_sel->SelectedIndex;//get the user choice from the user combo box
				_XMLFactory^ xml= gcnew _XMLFactory();//create xml output class
				MyList<_userInfo>^ newList = GUI_WMI->getList();//copy list to temporary location
						
			  xml->output(selectedIndex,file_name,newList);//send to output
				//with the arguments of the user selection, chosen filename, and the copied list
			 }
			catch (Exception ^e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
				Application::Exit();
			}
			
			

		 }


// ----------------------------------------------------------------
//  Name:           SaveAllButton_Click
//	Class:			Form1
//  Description:	action for the save all button
//  Arguments:      System::Object^,System::EventArgs^
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: System::Void SaveAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  try
			 {
				 saveFileDialog1->ShowDialog();//show save as dialog
				//get the filename and directory path 
				String^ file_name=gcnew String(saveFileDialog1->FileName);
				_XMLFactory^ xml= gcnew _XMLFactory();//create xml output class
				MyList<_userInfo>^ newList = GUI_WMI->getList();//copy wmi list into a temporary location
			 
				xml->output(file_name, newList);//xml output with the
				//user defined filename and the new list
			}
			catch (Exception ^e)//catch unforeseen error and display error
			{
				MessageBox::Show(String::Format("Error: ", e->Message),"ERROR",Forms::MessageBoxButtons::OK);
				Application::Exit();//exit application
			}



		 }

 // ----------------------------------------------------------------
//  Name:           UpdateUserList_Click
//	Class:			Form1
//  Description:	action for the save button
//  Arguments:      System::Object^,System::EventArgs^
//  Return Value:   NONE
// ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

private: System::Void UpdateUserList_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 user_name_sel->Items->Clear();//clear combo box
			 PopulateLists();//grab new user info, fill the list, and the combo box.
		 }


private:
		WMI* GUI_WMI;//WMI object
};
};
