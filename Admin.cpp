/*
 * Admin.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: nzayatz14
 */

#include "Admin.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

Admin::Admin() {
	// TODO Auto-generated constructor stub
	userName = "admin";
}

Admin::~Admin() {
	// TODO Auto-generated destructor stub
}

void Admin::viewBank()
{
	bank.printBank();
}

void Admin::viewAccounts()
{
	//added system clear for aesthetic reasons -TDG
	system("clear");
	cout<<"\nTotal number of accounts: "<<bank.getTotalAccounts()<<endl<<endl;
}

void Admin::viewAccountInDetail(){
	// ask for the account number of the account that the user wishes to view
	//if it is a valid account number, open<accountNumber.txt> read in all of
	//the information and print it all. If its not print error and call printOptions

	//added system clear for aesthetic reasons -TDG
	system("clear");

	string user;
	cout<<"Enter User Name: ";
	cin>>user;

	ExternalAccount ext;
	bank.find(user, ext);
	Client c;
	Client *cPtr = &c;
	InternalAccount t[2];

	ext.getAccountHolder(cPtr);

	cout<<endl<<c.getUserName()<<endl;
	//changed below line, so Admin cannot see the user's password -TDG
	cout<<"*****"<<endl;
	cout<<"Account Number: "<<ext.getAccountNumber()<<endl<<endl;
	c.displayPersonalInformation();
	cout<<endl;

	ext.getInternalAccounts(t[0],t[1]);

	t[0].displayInternalAccount();
	cout<<endl;
	t[1].displayInternalAccount();
	cout<<endl;

}

void Admin::createAccount(){
	//ask for general information
	//create client object from entered info
	//call bank.create ExternalAccount(client,password) function for bank class

	//added system clear for aesthetic reasons -TDG
	system("clear");

	Client clie;

	string firstName;
	string lastName;
	string b;
	char g;
	string p;
	string a;
	string e;
	string un;
	string pass;
	string pass2;

	cout<<"Please enter first name of client."<< endl;
	cin>>firstName;


	cout<<"Please enter last name of client."<< endl;
	cin>>lastName;

	string n = firstName + " "+lastName;

	//boolean for checking if valid date -TDG
	bool isB = true;
	do{
	cout<<"Please enter birthday of client. (i.e. MM/DD/YYYY)"<< endl;
	cin>>b;
	cout << b << endl;
	if(b.length()!=10)//if date is not of correct length -TDG
		isB = false;
	string duplicate=b;
	//making substrings to check valid format and actual dates-TDG
	string bms=duplicate.substr(0,2);
	char * bm;
	bm = const_cast<char*>((b.substr(0,2)).c_str());
	string bds=duplicate.substr(3,2);
	char * bd;
	bd = const_cast<char*>((b.substr(3,2)).c_str());
	string bys=duplicate.substr(6,4);
	char * by;
	by = const_cast<char*>((b.substr(6,4)).c_str());

	//checking that all dates are numeric and nothing but numbers or slashes in full date-TDG
	for(int i = 0; i < b.length()-1; i++){
		if(!((b[i]>='0'&&b[i]<='9')||b[i]=='/')){

			isB=false;
		}
	}
	for(int i = 0; i < bms.length() -1; i++){
		if(!(bm[i]>='0'&&bm[i]<='9')){

			isB=false;
		}
	}
	for(int i = 0; i < bds.length() -1; i++){
		if(!(bd[i]>='0'&&bd[i]<='9')){

			isB=false;
		}
	}
	for(int i = 0; i < bys.length() -1; i++){
		if(!(by[i]>='0'&&by[i]<='9')){

			isB=false;
		}
	}

	//convert substrings to integers to check numerical validity-TDG
	int b1 = atoi(bms.c_str());
	int b2 = atoi(bds.c_str());
	int b3 = atoi(bys.c_str());

	//make sure that month is correct-TDG
	if(b1>12||b1<1){

		isB=false;
	}
	//make sure correct amount of days in corresponding months (except leap years)-TDG
	if(b1==1||b1==3||b1==5||b1==7||b1==8||b1==10||b1==12){
		if(b2>31||b2<1){

			isB=false;
		}
	}
	if(b1==4||b1==6||b1==9||b1==11){
		if(b2>30||b2<1){

			isB=false;
		}
	}
	if(b1==2){
		if(b2>29||b2<1){

				isB=false;
		}
	}
	//make sure year is reasonable-TDG
	if(b3>2013||b3<1850){

		isB=false;
	}
	}while(isB==false);
	
	//boolean to keep track of if gender variable is an M or an F-TDG
	bool isG = true;
	do{
	cout<<"Please enter gender of client. (M or F)"<< endl;
	cin>>g;
	//make sure gender variable is an M or an F-TDG
	if(toupper(g)!='M'&&toupper(g)!='F')
		isG = false;//If it is not, return false-TDG
	else
		isG = true;//...
	}while(isG==false);

	//boolean to keep track of if the phone number is valid-TDG
	bool isP = false;
	do{
	cout<<"Please enter in phone number of client including area code. (No spaces or dashes.)"<< endl;
	cin>>p;
	//check if phone number is of correct length (10 digits including area code)-TDG
	if(p.length()==10)
		isP=true;
	else
		isP=false;
	//make sure every digit is numeric, and phone number contains no invalid characters-TDG
	for(int i = 0; i < p.length()-1; i++){
		if(!(p[i]>='0'&&p[i]<='9'))
			isP=false;
	}
	}while(isP==false);
	
	getline(cin, a);

	cout<<"Please enter in address of client. (Do not press enter, type all on one line.)\n";
	getline(cin, a);

	cout<<"Please enter in email of client."<< endl;
	cin>>e;

	cout<<"Please enter in username of client."<< endl;
	cin>>un;

	cout<<"Please enter in a password."<< endl;
	cin>>pass;

	cout<<"Please re-enter password."<< endl;
	cin>>pass2;


	int compare = pass.compare(pass2);

	//Added password verification, requiring users to enter their desired passwords twice when the admin creates their account-TDG
	while(compare!=0)
	{
		cout<<"Passwords do not match. Please try again."<<endl;

		cout<<"Please enter in a password."<< endl;
		cin>>pass;

		cout<<"Please re-enter password."<< endl;
		cin>>pass2;

		compare = pass.compare(pass2);
	}


	clie.setPerson(n,b,g,p,a,e,un);

	bank.createExternalAccount(clie, pass);

	cout<<endl;
}

void Admin::changePassword()
{
	//ask for the userName of the account (check to make sure it exists and is the //correct account)
	//ask for new password and re-entry
	//if both entries match, find the externalAccount in the bank and set password in
	//the temporary account to the new password
	//set the externalAccount in the Bank equal to the temporary
	//call printOptions()

	//added system clear for aesthetic reasons -TDG
	system("clear");

	ExternalAccount temp;
	temp.setAccountNumber(-1);

	string un;
	string pass;
	string pass2;
	cout<<"Please enter the username of the account that you wish to change the password for:" << endl;
	cin>>un;

	bank.find(un, temp);

	if(temp.getAccountNumber()!=-1){
		cout<<"Please enter the new password of the account:" << endl;
		cin>>pass;

		cout<<"Please enter the password again:" << endl;
		cin>>pass2;

		if(pass.compare(pass2)==0){
			temp.setPassword(pass);
			bank.updateAccount(un, temp);
		}
	}
}

void Admin::deleteAccount(){
	//added system clear for aesthetic reasons -TDG
	system("clear");

	string un;
	cout<<"Please enter the user name of the account you wish to delete:" << endl;
	cin>>un;

	bank.deleteExternalAccount(un);
}

void Admin::printOptions()
{
	//print and number the capabilities of the administrator (create an account, delete
	//an account, view a specific account, or change the password to an account)
	//ask the option which the user wants to do (by number) and call the respective
	//function

	//added system clear for aesthetic reasons -TDG
	system("clear");

	int n = -1;
	do{
		cout<<"Here you can do: \n1. View bank  \n2. View the number of accounts  \n3. View an account in detail \n4. Create an account \n5. Delete an account \n6. Change password of account \n0. Logout"<<
				"\nEnter the number you wish to choose: ";

		try{
			cin>>n;
			if(!cin)
				throw 1;
		}
		catch(int a){
			n=-1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}
		switch(n){
		case 1:
			viewBank();
			break;
		case 2:
			viewAccounts();
			break;
		case 3:
			viewAccountInDetail();
			break;
		case 4:
			createAccount();
			break;
		case 5:
			deleteAccount();
			break;
		case 6:
			changePassword();
			break;
		case 0:
			break;
		default:
			cout<<"Please enter a valid number."<<endl;
		}
	}while (n!=0);

	logout();
}

void Admin::logout(){
	bank.logout();
}
