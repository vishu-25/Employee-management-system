#include<iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

using namespace std;

int n,i,pos,r,j,flag=0,if_del=0;
fstream obj,f;
char filename[20];
class employee
{
 double salary;
 long int empid;
 char empname[30],des[30],address[100],pass[5],temp_ch;
 void read_details();
 void write_details();
 public :
 void getno()
 {
  cout<<"ENTER NO. OF EMPLOYEES\n";
  cin>>n;
 }
 void select();
 void insert_details();
 void display_details();
 void search();
 void dlt();
 void menu();
 void choice();
 void login();
 void append();
 void modify();
 void modifydata();
 int getid()
 {
  return empid;
 }
}o[100],s;
void employee :: menu()
{
 cout<<"FOR INSERTION ENTER 1\n";
 cout<<"FOR OPENING THE FILE ENTER 2\n";
 cout<<"FOR SEARCHING ENTER 3\n";
 cout<<"FOR DELETION ENTER 4\n";
 cout<<"FOR MODIFICATION ENTER 5\n";
 cout<<"FOR APPENDING ENTER 6\n";
 cout<<"ENTER YOUR CHOICE\n";
}
void employee :: login()
{
 cout<<"ENTER PASSWORD\n";
 for(i=0;i<6;i++)
 {
  temp_ch=getch();
  switch(temp_ch)
  {
   case '\r': temp_ch='\0';
	      break;
   case '\b': cout<<"\b \b";
	      i--;
	      break;
   default : cout<<"*";
  }
 }
 cout<<endl;
 if(strcmp(pass,"admin")!=0)
 {
  cout<<"ACCESS GRANTED\n";
  system("cls");
 }
 else
 {
  cout<<"ACCES DENIED\n";
  getch();
  exit(0);
 }
}
void employee :: insert_details()
{
 cout<<"ENTER ID\n";
 cin>>empid;
 cout<<"ENTER NAME\n";
 gets(empname);
 cout<<"ENTER DESIGNATION\n";
 gets(des);
 cout<<"ENTER ADDRESS\n";
 gets(address);
 cout<<"ENTER SALARY\n";
 cin>>salary;
 write_details();
}
void employee :: modifydata()
{
 cout<<"ENTER NAME\n";
 gets(empname);
 cout<<"ENTER DESIGNATION \n";
 gets(des);
 cout<<"ENTER ADDRESS \n";
 gets(address);
 cout<<"ENTER SALARY \n";
 cin>>salary;
}
void employee :: display_details()
{
 read_details();
 cout<<"ID :"<<empid<<"\n";
 cout<<"NAME :";
 puts(empname);
 cout<<"\n";
 cout<<"DESIGNATION :";
 puts(des);
 cout<<endl;
 cout<<"ADDRESS :";
 puts(address);
 cout<<"SALARY :"<<salary<<endl;
}
void employee:: write_details()
{
 obj.open (filename, ios::binary | ios::out);
 obj.write((char*)&o, sizeof(o));
 obj.close();
}
void employee :: select()
{
 int cho;
 cin>>cho;
 switch (cho)
 {
  case 1 : for( int i=0;i<n;i++)
	         o[i].insert_details();
	         break;
  case 2 : for(i=0;i<n;i++)
	         o[i].display_details();
	         break;
  case 3 : s.search();
	         break;
  case 4 : s.search();
	         if(flag==1)
	         {
	          s.dlt();
	          for(j=0; j<n; j++)
	          o[j].display_details();
	         }
	         else
	         cout<<"DELETION NOT POSSIBLE\n";
	         break;
  case 5 : s.modify();
           break;
  case 6 : s.append();
	         break;
  default : cout<<"WRONG CHOICE\n";
 }
}
void employee :: read_details()
{
 obj.open(filename, ios::binary | ios::in);
 obj.read((char*)&o, sizeof(o));
 obj.close();
}
void employee :: search()
{
 flag=0;
 int j;
 obj.open(filename, ios :: binary | ios::in);
 cout<<"ENTER ID to be deleted/modified/search\n";
 cin>>r;
 while(!obj.eof())
 {
  obj.read((char*)&o, sizeof(o));
  for(j=0; j<n; j++)
  {
   i++;
   if(r==o[j].getid())
   {
    pos=obj.tellg()-sizeof(o);
    flag=1;
    break;
   }
  }
}
 if(flag==1)
 cout<<"FOUND\n";
 else
 cout<<"ERR0R 404! NOT FOUND\n";
 obj.close();
 }
void employee :: dlt ()
{
 f.open(filename, ios::binary | ios::in);
 obj.open("temp", ios::binary | ios::out);
 f.seekg(0);
 while(f.read((char*)&s, sizeof(s)))
 {
  if(r!=getid())
  {
	 obj.write((char*)&s,sizeof(s));
	}
 }
 f.close();
 obj.close();
 remove(filename);
 rename("temp",filename);
 cout<<"DELETION SUCCESSFUL\n";
 n=n-1;
 }

void employee :: modify()
{
 f.open(filename,ios::in|ios::binary);
 int flag=0,r;
 cout<<"ENTER ID TO BE MODIFIED \n";
 cin>>r;
 while(f.read((char*)&s,sizeof(s)))
 {
  if(r==s.getid())
  {
   flag=1;
   break;
  }
 }
 f.close();
 if(flag==0)
 {
  cout<<"EMPLOYEE ID DOES NOT EXIST \n";
 }
 else
 {
  f.open(filename,ios::in|ios::binary);
  while(f.read((char*)&s,sizeof(s)))
  {
   if(r==s.getid())
   {
    f.seekg(f.tellg()-sizeof(s),ios::beg);
    s.modifydata();
    f.write((char*)&s,sizeof(s));
    break;
   }
  }
  f.close();
  cout<<"RECORD MODIFIED SUCCESSFULLY \n";
 }
}
void employee :: append()
{
 cout<<"ENTER NEW RECORD\n";
 obj.open(filename,ios::binary|ios::app);
 o[n].insert_details();
 n++;
 s.write_details();
}
void main()
{
 system("cls");
 s.login();
 char cont='y';
 cout<<"WELCOME TO EMPLOYEE MANAGEMENT\n";
 cout<<"ENTER FILE NAME\n";
 gets(filename);
 system("cls");
 s.getno();
 while(cont=='y')
 {
  s.menu();
  s.select();
 cout<<"TO EXIT PRESS n \n";
 cout<<"TO CONTINUE PRESS y \n";
 cin>>cont;
 if(cont!='y')
 exit(0);
 system("cls");

}
 getch(); }
