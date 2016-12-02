//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Math.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

int critik = 0;
int NHuman = 0;
//definition of variables
int t[20];
int x[20];
int y[20];
int z[100];
int aLine[100];
int aSize;
int human_hours;
int move[20];
void search(int point, int a);
bool optimize(int, int *, int);
int wid;
int p;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------


void __fastcall TForm3::Button1Click(TObject *Sender)
{
aSize = 0;

Chart3->Visible = false;
Chart4->Visible = false;

int a = Form2->k;
Chart1->LeftAxis->Maximum = a + 1;

for (int i =0; i < a; i++)
t[i]=StrToInt(Form2->Edits[i][0]->Text)/StrToInt(Form2->Edits[i][1]->Text);

//definition of series
for (int i = 0; i <= a; i ++)
{
TLineSeries *Series = new TLineSeries(Chart1);
Chart1->AddSeries(Series);
Chart1->Series[i]->Clear();
}

//make net
for (int i = -1; i < 31; i++)
Chart1->Series[a]->AddXY(i, 0, i, clRed);

Chart1->Series[a]->HorizAxis = aTopAxis;


//start paint
for (int i = 0; i < a; i++)
{
        int max = 0;
        x[i] = 0;

        for (int j = 0; j < i; j++)
                if (Form2->CheckBox[j][i]->Checked)
                {
                        if (max < y[j]) max = y[j];
                }
        x[i] += max;
        y[i] = x[i] + t[i];





        if (critik < y[i])
        critik = y[i];
} // end paint




TLineSeries *Seriess = new TLineSeries(Chart2);
Chart2->AddSeries(Seriess);
Chart2->Series[0]->Clear();

//second graph
for (int i = 0; i <= critik; i++)
{
        z[i] = 0;
        for (int j = 0; j < a; j++)
        {
                if (x[j] <= i && i < y[j]) z[i] += StrToInt(Form2->Edits[j][1]->Text);
        }
} //end second graph



//paint second graph
for (int i = 0; i < critik; i++)
{       if (i == 0)
                Chart2->Series[0]->AddXY(i, z[i], i, clRed);
        else
                if (z[i] != z[i-1])
                        Chart2->Series[0]->AddXY(i, z[i], i, clRed);
        Chart2->Series[0]->AddXY(i+1, z[i], i+1, clRed);
        if (z[i] > NHuman) NHuman = z[i];
} //end paint second graph

wid = 80 / sqrt(NHuman > critik ? NHuman : critik);

Chart1->TopAxis->Maximum = critik + 1;
Chart1->Width = ((critik + 1) * wid) * 1.025;




Chart2->Width = Chart1->Width;
Chart2->BottomAxis->Maximum = critik + 1;
Chart2->LeftAxis->Maximum = NHuman + 1;
if (Chart1->LeftAxis->Maximum >= 10 && Chart2->LeftAxis->Maximum < 10)
Chart2->LeftAxis->Maximum = 10;
if (Chart1->LeftAxis->Maximum < 10 && Chart2->LeftAxis->Maximum >= 10)
{
Chart1->LeftAxis->Maximum = 10;
Chart1->Height = 300 * 1.025;
}
else Chart1->Height = ((a + 1) * wid ) * 1.025;
Chart2->Height = (Chart2->LeftAxis->Maximum * wid ) * 1.025;
Chart2->Top = Chart1->Top+Chart1->Height;
Button2->Top = Chart2->Top+Chart2->Height + 16;


Form3->Width = Chart1->Width + 50;
Form3->Height = Button2->Top + 70;

for (int i = 0; i < a; i++)
        {
                if (y[i] == critik)
                {
                        aLine[aSize] = i;
                        aSize++;
                        search(i, a);
                }
        }

        for (int i = 0; i < a; i++)
                {
                TColor color = clRed;
                for (int j = 0; j < aSize; j++)
                if (aLine[j] == i) color = clBlue;

                Chart1->Series[i]->AddXY(x[i], i+1, x[i], color);
                Chart1->Series[i]->AddXY(y[i], i+1, y[i], color);

                Chart1->Series[i]->HorizAxis = aTopAxis;
                }
}
//---------------------------------------------------------------------------

void search(int point, int a)
{
        for (int i = 0; i < point; i++)
        {
        if (x[point]!=0)
                if (Form2->CheckBox[i][point]->Checked)
                {



                        if (x[point] == y[i])
                        {
                        bool checked = true;
                        for (int j = 0; j < aSize; j++)
                        if (aLine[j] == i) checked=false;
                        if (checked)
                        {
                                aLine[aSize] = i;
                                aSize++;
                        }
                                search(i, a);
                        }

                }
        }
}






void __fastcall TForm3::Button2Click(TObject *Sender)
{

 //definition variables
 int a = Form2->k;


 double p1;
 human_hours = 0;

 for (int i = 0; i < a; i++)
 human_hours += StrToInt(Form2->Edits[i][0]->Text);

 p1 = (double)human_hours / (double)critik;
 p = (int)p1;
 if ((double)p1 / (double)((int)p1) != 1.0) p++;

 if (p >= NHuman)
 {
  Application->MessageBox("�������� ����������� ���������", "������", MB_OK);
 }
 else
 {//start else
 Chart3->Visible = true;
Chart4->Visible = true;
Button2->Enabled = false;
Form3->N2->Enabled = false;
N5->Enabled = true;


 for (int i = 0; i < 20; i++)
 move[i] = 0;

 while (p < NHuman)
 {
  if (optimize(p, move, 0)) break;
 p++;
 }








Chart3->LeftAxis->Maximum = Chart1->LeftAxis->Maximum;

//definition of series
for (int i = 0; i <= a; i ++)
{
TLineSeries *Series = new TLineSeries(Chart3);
Chart3->AddSeries(Series);
Chart3->Series[i]->Clear();
}

//make net
for (int i = -1; i < 31; i++)
Chart3->Series[a]->AddXY(i, 0, i, clRed);

Chart3->Series[a]->HorizAxis = aTopAxis;


TLineSeries *Seriess = new TLineSeries(Chart4);
Chart4->AddSeries(Seriess);
Chart4->Series[0]->Clear();

//second graph
for (int i = 0; i <= critik; i++)
{
        z[i] = 0;
        for (int j = 0; j < a; j++)
        {
                if ((x[j]+move[j]) <= i && i < (y[j]+move[j])) z[i] += StrToInt(Form2->Edits[j][1]->Text);
        }
} //end second graph



//paint second graph
for (int i = 0; i < critik; i++)
{       if (i == 0)
                Chart4->Series[0]->AddXY(i, z[i], i, clRed);
        else
                if (z[i] != z[i-1])
                        Chart4->Series[0]->AddXY(i, z[i], i, clRed);
        Chart4->Series[0]->AddXY(i+1, z[i], i+1, clRed);
        if (z[i] > NHuman) NHuman = z[i];
} //end paint second graph




Chart3->TopAxis->Maximum = Chart1->TopAxis->Maximum;
Chart3->Width = Chart1->Width;
Chart3->Top = Chart1->Top;



Chart4->Width = Chart1->Width;
Chart4->BottomAxis->Maximum = Chart2->BottomAxis->Maximum;
Chart4->LeftAxis->Maximum = Chart2->LeftAxis->Maximum;
Chart3->LeftAxis->Maximum = Chart1->LeftAxis->Maximum;
Chart3->Height = Chart1->Height;
Chart4->Height = Chart2->Height;
Chart4->Top = Chart2->Top;
Chart3->Left=Chart1->Width;
Chart4->Left=Chart3->Left;
Form3->Width = Chart3->Width*2 + 50;
Form3->Height = Button2->Top + 70;


        for (int i = 0; i < a; i++)
                {
                TColor color = clRed;
                for (int j = 0; j < aSize; j++)
                if (aLine[j] == i) color = clBlue;
                if (move[i] > 0) color = clMaroon;
                Chart3->Series[i]->AddXY(x[i]+move[i], i+1, x[i]+move[i], color);
                Chart3->Series[i]->AddXY(y[i]+move[i], i+1, y[i]+move[i], color);

                Chart3->Series[i]->HorizAxis = aTopAxis;
                }
                }//end else
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->Close();
}
//---------------------------------------------------------------------------

bool calc(int a, int p, int *move, int num)
{
 int sum = 0;
 for (int i = 0; i < a; i++)
  if ((x[i] + move[i]) <= num && num < (y[i] + move[i]))
  sum += StrToInt(Form2->Edits[i][1]->Text);
  return sum <= p;
}

bool moving(int a, int start, int *mov)
{
for (int i = 0; i < aSize; i++)
if (aLine[i] == start) return false;
 int move[20];
 for (int i = 0; i < 20; i++)
 move[i] = mov[i];
 if ((y[start] + move[start] + 1) <= critik)
 {
  move[start]++;
  for (int i = start + 1; i < a; i++)
  {
    if (Form2->CheckBox[start][i]->Checked)
    {
     if (y[start] + move[start] > x[i])
     if (moving(a, i ,move))
     {
      for (int k = 0; k < 20; k++)
      mov[k] = move[k];
      return true;
     }
     else return false;
    }
  }
 }
 else return false;
 for (int k = 0; k < 20; k++)
      mov[k] = move[k];
 return true;
}



bool optimize(int p, int *mov, int start)
{
if (start == critik) return true;
 int a = Form2->k;
 int move[20];
 int fmove[20];
 for (int i = 0; i < 20; i++)
 {
  move[i] = mov[i];
  fmove[i] = mov[i];
 }

      if (calc(a, p, move, start))
      if (optimize(p, move, start + 1))
      {
       for (int i = 0; i < 20; i++)
       mov[i] = move[i];
       return true;
      }
 for (int i = start; i < critik - 1; i++)
 {//1
  for (int j = 0; j < a; j++)
  {//2
    if (moving(a, j, fmove))
    {//4
     for (int k = 0; k < 20; k++)
     move[k] = fmove[k];

     if (calc(a, p, move, i))
      if (optimize(p, move, start + 1))
      {
              for (int i = 0; i < 20; i++)
       mov[i] = move[i];
       return true;
      }
    }//4
   }//2
  }//1
  return false;
}

void __fastcall TForm3::N4Click(TObject *Sender)
{
Application->MessageBox("V 1.0\n ����� �������� ������", "��� ��������", MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N3Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N2Click(TObject *Sender)
{
 Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N5Click(TObject *Sender)
{
TMemo *m = Form4->Memo1;
AnsiString reserv, moved, maxx;

maxx = "ʳ������ ���������� �� ����������: " + IntToStr(NHuman) + ". ʳ������ ���������� ���� ����������: " + IntToStr(p) + '.';
m->Lines->Add(maxx);

reserv = "���������� ������� �������� �� ������� ��������, �� ����� ������ � ���:";
bool point = false;
for (int i = 0, k = Form2->k; i < k; i++)
{
bool add = true;
for (int j = 0; j < aSize; j++)
if (aLine[j] == i)
{
 add = false;
 break;
}
if (add)
{
if (point) reserv += ',';
else point = true;
reserv += " " + IntToStr(i + 1);
}
}
reserv += '.';
m->Lines->Add(reserv);

moved = "���������� ��������� ����������� ";
point = false;
for (int i = 0; i < 20; i++)
if (move[i] > 0)
{
 if (point) moved += ',';
 else point = true;

 moved += " " + IntToStr(i + 1) + " �������� �� " + IntToStr(move[i]);
 if (move[i] == 1) moved += " ����";
 else
 if (move[i] < 5) moved += " ���";
 else moved += " ����";
}
moved += '.';

m->Lines->Add(moved);


Form4->Show();
Form3->Enabled = false;
}
//---------------------------------------------------------------------------


