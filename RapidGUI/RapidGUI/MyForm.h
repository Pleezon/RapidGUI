#pragma once
#include <Windows.h>
namespace RapidGUI {



	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->dragging = false;

		}
		void repaintBoxes() {
			SprayFieldX->Invalidate();
			SprayPatternBox->Invalidate();
			SprayFieldY->Invalidate();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ exitButton;
	private: System::Windows::Forms::Button^ minimizeButton;
	private: System::Windows::Forms::FlowLayoutPanel^ Controlbar;
	private: bool dragging;
	private: Point offset;
	private: System::Windows::Forms::PictureBox^ SprayPatternBox;
	private: System::Windows::Forms::PictureBox^ SprayFieldX;
	private: System::Windows::Forms::PictureBox^ SprayFieldY;
	public: System::Windows::Forms::NumericUpDown^ RandomPercentNumberBox;
	private:
	public: System::Windows::Forms::CheckBox^ RegenerateBox;
	public:
	public: System::Windows::Forms::ComboBox^ selectedInterpolationBox;

	public: System::Windows::Forms::ComboBox^ GunBox;
	public: System::Windows::Forms::ComboBox^ ScopeBox;

	private: System::Windows::Forms::Label^ label1;
	public:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ RapidLabel;
	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::CheckBox^ enabledBox;
	private:





	private:



	private:


	public:

	private:

	public:

	private:




	private:



	public:




	public:

	public:

	public:

	public:
	public:

	public:


	protected:

	protected:

	protected:

	protected:

	protected:

	protected:

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->exitButton = (gcnew System::Windows::Forms::Button());
			this->minimizeButton = (gcnew System::Windows::Forms::Button());
			this->Controlbar = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->SprayPatternBox = (gcnew System::Windows::Forms::PictureBox());
			this->SprayFieldX = (gcnew System::Windows::Forms::PictureBox());
			this->SprayFieldY = (gcnew System::Windows::Forms::PictureBox());
			this->RandomPercentNumberBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->RegenerateBox = (gcnew System::Windows::Forms::CheckBox());
			this->selectedInterpolationBox = (gcnew System::Windows::Forms::ComboBox());
			this->GunBox = (gcnew System::Windows::Forms::ComboBox());
			this->ScopeBox = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RapidLabel = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->enabledBox = (gcnew System::Windows::Forms::CheckBox());
			this->Controlbar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayPatternBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayFieldX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayFieldY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RandomPercentNumberBox))->BeginInit();
			this->SuspendLayout();
			// 
			// exitButton
			// 
			this->exitButton->BackColor = System::Drawing::Color::Gray;
			this->exitButton->CausesValidation = false;
			this->exitButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exitButton->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exitButton->Location = System::Drawing::Point(88, 3);
			this->exitButton->Name = L"exitButton";
			this->exitButton->Size = System::Drawing::Size(73, 33);
			this->exitButton->TabIndex = 0;
			this->exitButton->Text = L"exit";
			this->exitButton->UseVisualStyleBackColor = false;
			this->exitButton->Click += gcnew System::EventHandler(this, &MyForm::exitButton_Click);
			// 
			// minimizeButton
			// 
			this->minimizeButton->BackColor = System::Drawing::Color::Gray;
			this->minimizeButton->CausesValidation = false;
			this->minimizeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->minimizeButton->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->minimizeButton->Location = System::Drawing::Point(3, 3);
			this->minimizeButton->Name = L"minimizeButton";
			this->minimizeButton->Size = System::Drawing::Size(79, 33);
			this->minimizeButton->TabIndex = 1;
			this->minimizeButton->Text = L"minimize";
			this->minimizeButton->UseVisualStyleBackColor = false;
			this->minimizeButton->Click += gcnew System::EventHandler(this, &MyForm::minimizeButton_Click);
			// 
			// Controlbar
			// 
			this->Controlbar->CausesValidation = false;
			this->Controlbar->Controls->Add(this->exitButton);
			this->Controlbar->Controls->Add(this->minimizeButton);
			this->Controlbar->Location = System::Drawing::Point(526, -2);
			this->Controlbar->Name = L"Controlbar";
			this->Controlbar->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Controlbar->Size = System::Drawing::Size(164, 42);
			this->Controlbar->TabIndex = 2;
			// 
			// SprayPatternBox
			// 
			this->SprayPatternBox->BackColor = System::Drawing::Color::Gray;
			this->SprayPatternBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SprayPatternBox->Location = System::Drawing::Point(12, 31);
			this->SprayPatternBox->Name = L"SprayPatternBox";
			this->SprayPatternBox->Size = System::Drawing::Size(260, 406);
			this->SprayPatternBox->TabIndex = 3;
			this->SprayPatternBox->TabStop = false;
			this->SprayPatternBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::SprayPatternBox_Paint);
			// 
			// SprayFieldX
			// 
			this->SprayFieldX->BackColor = System::Drawing::Color::Gray;
			this->SprayFieldX->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SprayFieldX->Location = System::Drawing::Point(278, 229);
			this->SprayFieldX->Name = L"SprayFieldX";
			this->SprayFieldX->Size = System::Drawing::Size(400, 101);
			this->SprayFieldX->TabIndex = 4;
			this->SprayFieldX->TabStop = false;
			this->SprayFieldX->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::SprayFieldX_Paint);
			// 
			// SprayFieldY
			// 
			this->SprayFieldY->BackColor = System::Drawing::Color::Gray;
			this->SprayFieldY->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SprayFieldY->Location = System::Drawing::Point(278, 336);
			this->SprayFieldY->Name = L"SprayFieldY";
			this->SprayFieldY->Size = System::Drawing::Size(400, 101);
			this->SprayFieldY->TabIndex = 5;
			this->SprayFieldY->TabStop = false;
			this->SprayFieldY->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::SprayFieldY_Paint);
			// 
			// RandomPercentNumberBox
			// 
			this->RandomPercentNumberBox->BackColor = System::Drawing::Color::DimGray;
			this->RandomPercentNumberBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RandomPercentNumberBox->ForeColor = System::Drawing::SystemColors::WindowText;
			this->RandomPercentNumberBox->Location = System::Drawing::Point(380, 203);
			this->RandomPercentNumberBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->RandomPercentNumberBox->Name = L"RandomPercentNumberBox";
			this->RandomPercentNumberBox->Size = System::Drawing::Size(58, 20);
			this->RandomPercentNumberBox->TabIndex = 9;
			this->RandomPercentNumberBox->ValueChanged += gcnew System::EventHandler(this, &MyForm::RandomPercentNumberBox_ValueChanged);
			// 
			// RegenerateBox
			// 
			this->RegenerateBox->Appearance = System::Windows::Forms::Appearance::Button;
			this->RegenerateBox->AutoSize = true;
			this->RegenerateBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RegenerateBox->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegenerateBox->Location = System::Drawing::Point(278, 85);
			this->RegenerateBox->Name = L"RegenerateBox";
			this->RegenerateBox->Size = System::Drawing::Size(111, 24);
			this->RegenerateBox->TabIndex = 8;
			this->RegenerateBox->Text = L"auto refresh";
			this->RegenerateBox->UseVisualStyleBackColor = false;
			this->RegenerateBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::RegenerateBox_CheckedChanged);
			// 
			// selectedInterpolationBox
			// 
			this->selectedInterpolationBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->selectedInterpolationBox->FormattingEnabled = true;
			this->selectedInterpolationBox->Location = System::Drawing::Point(278, 202);
			this->selectedInterpolationBox->Name = L"selectedInterpolationBox";
			this->selectedInterpolationBox->Size = System::Drawing::Size(84, 21);
			this->selectedInterpolationBox->TabIndex = 6;
			this->selectedInterpolationBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::selectedInterpolationBox_SelectedIndexChanged);
			// 
			// GunBox
			// 
			this->GunBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->GunBox->FormattingEnabled = true;
			this->GunBox->Location = System::Drawing::Point(278, 58);
			this->GunBox->Name = L"GunBox";
			this->GunBox->Size = System::Drawing::Size(191, 21);
			this->GunBox->TabIndex = 11;
			this->GunBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::GunBox_SelectedIndexChanged);
			// 
			// ScopeBox
			// 
			this->ScopeBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ScopeBox->FormattingEnabled = true;
			this->ScopeBox->Location = System::Drawing::Point(278, 31);
			this->ScopeBox->Name = L"ScopeBox";
			this->ScopeBox->Size = System::Drawing::Size(191, 21);
			this->ScopeBox->TabIndex = 12;
			this->ScopeBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ScopeBox_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(377, 186);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 14);
			this->label1->TabIndex = 14;
			this->label1->Text = L"RANDOM%";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(278, 186);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(43, 14);
			this->label2->TabIndex = 15;
			this->label2->Text = L"MODE";
			// 
			// RapidLabel
			// 
			this->RapidLabel->AutoSize = true;
			this->RapidLabel->Font = (gcnew System::Drawing::Font(L"Base 05", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RapidLabel->Location = System::Drawing::Point(12, 5);
			this->RapidLabel->Name = L"RapidLabel";
			this->RapidLabel->Size = System::Drawing::Size(106, 23);
			this->RapidLabel->TabIndex = 16;
			this->RapidLabel->Text = L"Rapid b1";
			this->RapidLabel->Click += gcnew System::EventHandler(this, &MyForm::RapidLabel_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Constantia", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(124, 13);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(102, 15);
			this->label3->TabIndex = 17;
			this->label3->Text = L"by Pleezon#8867";
			// 
			// enabledBox
			// 
			this->enabledBox->Appearance = System::Windows::Forms::Appearance::Button;
			this->enabledBox->AutoSize = true;
			this->enabledBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->enabledBox->Font = (gcnew System::Drawing::Font(L"Base 05", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->enabledBox->Location = System::Drawing::Point(395, 85);
			this->enabledBox->Name = L"enabledBox";
			this->enabledBox->Size = System::Drawing::Size(73, 24);
			this->enabledBox->TabIndex = 18;
			this->enabledBox->Text = L"enabled";
			this->enabledBox->UseVisualStyleBackColor = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(690, 446);
			this->Controls->Add(this->enabledBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->RapidLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ScopeBox);
			this->Controls->Add(this->GunBox);
			this->Controls->Add(this->RandomPercentNumberBox);
			this->Controls->Add(this->RegenerateBox);
			this->Controls->Add(this->selectedInterpolationBox);
			this->Controls->Add(this->SprayPatternBox);
			this->Controls->Add(this->SprayFieldY);
			this->Controls->Add(this->SprayFieldX);
			this->Controls->Add(this->Controlbar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->Text = L"Rapid";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Shown += gcnew System::EventHandler(this, &MyForm::MyForm_Shown);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
			this->Controlbar->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayPatternBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayFieldX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SprayFieldY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RandomPercentNumberBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void exitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::Application::Exit();
	}
	private: System::Void minimizeButton_Click(System::Object^ sender, System::EventArgs^ e) {
		WindowState = FormWindowState::Minimized;
	}
	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->dragging = true;
		this->offset = Point(e->X, e->Y);

	}
	private: System::Void MyForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (this->dragging) {
			Point currentScreenPos = PointToScreen(e->Location);
			Location = Point(currentScreenPos.X - this->offset.X,
				currentScreenPos.Y - this->offset.Y);
		}
	}
	private: System::Void MyForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->dragging = false;
	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void MyForm_Shown(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SprayPatternBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void SprayFieldX_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void SprayFieldY_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void selectedInterpolationBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void labelGeneration_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void RegenerateBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void RandomPercentNumberBox_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void GunBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ScopeBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void RapidLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}