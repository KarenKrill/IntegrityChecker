#pragma once
#include "stdafx.h"

namespace IntegrityCheckerGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openStandardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsStandardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::TreeView^  treeView2;
	private: System::Windows::Forms::ToolStripMenuItem^  hashToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  checkToolStripMenuItem;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  loadHashesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sortToolStripMenuItem;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openStandardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsStandardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hashToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->checkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->treeView2 = (gcnew System::Windows::Forms::TreeView());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->loadHashesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sortToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->hashToolStripMenuItem, this->checkToolStripMenuItem, this->sortToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(747, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->openStandardToolStripMenuItem,
					this->loadHashesToolStripMenuItem, this->saveAsStandardToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openStandardToolStripMenuItem
			// 
			this->openStandardToolStripMenuItem->Name = L"openStandardToolStripMenuItem";
			this->openStandardToolStripMenuItem->Size = System::Drawing::Size(195, 26);
			this->openStandardToolStripMenuItem->Text = L"Load standard";
			this->openStandardToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openStandardToolStripMenuItem_Click);
			// 
			// saveAsStandardToolStripMenuItem
			// 
			this->saveAsStandardToolStripMenuItem->Name = L"saveAsStandardToolStripMenuItem";
			this->saveAsStandardToolStripMenuItem->Size = System::Drawing::Size(195, 26);
			this->saveAsStandardToolStripMenuItem->Text = L"Save as standard";
			this->saveAsStandardToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveAsStandardToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(195, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// hashToolStripMenuItem
			// 
			this->hashToolStripMenuItem->Name = L"hashToolStripMenuItem";
			this->hashToolStripMenuItem->Size = System::Drawing::Size(54, 24);
			this->hashToolStripMenuItem->Text = L"Hash";
			this->hashToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::hashToolStripMenuItem_Click);
			// 
			// checkToolStripMenuItem
			// 
			this->checkToolStripMenuItem->Name = L"checkToolStripMenuItem";
			this->checkToolStripMenuItem->Size = System::Drawing::Size(60, 24);
			this->checkToolStripMenuItem->Text = L"Check";
			this->checkToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::checkToolStripMenuItem_Click);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 28);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->textBox1);
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->textBox2);
			this->splitContainer1->Panel2->Controls->Add(this->treeView2);
			this->splitContainer1->Size = System::Drawing::Size(747, 382);
			this->splitContainer1->SplitterDistance = 370;
			this->splitContainer1->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(0, 0);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(370, 34);
			this->textBox1->TabIndex = 1;
			// 
			// treeView1
			// 
			this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView1->Location = System::Drawing::Point(0, 40);
			this->treeView1->Name = L"treeView1";
			this->treeView1->ShowNodeToolTips = true;
			this->treeView1->Size = System::Drawing::Size(370, 342);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::treeView1_AfterSelect);
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(0, 0);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(373, 34);
			this->textBox2->TabIndex = 2;
			// 
			// treeView2
			// 
			this->treeView2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView2->Location = System::Drawing::Point(0, 40);
			this->treeView2->Name = L"treeView2";
			this->treeView2->Size = System::Drawing::Size(373, 342);
			this->treeView2->TabIndex = 1;
			this->treeView2->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::treeView1_AfterSelect);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// loadHashesToolStripMenuItem
			// 
			this->loadHashesToolStripMenuItem->Name = L"loadHashesToolStripMenuItem";
			this->loadHashesToolStripMenuItem->Size = System::Drawing::Size(195, 26);
			this->loadHashesToolStripMenuItem->Text = L"Load hashes";
			this->loadHashesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::loadHashesToolStripMenuItem_Click);
			// 
			// sortToolStripMenuItem
			// 
			this->sortToolStripMenuItem->Name = L"sortToolStripMenuItem";
			this->sortToolStripMenuItem->Size = System::Drawing::Size(48, 24);
			this->sortToolStripMenuItem->Text = L"Sort";
			this->sortToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::sortToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 26);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(747, 410);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(5);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"IntegrityCheckerGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: String^ StdWstrToStr(std::wstring wstr)
		{
			String^ res=L"";
			for(unsigned int i=0; i<wstr.size(); i++)
			{
				res+=wstr[i];
			}
			return res;
		}
private: std::wstring StrToStdWstr(String^ str)
		{
			std::wstring res=L"";
			for(int i=0; i<str->Length; i++)
			{
				res+=str[i];
			}
			return res;
		}
private: bool hashSaved;
private: DataIntegrity::IntegrityChecker *iChecker;
private: void RefreshTree(TreeNodeCollection ^collection, SAL::TreeNode<DataIntegrity::FileInfo> *node)
{
			 TreeNode ^temp;
			 if (node->childs.Size())
			 {
				 temp = collection->Add("Folder", StdWstrToStr(node->value.filename));
				 for (uint i = 0; i < node->childs.Size(); i++)
				 {
					 RefreshTree(temp->Nodes, node->childs[i]);
				 }
			 }
			 else temp = collection->Add("File", StdWstrToStr(node->value.filename));
			 std::wstring wstrHash = node->value.hash.ToWstr();
			 temp->ToolTipText = gcnew System::String(wstrHash.c_str());
}
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e){
			 iChecker=new DataIntegrity::IntegrityChecker();
			 hashSaved=true;
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e){
			 if(!hashSaved)
			 {
				 System::Windows::Forms::DialogResult dr;
				 dr=MessageBox::Show(L"Сохранить эталон хэшей перед выходом", L"Closing...", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
				 if(dr==Windows::Forms::DialogResult::Yes)
				 {
					 saveAsStandardToolStripMenuItem_Click(this, nullptr);
				 }
				 else if(dr==Windows::Forms::DialogResult::Cancel){e->Cancel=true;}
			 }
		 }
private: System::Void openStandardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
			 if(openFileDialog1->ShowDialog()==Windows::Forms::DialogResult::OK)
			 {
				 if(!iChecker->LoadStandard(StrToStdWstr(openFileDialog1->FileName))) return;
				 hashSaved=false;
				 MessageBox::Show(L"Opened!", L"Opening...", MessageBoxButtons::OK, MessageBoxIcon::Information);
				 treeView1->Nodes->Clear();
				 RefreshTree(treeView1->Nodes, iChecker->GetStandardTreeRoot());
			 }
		 }
private: System::Void saveAsStandardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
			 if(saveFileDialog1->ShowDialog()==Windows::Forms::DialogResult::OK)
			 {
				 if(!iChecker->SaveStandard(StrToStdWstr(saveFileDialog1->FileName))) return;
				 hashSaved=true;
				 MessageBox::Show(L"Saved!", L"Saving...", MessageBoxButtons::OK, MessageBoxIcon::Information);
				 //treeView1->Nodes->Clear();
				 //RefreshTree(treeView1->Nodes, iChecker->GetStandardTreeRoot());
			 }
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
			 Close();
		 }
private: System::Void hashToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
			 if (folderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
			 {
				 if (iChecker->Hash(StrToStdWstr(folderBrowserDialog1->SelectedPath)))
				 {
					 hashSaved = false;
					 MessageBox::Show(L"Hashed!", L"Hashing...", MessageBoxButtons::OK, MessageBoxIcon::Information);
					 treeView2->Nodes->Clear();
					 RefreshTree(treeView2->Nodes, iChecker->GetTreeRoot());
				 }
				 else MessageBox::Show(L"Hashing failed!", L"Hashing...", MessageBoxButtons::OK, MessageBoxIcon::Error);
			 }
		 }
private: System::Void checkToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (iChecker->Check()) MessageBox::Show(L"Trees are equal!", L"Checking...", MessageBoxButtons::OK, MessageBoxIcon::Information);
			 else MessageBox::Show(L"Trees not equal!", L"Checking...", MessageBoxButtons::OK, MessageBoxIcon::Information);
		 }
private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 if (e == nullptr) return;
			 if ((TreeView^)sender == treeView1) textBox1->Text = e->Node->ToolTipText;
			 else textBox2->Text = e->Node->ToolTipText;
}
private: System::Void loadHashesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
			 {
				 if (!iChecker->LoadHashes(StrToStdWstr(openFileDialog1->FileName))) return;
				 MessageBox::Show(L"Opened!", L"Opening...", MessageBoxButtons::OK, MessageBoxIcon::Information);
				 treeView2->Nodes->Clear();
				 RefreshTree(treeView2->Nodes, iChecker->GetTreeRoot());
			 }
}
private: System::Void sortToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 iChecker->SortHashes();
			 treeView1->Nodes->Clear();
			 treeView2->Nodes->Clear();
			 RefreshTree(treeView1->Nodes, iChecker->GetStandardTreeRoot());
			 RefreshTree(treeView2->Nodes, iChecker->GetTreeRoot());
}
};
}

