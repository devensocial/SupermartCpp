#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
class shop
{
	int id, price;
	char item_name[20];

public:

	void item_add()                       //This is to be saved in the file "item"
	{
			cout<<"\nENTER ITEM ID: ";
			cin>>id;
			cout<<"\nENTER ITEM NAME: ";
			gets(item_name);
			cout<<"\nENTER ITEM PRICE: ";
			cin>>price;
	}

	void show_item()
	{
		cout<<"\n\n\nITEM ID : "<<id;
		cout<<"\tITEM NAME : ";
		puts(item_name);
		cout<<"\t\t\t\t\t\t\tITEM PRICE : "<<price;
		cout<<"\n_________________________________"
		<<"_______________________________________\n";
	}

	int id1()
	{
		return id;
	}

	int price1()
	{
		return price;
	}
};

class cart
{
	long totcost;
public:
	cart()
	{
		totcost=0;
	}
	void bill(long n,int quan)
	{
		totcost=totcost+n*quan;
	}
	void currbill()
	{
		cout<<"\nCURRENT BILL AMOUNT: "<<totcost;
	}
	void showbill()
	{
		if(totcost>=10000)
		{
			cout<<"\n\n\n\tYOUR TOTAL BILL AMOUNT AFTER DISCOUNT: "<<(totcost*8)/10;
		}
		else
      	cout<<"\n\n\n\tYOUR TOTAL BILL AMOUNT: "<<totcost;
	}
};

void display_list()
	{
		shop fr;
		ifstream datafile;
		datafile.open("A.dat",ios::binary);
		while(datafile.read((char*)&fr,sizeof(fr)))
		{
			fr.show_item();
		}datafile.close();
	}

void write_data()
{
	shop obj;
	ofstream fp2;
	fp2.open("A.dat",ios::binary|ios::app);
	char say;
	qq:
	cout<<"\nDO YOU WANT TO ENTER A RECORD? (y/n) : ";
	cin>>say;
	if(say=='y'||say=='Y')
	{
		obj.item_add();
		fp2.write((char*)&obj,sizeof(obj));

		goto qq;
	}fp2.close();
}

void search(int n)
{
	shop obj;
	ifstream fp1;
	fp1.open("A.dat",ios::binary);
	while(fp1.read((char*)&obj,sizeof(obj)))
	{
		if(obj.id1()==n)
		{
			obj.show_item();
		}
	}
}

int searchret(int n)
{
	shop obj;
	ifstream fp1;
	fp1.open("A.dat",ios::binary);
	while(fp1.read((char*)&obj,sizeof(obj)))
	{
		if(obj.id1()==n)
		{
			return obj.price1();
		}
	}
}

void delete_item(int n)
{
	shop obj;
	ifstream fp1;
	fp1.open("A.dat",ios::binary);
	ofstream fp2;
	fp2.open("temp.dat",ios::out|ios::binary);
	while(fp1.read((char*)&obj,sizeof(obj)))
	{
		if(n!=obj.id1())
			fp2.write((char*)&obj,sizeof(obj));
	}
	fp1.close();
	fp2.close();
	remove("A.dat");
	rename("temp.dat","A.dat");
}

void modify_item(int n)
{
	shop obj;
	fstream fp;
	fp.open("A.dat",ios::binary|ios::in|ios::out); 														//Error in handout 1 "ios:in;"
	int found=0;
	while(fp.read((char*)&obj,sizeof(obj)))
	{
		if(obj.id1()==n)
		{
		{
			obj.show_item();
			obj.item_add();
			int s=sizeof(obj);
			fp.seekp(-s,ios::cur);
			fp.write((char*)&obj,sizeof(obj));
			found++;
		}
		fp.close();
		}
		else
		{
			cout<<"\nSORRY!!:(\nNO SUCH ITEM FOUND!";
		}
	}
}


void main()
{
	shop a;
	cart b;

	int ans1,mid,quantity;
	char ans,ans2,ans3,ans4,pass[10];

	cout<<"++++++++++++++++++++++++++++++++++++++++++\n"
		 <<"ENTER PASSWORD OR CONTINUE AS A CUSTOMER(C)";
	{
		//char m[10];
		cout<<"\n\tPASSWORD: ";
		for(int qw=0;qw<10;qw++)
		{
			char chq = getch();
			if (chq == '\r')
				break;
			else
				cout<<"*";
			pass[qw] = chq;
		}
	pass[qw] = '\0';
	}
	cout<<"\n++++++++++++++++++++++++++++++++++++++++++";
	if (strcmp(pass,"deven")==0||strcmp(pass,"DEVEN")==0)
	{
		cout<<"\n\tACCESS GRANTED!\n";
		do
		{
			ee:
			cout<<"\n\t______________________________";
			cout<<"\n\tWHAT WOULD YOU LIKE TO DO?\n";
			cout<<"\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout<<"\t1. Add item to list \n\t2. Review the list\n"
				 <<"\t3. Delete item from list\n\t4. Search and modify\n"
				 <<"\t5. Exit and open the customer menu\n";
			cout<<"\n\tYOUR CHOICE: ";
			cin>>ans1;
			if(ans1==1)
			{
				clrscr();
				cout<<"\n\tMENU FOR ADDING RECORD\n";
				write_data();		//Add item
				goto ee;
			}
			else if(ans1==2)
			{
				clrscr();
				cout<<"\n\tMENU FOR DISPLAYING RECORD\n";
				display_list();		//Print list
				goto ee;
			}
			else  if(ans1==3)
			{
				ans4='y';
				while(ans4=='y'||ans4=='Y')
				{
					clrscr();
					cout<<"\n\tMENU FOR DELETING RECORD\n";
					cout<<"\nEnter the item(ID) to be deleted! ";
					cin>>mid;
					delete_item(mid);     //delete item
					cout<<"\nDo you want to delete more items? (y/n) :";
					cin>>ans4;
				}
				goto ee;
			}
			else if(ans1==4)
			{
				clrscr();
				cout<<"\n\tMENU FOR SEARCHING AND EDITING RECORD\n";
				cout<<"\nEnter the item(ID) to be searched!";
				cin>>mid;
				modify_item(mid);
				goto ee;
			}
		}while(ans1!=5);
		cout<<"\n\n......PROCEEDING TO CUSTOMER MENU\n";
		goto rr;
	}
	else
	{
	  clrscr();
	  rr:
	  cout<<"\t\t    ############---Welcome---############";
	  cout<<"\n\t\t\t    DEVEN'S GENERAL STORE";
	  cout<<"\n";
	  cout<<"\n\n\t\t\tWhat would you like to buy?";
	  cout<<"\n\n\t\t\t     Here's the list";
     ans2='Y';
	  while(ans2=='y'||ans2=='Y')
	  {
		display_list();
		cout<<"\n\nEnter the item code you want to buy: ";
		cin>>mid;
		clrscr();
		cout<<"\n\nDetails of requested item : "<<endl;
		search(mid);
		cout<<"\n\nAdd item to cart? (y/n) : ";
		cin>>ans3;
		if (ans3=='y'||ans3=='Y')
		{
			cout<<"\nENTER QUANTITY: ";
			cin>>quantity;
			long dota=searchret(mid);
			b.bill(dota,quantity);
			cout<<"\nITEM ADDED TO CART!\n";
			b.currbill();
			cout<<"\n\n\t\tOFFER!!\nSHOP FOR Rs.10000 and more and get 20% off!!\n\n";
		}
		cout<<"\nDo you want to add more items? (y/n) :    ";
		cin>>ans2;
	  }
	  clrscr();
	  cout<<"\n\n\t    ############---THANKS FOR SHOPPING!!---############";
	  b.showbill();
	}
}
