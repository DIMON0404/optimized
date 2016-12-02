//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
bool check(AnsiString a);


//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
        k = StrToFloat(Form1->Edit1->Text);
for (int i=0; i<k; i++)
{
        for (int j=0; j<k; j++)
        {
                CheckBox[i][j] = new TCheckBox(this);
                CheckBox[i][j]->Parent = this;
                CheckBox[i][j]->Name = "CheckBoxes"+AnsiString(i)+"_"+AnsiString(j);
                CheckBox[i][j]->Height = 20;
                CheckBox[i][j]->Width = 20;
                CheckBox[i][j]->Left = 50 + j * (10 + CheckBox[i][j]->Width);
                CheckBox[i][j]->Top = 50 + i * (10 + CheckBox[i][j]->Height);
                CheckBox[i][j]->Caption="";
                if (i>=j) CheckBox[i][j]->Enabled = false;
        }
        Edit[i][0] = new TEdit(this);
        Edit[i][0]->Parent = this;
        Edit[i][0]->Name = "Edit"+AnsiString(i)+"_"+AnsiString(0);
        Edit[i][0]->AutoSize=false;
        Edit[i][0]->Height = 20;
        Edit[i][0]->Width = 20;
        Edit[i][0]->Left = 20;
        Edit[i][0]->Top = 50 + i * (10 + Edit[i][0]->Height);
        Edit[i][0]->Text = AnsiString(i+1);
        Edit[i][0]->Enabled=false;

        Edit[i][1] = new TEdit(this);
        Edit[i][1]->Parent = this;
        Edit[i][1]->Name = "Edit"+AnsiString(i)+"_"+AnsiString(1);
        Edit[i][1]->AutoSize=false;
        Edit[i][1]->Height = 20;
        Edit[i][1]->Width = 20;
        Edit[i][1]->Left = 50 + i * (10 + Edit[i][1]->Height);
        Edit[i][1]->Top = 20;
        Edit[i][1]->Text=AnsiString(i+1);
        Edit[i][1]->Enabled=false;

        Edits[i][0] = new TEdit(this);
        Edits[i][0]->Parent = this;
        Edits[i][0]->Name = "Edit"+AnsiString(i)+"_"+AnsiString(2);
        Edits[i][0]->AutoSize=false;
        Edits[i][0]->Height = 20;
        Edits[i][0]->Width = 30;
        Edits[i][0]->Left = 50 + k * (10 + CheckBox[0][0]->Width);
        Edits[i][0]->Top = Edit[i][0]->Top;
        Edits[i][0]->Text = "";
        Edits[i][0]->Enabled=true;

        Edits[i][1] = new TEdit(this);
        Edits[i][1]->Parent = this;
        Edits[i][1]->Name = "Edit"+AnsiString(i)+"_"+AnsiString(3);
        Edits[i][1]->AutoSize=false;
        Edits[i][1]->Height = 20;
        Edits[i][1]->Width = 30;
        Edits[i][1]->Left = Edits[i][0]->Left+40;
        Edits[i][1]->Top = Edit[i][0]->Top;
        Edits[i][1]->Text="";
        Edits[i][1]->Enabled=true;

}
        Edits[k][0] = new TEdit(this);
        Edits[k][0]->Parent = this;
        Edits[k][0]->Name = "Edit"+AnsiString(k)+"_"+AnsiString(2);
        Edits[k][0]->AutoSize=false;
        Edits[k][0]->Height = 20;
        Edits[k][0]->Width = 30;
        Edits[k][0]->Left = 50 + k * (10 + CheckBox[0][0]->Width);
        Edits[k][0]->Top = 20;
        Edits[k][0]->Text = "H";
        Edits[k][0]->Enabled=false;

        Edits[k][1] = new TEdit(this);
        Edits[k][1]->Parent = this;
        Edits[k][1]->Name = "Edit"+AnsiString(k)+"_"+AnsiString(3);
        Edits[k][1]->AutoSize=false;
        Edits[k][1]->Height = 20;
        Edits[k][1]->Width = 30;
        Edits[k][1]->Left = Edits[k-1][0]->Left+40;
        Edits[k][1]->Top = 20;
        Edits[k][1]->Text="P";
        Edits[k][1]->Enabled=false;

Form2->Width = Edits[k-1][1]->Left + 50;
Form2->BorderStyle=bsSingle;
Start->Top = Edit[k-1][0]->Top + 30;
Start->Left = 20;
Form2->Height = Start->Top + 70;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::StartClick(TObject *Sender)
{
bool start = true;
for (int i = 0; i < k; i++)
{
if (Edits[i][0]->Text=="") start = false;
else
if (check(Edits[i][0]->Text)) start = false;

if (Edits[i][1]->Text=="") start = false;
else
if (check(Edits[i][1]->Text)) start = false;

if (Edits[i][0]->Text < Edits[i][1]->Text) start = false;
}

if (start)
{
Form3->Show();
Form3->Button1Click(Sender);
Form2->Hide();
}
else
Application->MessageBox("������ �������� ����", "�������", MB_ICONWARNING);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{

Form1->Close();
}
//---------------------------------------------------------------------------

bool check(AnsiString a)
{
Char* b = a.c_str();
if (b[0]<49 || b[0]>57) return true;
for (int i = 0, l = a.Length(); i < l; i++)
if (b[i]<48 || b[i]>57)
{
        return true;
}
return false;
}
void __fastcall TForm2::Form1N4Click(TObject *Sender)
{
Start->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N3Click(TObject *Sender)
{
Application->MessageBox("V 1.0\n ����� �������� ������", "��� ��������", MB_OK);        
}
//---------------------------------------------------------------------------
