#pragma once
#include <msclr\marshal_cppstd.h>	/* String^ to string */
#include "Parser.h"
#include "WMemStat.h"



namespace PasswdParser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;	//unmanaged fun ptr



	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	public:
		static void RUN() {
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
			MyForm form;

			ManagedBWReportProgress^ managed1 = gcnew ManagedBWReportProgress(%form, &BWReportProgress);
			IntPtr stubPointer1 = Marshal::GetFunctionPointerForDelegate(managed1);
			form.BWReportProgressPtr = static_cast<UnmanagedBWReportProgress>(stubPointer1.ToPointer());


			ManagedBWCancellationPending^ managed2 = gcnew ManagedBWCancellationPending(%form, &BWCancellationPending);
			IntPtr stubPointer2 = Marshal::GetFunctionPointerForDelegate(managed2);
			form.BWCancellationPendingPtr = static_cast<UnmanagedBWCancellationPending>(stubPointer2.ToPointer());

			Application::Run(%form);

			GC::KeepAlive(managed1);	// Important: ensure stub can't be collected while native code is running.
			GC::KeepAlive(managed2);	// Important: ensure stub can't be collected while native code is running.

		}


		///	get unmanaged function pointer for callback
		typedef void(*UnmanagedBWReportProgress)(int arg);
		delegate void ManagedBWReportProgress(int arg);

		void BWReportProgress(int arg) {
			this->backgroundWorker1->ReportProgress(arg);
		}
		void(*BWReportProgressPtr)(int);
		///
		///	get unmanaged function pointer for callback
		typedef bool(*UnmanagedBWCancellationPending)(void);
		delegate bool ManagedBWCancellationPending(void);

		bool BWCancellationPending(void) {
			return this->backgroundWorker1->CancellationPending;
		}
		bool(*BWCancellationPendingPtr)();
		///

	private: int ComboBox2SelectedIndex = 0;


			 MyForm(void) {
				 InitializeComponent();
				 //
				 //TODO: Add the constructor code here
				 //

				 this->folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
				 this->textBox1->Text = System::Windows::Forms::Application::StartupPath;
				 this->comboBox2->SelectedIndex = ComboBox2SelectedIndex;
				 this->textBox2->Text = L":;/|\\";
				 this->textBox3->Location = this->checkedListBox1->Location;
				 this->label1->Focus();	//to_do: not work as it should.
										///
				 WMemStat ms;
				 this->numericUpDown1->Value = (size_t)((ms.Avalible_Physical_Memory() * 0.8) / 1048576);
				 ///

			 }


	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;



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

	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::ComponentModel::IContainer^  components;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->contextMenuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->AllowDrop = true;
			this->checkedListBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkedListBox1->ContextMenuStrip = this->contextMenuStrip1;
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->IntegralHeight = false;
			this->checkedListBox1->Location = System::Drawing::Point(6, 19);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(217, 83);
			this->checkedListBox1->TabIndex = 0;
			this->checkedListBox1->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &MyForm::checkedListBox1_ItemCheck);
			this->checkedListBox1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::checkedListBox1_DragDrop);
			this->checkedListBox1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::checkedListBox1_DragEnter);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripMenuItem1,
					this->toolStripMenuItem2, this->toolStripSeparator1, this->toolStripMenuItem3, this->toolStripMenuItem4
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->contextMenuStrip1->ShowImageMargin = false;
			this->contextMenuStrip1->Size = System::Drawing::Size(123, 98);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(122, 22);
			this->toolStripMenuItem1->Text = L"Select all";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(122, 22);
			this->toolStripMenuItem2->Text = L"Select none";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem2_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(119, 6);
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(122, 22);
			this->toolStripMenuItem3->Text = L"Clear selected";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem3_Click);
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(122, 22);
			this->toolStripMenuItem4->Text = L"Clear all";
			this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem4_Click);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(203, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(20, 20);
			this->button1->TabIndex = 3;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseClick);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->comboBox2);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(229, 130);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Output path: ";
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(72, 98);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(151, 20);
			this->textBox2->TabIndex = 8;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(10, 20);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(187, 20);
			this->textBox1->TabIndex = 7;
			this->textBox1->Validated += gcnew System::EventHandler(this, &MyForm::textBox1_Validated);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 101);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(59, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Delimeters:";
			// 
			// comboBox2
			// 
			this->comboBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"email<delimeter>password", L"login<delimeter>password" });
			this->comboBox2->Location = System::Drawing::Point(72, 45);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(151, 21);
			this->comboBox2->TabIndex = 2;
			this->comboBox2->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox2_SelectionChangeCommitted);
			this->comboBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::comboBox2_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 48);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"String type:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 74);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Buffer (MB):";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			this->numericUpDown1->Location = System::Drawing::Point(72, 72);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(151, 20);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->checkedListBox1);
			this->groupBox2->Location = System::Drawing::Point(12, 176);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(229, 108);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Input files:";
			// 
			// textBox3
			// 
			this->textBox3->AcceptsReturn = true;
			this->textBox3->AcceptsTab = true;
			this->textBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox3->Location = System::Drawing::Point(-137, 67);
			this->textBox3->MaxLength = 0;
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox3->Size = System::Drawing::Size(217, 83);
			this->textBox3->TabIndex = 3;
			this->textBox3->Visible = false;
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.BackgroundImage")));
			this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button4->Location = System::Drawing::Point(171, 84);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(16, 16);
			this->button4->TabIndex = 2;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Location = System::Drawing::Point(188, 84);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(16, 16);
			this->button3->TabIndex = 1;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button3_MouseClick);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(160, 148);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 22);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Start";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->CheckFileExists = false;
			this->openFileDialog1->FileName = L"Select folder";
			this->openFileDialog1->Filter = L"All files (*.*)|*.*|Text files (*.txt)|*.txt|List files (*.lst)|*.lst";
			this->openFileDialog1->Multiselect = true;
			this->openFileDialog1->ValidateNames = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar1->BackColor = System::Drawing::SystemColors::Control;
			this->progressBar1->Cursor = System::Windows::Forms::Cursors::Default;
			this->progressBar1->Enabled = false;
			this->progressBar1->Location = System::Drawing::Point(22, 153);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(132, 12);
			this->progressBar1->Step = 1;
			this->progressBar1->TabIndex = 7;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(253, 296);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MinimumSize = System::Drawing::Size(250, 285);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PasswdParser";
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_Click);
			this->contextMenuStrip1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	///
	private: System::Void MyForm_Click(System::Object^  sender, System::EventArgs^  e) {
		label1->Focus();
	}
	///


	///
	private: System::Void textBox1_Validated(System::Object^  sender, System::EventArgs^  e) {
		if (Directory::Exists(this->textBox1->Text)) {
			this->folderBrowserDialog1->SelectedPath = this->textBox1->Text;
		}
		else {
			this->textBox1->Text = this->folderBrowserDialog1->SelectedPath;
		}
	}


	private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (this->folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->textBox1->Text = this->folderBrowserDialog1->SelectedPath;
		}
	}
	///


	///
	private: System::Void comboBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		this->comboBox2->SelectedIndex = ComboBox2SelectedIndex;
	}


	private: System::Void comboBox2_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
		ComboBox2SelectedIndex = this->comboBox2->SelectedIndex;
	}
	///


	///
	public: void ProcessDirectory(String^ targetDirectory) {
		array<String^>^ fileEntries = Directory::GetFiles(targetDirectory);
		for each(String^ fileName in fileEntries) {
			ProcessFile(fileName);
		}

		array<String^>^ subdirectoryEntries = Directory::GetDirectories(targetDirectory);
		for each(String^ subdirectory in subdirectoryEntries) {
			ProcessDirectory(subdirectory);
		}
	}


	public: void ProcessFile(String^ targetFile) {
		if (File::Exists(targetFile)) {
			std::string str = msclr::interop::marshal_as<std::string>(targetFile);
			if (str.substr(str.find_last_of('.') + 1, str.npos) == "txt" ||
				str.substr(str.find_last_of('.') + 1, str.npos) == "lst") {

				if (!this->checkedListBox1->Items->Contains(targetFile)) {
					this->checkedListBox1->Items->Add(targetFile, System::Windows::Forms::CheckState::Checked);
					this->button2->Enabled = true;
				}
			}
		}
	}


	private: System::Void button3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		openFileDialog1->FileName = L"Select folder";

		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			std::string str = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);
			if (str.rfind("Select folder") != str.npos) {
				str = str.substr(0, str.find_last_of('\\'));
				String^ folderPath = gcnew String(str.c_str());
				ProcessDirectory(folderPath);
				return;
			}

			for each(String^ it in this->openFileDialog1->FileNames) {
				ProcessFile(it);
			}
		}
	}


	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		while (this->checkedListBox1->CheckedItems->Count) {
			this->checkedListBox1->Items->RemoveAt(this->checkedListBox1->CheckedIndices[0]);
		}
	}


	private: System::Void checkedListBox1_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
			e->Effect = DragDropEffects::All;
		}
		else {
			e->Effect = DragDropEffects::None;
		}
	}


	private: System::Void checkedListBox1_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		array<String^>^ droplist = (array<String^>^)e->Data->GetData(DataFormats::FileDrop, false);
		for each(String^ it in droplist) {
			if (Directory::Exists(it)) {
				ProcessDirectory(it);
			}
			else {
				ProcessFile(it);
			}
		}
	}


	private: System::Void checkedListBox1_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) {
		if (this->checkedListBox1->CheckedIndices->Count == 1 &&
			e->NewValue == System::Windows::Forms::CheckState::Unchecked) {
			this->button2->Enabled = false;
		}
		else {
			this->button2->Enabled = true;
		}
	}	//check state updated after this event
	///


	///
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int i = 0; i < this->checkedListBox1->Items->Count; ++i)
		{
			checkedListBox1->SetItemCheckState(i, System::Windows::Forms::CheckState::Checked);
		}
	}


	private: System::Void toolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int i = 0; i < this->checkedListBox1->Items->Count; ++i)
		{
			checkedListBox1->SetItemCheckState(i, System::Windows::Forms::CheckState::Unchecked);
		}
	}


	private: System::Void toolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e) {
		while (this->checkedListBox1->CheckedItems->Count) {
			this->checkedListBox1->Items->RemoveAt(this->checkedListBox1->CheckedIndices[0]);
		}
	}


	private: System::Void toolStripMenuItem4_Click(System::Object^  sender, System::EventArgs^  e) {
		this->checkedListBox1->Items->Clear();
	}
	///


	///
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->button2->Text == "Start") {
			this->button2->Enabled = false;
			if (!this->backgroundWorker1->IsBusy) {
				this->groupBox1->Enabled = false;
				this->groupBox2->Enabled = false;
				this->progressBar1->Enabled = true;
				this->button2->Text = "Cancel";
				this->Text = "PasswdParser  " + "0%";
				this->backgroundWorker1->RunWorkerAsync();
			}
			this->button2->Enabled = true;
		}
		else if (this->button2->Text == "Cancel") {
			if (this->backgroundWorker1->IsBusy) {
				this->button2->Enabled = false;
				this->button2->Text = "Wait";
				this->backgroundWorker1->CancelAsync();
			}
		}
		else if (this->button2->Text == "Ok") {
			this->button2->Enabled = false;
			this->groupBox2->Enabled = false;
			this->textBox3->Visible = false;
			this->textBox3->Text = "";
			this->progressBar1->Value = 0;
			this->progressBar1->Enabled = false;
			this->Text = "PasswdParser";
			this->groupBox2->Text = "Input files:";
			this->groupBox1->Enabled = true;
			this->groupBox2->Enabled = true;
			this->button2->Text = "Start";
			this->button2->Enabled = true;
		}
	}
	///


	///
	public: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		int result;
		Parser& ps = Parser::getInstance();
		ps.begin_time = clock();
		ps.basePath = msclr::interop::marshal_as<std::string>(this->textBox1->Text->ToString());
		ps.bufferMax = Convert::ToInt64(this->numericUpDown1->Value) * 1024 * 1024;	//bytes
		ps.delimSet = msclr::interop::marshal_as<std::string>(this->textBox2->Text->ToString());
		//ps.stringFormat = this->comboBox2->SelectedIndex;		//bug?
		ps.stringFormat = this->ComboBox2SelectedIndex;
		///
		ps.CancellationPending = BWCancellationPendingPtr;
		ps.ReportProgress = BWReportProgressPtr;
		///

		for each(String^ it in this->checkedListBox1->CheckedItems) {

			result = ps.parse((msclr::interop::marshal_as<std::string>(it->ToString())).c_str());

			if (result == SUCCESS__) {
				this->backgroundWorker1->ReportProgress((int)((ps.totalFilesCnt * 50) / this->checkedListBox1->Items->Count));
			}
			else if (result == READ_ERROR__) {
				continue;	//skip bad file
			}
			else {
				e->Cancel = true;
				return;
			}
		}

		result = ps.flush();

		if (result != SUCCESS__) {
			e->Cancel = true;
			return;
		}

		result = ps.merge();

		if (result != SUCCESS__) {
			e->Cancel = true;
			return;
		}

		return;
	}


	private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		if (e->ProgressPercentage < 100) {
			this->progressBar1->Value = e->ProgressPercentage;
			this->Text = "PasswdParser  " + e->ProgressPercentage + "%";
		}
	}


	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		Parser& ps = Parser::getInstance();
		ps.cleanupFiles();

		this->progressBar1->Value = 100;
		this->Text = "PasswdParser  " + "100%";

		if (e->Cancelled) {
			if (ps.LastError == ABORT__) {
				ps.appLog(
					std::string("Canceled! \n") +
					"Wasted time: " + ps.getElapsedTime()
				);
			}
			else {
				ps.appLog(
					std::string("Exit on error! \n") +
					"Wasted time: " + ps.getElapsedTime()
				);
			}
		}
		else {
			ps.appLog(
				std::string("Done! \n") +
				"Total merged: \t\t" + std::to_string(ps.totalFilesCnt) + " file(s) \n" +
				"Completed in: \t\t" + ps.getElapsedTime() + "\n" +
				"logins_long.lst \t" + std::to_string(ps.lstLinesCnt[1]) + "\n" +
				"logins_short.lst \t" + std::to_string(ps.lstLinesCnt[0]) + "\n" +
				"passwd_long.lst \t" + std::to_string(ps.lstLinesCnt[3]) + "\n" +
				"passwd_short.lst \t" + std::to_string(ps.lstLinesCnt[2]) + "\n" +
				"unknown_data.lst \t" + std::to_string(ps.lstLinesCnt[4]) + "\n"
			);
		}

		this->groupBox2->Text = L"Log:";
		this->textBox3->AppendText(msclr::interop::marshal_as<String^>(ps.getLog())->Replace("\n", "\r\n"));
		this->textBox3->Visible = true;
		this->groupBox2->Enabled = true;
		ps.writeLog();
		ps.clearData();
		this->button2->Text = "Ok";
		this->button2->Enabled = true;
	}






	};
}




//System::Threading::Thread::Sleep(1000);
//System::Threading::Thread::Sleep(TimeSpan::FromSeconds(1));

//bool% CancelPend_ = this->backgroundWorker1->CancellationPending;
//cli::pin_ptr<bool> pPtr = &CancelPend_;
//ps.CancellationPending = pPtr;

