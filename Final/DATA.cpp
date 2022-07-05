#include "DATA.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


string passw = "admin"; // creating apassword for manager_hr 
fstream appdata, acc_appdata, mangdata; // files i will use to keep my data like (applicant information,manager marked selection)
applicant *app, temp;//dynamic allocation for data
bool start = 0, read = 0, open = 0;//false value
bool done = 0, del = 0;//flags for certain stages in program
int idc = 0, appM, agmx, agmn, minexpe, minqual;//declare number of applicant,the max age,the min age,the experince of applicant,
int  acc_appn, cur_appn = 0, max_appn, reqapp;// current applicant number,the max number to stop , number of applicants required
int maxexp, minexp;//holds the max and min qualifactins
int acc_qual[4] = { 0 }; //an array use in the operation when show accpeted applicants
int qual[4] = { 0 }; //number of applicants with each qualfications


void readfile() //reads records to optain las status of the program

{

	mangdata.open("mangdata.txt.", ios::in); //open manager data records
	mangdata >> idc >> open >> start >> done >> max_appn >> cur_appn >> reqapp >> agmx >> agmn >> minexpe >> minqual >> passw;
	mangdata.close();//read manager data from file 
	if (start || done) //if application is started at all
	{
		app = new applicant[max_appn];// dynamic allocation
		appdata.open("applicants.txt", ios::in); //reads applicants data in array
		if (appdata.eof()){ // if no data in file
			cout << "\n No applicants applied yet ..  ";
			manager();// back to manager menu
		}
		for (int i = 0; i<cur_appn; i++){ //reads every applicant so far from menu
			getline(appdata, app[i].name, '-'); //reads name till "-"
			appdata >> app[i].ag; //age
			appdata >> app[i].expe; //experience
			appdata >> app[i].qual; //qualification
			appdata >> app[i].id;// show data stored on it 

			if (appdata.eof())  break;
		}
		read = true; //true when data is read
		appdata.close();// close file 
	}//end if

}



void view(int i)
//body
{
	system("cls");    /// clear system ////


	int indx; //holds index
	if (i == -1){ //takes id from the user if no id argument is passed to the function 
		cout << "\n Enter id : ";
		cin >> i; //takes id
	}
	for (int y = 0; y <= cur_appn; y++) //searches for id
	{
		if (y == cur_appn) //if id not found by the end of loop
		{
			cout << "\n view id not found .. ";
			system("pause");
			applicantmn();
			break;
		}
		else if (i == app[y].id) //id found
		{
			i = app[y].id;
			indx = y; //takes index in int indx
			break;
		}

	}
	system("cls");
	if (start&&done&&app[i].accpt) //if chosen and accepted
		cout << "applicant accepted... \n";
	else if (start&&done && !(app[i].accpt)) //if chosen and not accepted
		cout << "applicant not accepted... \n";
	else if (!(done)) //if not hosen yet
		cout << "applicants not chosen yet... \n";

	cout << "\n id : " << i
		<< "\n name : " << app[indx].name
		<< "\n age : " << app[indx].ag
		<< "\n qualification : ";



	switch (app[indx].qual)//outputs qualification
	{
	case 1: cout << "undergraduate";
		break;
	case 2: cout << "bachelor degree";
		break;
	case 3: cout << "master degree";
		break;
	case 4: cout << "doctorate";
	}
	cout << "\n expiernce : " << app[indx].expe << " years\n";
	system("pause");
	if (!del) //if the program isn't directed here form delete function
		menu(); //main menu
	del = false; //restes delete





}







void viewtemp() //simply views data in temp variable to the user
//body
{
	cout << "\n id : " << temp.id
		<< "\n name : " << temp.name
		<< "\n age : " << temp.ag
		<< "\n qualification : ";
	switch (temp.qual)
	{
	case 1: cout << "undergraduate";
		break;
	case 2: cout << "bachelor degree";
		break;
	case 3: cout << "master degree";
		break;
	case 4: cout << "doctorate";
	}
	cout << "\n expiernce : " << temp.expe << " years";// end switch
}// used to read data from applicant and store it







void delet() //deletes certain application
//body
{
	system("cls");// clear system



	del = true;  //sets delete to true so the view function doesn't call main menu
	int indx;
	cout << "\n Enter applicant id to delete : ";
	int i;
	cin >> i; //takes id to delete
	system("cls");//clear screen
	for (int y = 0; y <= cur_appn; y++) //searches for id
	{
		if (y == cur_appn) //if id not found by the end of loop
		{
			cout << "\n delet id not found .. ";
			system("pause");
			menu();
			break;
		}
		else if (i == app[y].id) //if id found
		{
			cout << cur_appn;
			indx = y;
			break;
		}

	}
	view(i); //passes id to view function to view applicant profile
	cout << "\n Are You sure you want to DELETE this application ? enter \"Y\" to delete : ";
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') //choice selection
	{
		for (int x = indx; x < cur_appn - 1 /*current applicant -1 because app[x+1]*/; x++)
		{
			app[x] = app[x + 1];

		}
		cur_appn--;
		update(); //updates records after delete
		cout << "\n Application deleted .. ";
		system("pause");
		menu(); //calls main menu




	}

}//// afunction used to delete applications and the id for the applicant and display that





void update() //updates records
{
	appdata.open("applicants.txt", ios::out); //opens applicants data
	for (int i = 0; i < cur_appn; i++){
		//writes applicant data to file
		appdata << app[i].name << "-";      //name
		appdata << app[i].ag << " ";        //age
		appdata << app[i].expe << " ";      //experience
		appdata << app[i].qual << " ";      //qualifications
		appdata << app[i].id << "\n";       //id
	}
	if (done){ //applicants are already chosen
		for (int i = 0; i < acc_appn; i++){ //writes accepted applicants data to file
			acc_appdata << "name : " << app[i].name << "-";
			acc_appdata << " - age : " << app[i].ag;
			acc_appdata << " - experience : " << app[i].expe;
			acc_appdata << " - qualification : " << app[i].qual;
			acc_appdata << app[i].id << "\n";
		}
	}
	else { //if applicants not yet chosen just writes the first few applicants tp accepted applicants records
		for (int i = 0; i < reqapp; i++){

			acc_appdata << "name : " << app[i].name << "-";
			acc_appdata << " - age : " << app[i].ag;
			acc_appdata << " - experience : " << app[i].expe;
			acc_appdata << " - qualification : " << app[i].qual;
			acc_appdata << app[i].id << "\n";
		}
	}
	appdata.close(); //closes files
	acc_appdata.close();
	cout << "\nRcords updated  ";
	system("pause"); //used to prombe "press any key to continue" and hold the screen
}// afunction used to update data for applicants 

void close() //saves data to records and closes program
//body
{
	update(); //calls update function to save applicants data
	mangupdate(); //calls mangupdate function to save manager data
	delete[] app; //delets dynamically allocated array
	exit(0); //exits program
}// afunction use to close the application when i finished 



void reset() //resets all program data to default
//body
{
	string passwT; //requires password
	int trial = 0; //password trials counter
	do {
		if (trial>2) //trial validation
			menu();
		trial++;

		system("cls");
		cout << "\nYou have 3 trials ... trial #" << trial << "\n Enter manager password : ";
		cin >> passwT;

	} while (passwT != passw); //password validation

	appdata.open("applicants.txt", ios::out); //opens all records using ios::out to clear the data
	acc_appdata.open("Accepted applicants.txt", ios::out);
	mangdata.open("mangdata.txt", ios::out);

	appdata.close();
	acc_appdata.close(); //closes all records as they're empty now
	mangdata.close();

	open = start = done = false; //bool data set to false  
	max_appn = cur_appn = reqapp = agmx = agmn = minexpe = minqual = 0; //qulifications set to zero
	passw = "admin"; //password set back to default "admin"

	cout << "\n All data reset .. ";
	system("pause");
	menu(); //back to main menu

}//afunction used to delete all data for applicants and start from beginning