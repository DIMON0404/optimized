//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

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
//----------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
bool start = true;
if (Edit1->Text=="") start = false;
else
if (check(Edit1->Text)) start = false;

if (start && StrToInt(Edit1->Text) <= 20)
{
Form2->Show();
Form1->Hide();
Form2->Button1Click(Sender) ;
}
else
Application->MessageBox("Введіть коректні дані", "Помилка", MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
Application->MessageBox("V 1.0\n Автор Гайдучик Дмитро", "Про програму", MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
      Close();  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
Button1->Click();        
}
//---------------------------------------------------------------------------

