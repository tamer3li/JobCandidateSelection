#include <iostream>
#include <string>
#include <fstream>
#include "MANAGER_HR.h"


using namespace std;

void menu()
//body
{
	int x;       //to hold user choice
	do
	{
		system("cls");
		cout << "==========================================" << endl;
		cout << "|        Job candidate selection         |" << endl;
		cout << "==========================================" << endl;
		cout << "|                  menu                  |" << endl;
		cout << "==========================================" << endl;
		cout << "            1-manager(HR)                 " << endl;
		cout << "            2-applicant                   " << endl;
		cout << "            3-close                       " << endl;
		cout << "Enter your choice : ";
		cin >> x;
		system("cls");
	} while (!(x == 1 || x == 2 || x == 3));//data validation
	switch (x)
	{
	case 1:
	{manager(); } //manager menu
		break;
	case 2:
	{applicantmn(); }  //applicant menu
		break;
	case 3:
	{close(); }
		break;
	}
}


void manager()
{
	string passwT; //manager password
	int trial = 0; //password entry trials
	do {
		if (trial>2)
			menu();
		trial++;

		system("cls");
		cout << "\nYou have 3 trials ... trial #" << trial << "\n Enter manager password : ";
		cin >> passwT;

	} while (passwT != passw);  //passwrod validation
	readfile();
	int ch;
	if (!start){   //manager started application
		system("cls");
		cout << "\t 1- to open application\n \t2- to exit\n \tYour choice : ";  //prombt
		cin >> ch;

		switch (ch) {    //choice
		case 1:
			open = true;   //true when applicant opened vacancies
			cout << "\n Application is now open ... ";
			system("pause");
			specqual();  //call to "specify qualifications" function

			break;
		case 2:
			cout << "\n";
			system("pause");
			close(); //close function .. saves everything to files then exit
		}
	}
	else if (start) {    //applications started and qualifications specefied
		system("cls");
		if (done)  //true when all applicants applied
		{
			cout << "\n Applicants reached the maximum number needed.\n You can now select from candidates.."
				<< "\n To select from candidates select (3) in the next menu .. ";
			system("pause");
		}
		system("cls"); // full manager menu
		cout << "==========================================" << endl
			<< "           Manager/HR menu                   " << endl
			<< "==========================================" << endl
			<< "            1-start new application                " << endl
			<< "            2-check application status                   " << endl
			<< "            3-close vacancies and choose from candidates            " << endl
			<< "            4-view certain application (requires id)              " << endl
			<< "            5-delete certain application (requires id)               " << endl
			<< "            6-Back to main menu               " << endl
			<< "            7-change manager password               " << endl
			<< "            8-reset                " << endl
			<< "            9-EXIT               " << endl
			<< "\nEnter your choice : ";
		cin >> ch;
		switch (ch) {
		case 1: specqual();  //respecify qualifications canceling previous applications
			break;
		case 2:
			chck(); //checking applicants status
			break;
		case 3:
			endapp(); //closing vacancies and selecting candidates
			break;
		case 4: view(); //searches and views certain applicant profile
			break;
		case 5: delet(); //deletes certain application
			menu();
			break;
		case 6:
			menu(); //back to main menu
			break;
		case 7:
			system("cls");
			cout << "\n Enter new password .. no spaces allowed : "; //respecify password
			cin >> passw;
			cout << "\n New password is : " << passw << endl;
			system("pause");
			mangupdate();
			menu();
			break;
		case 8: reset(); //resets all values to default as means to restart the program
			break;
		case 9: close(); //saves all data to files then exits
			break;

		}
	}
}



void specqual() //specify qualifications body
//body
{
	system("cls");
	char ch = 'n'; //holds choice .. 'n' for default value when not used
	if (open && start){  // application open and qualifications specefied before
		cout << "\n starting a new application now will cancel old application\and delete all data\n"
			<< "are you sure you want to start a new application now ? Enter y for yes, any other letter for no : ";
		cin >> ch;
	}
	if (ch == 'y' || ch == 'Y' || !start) //if the user chooses to creat new specifications or it wasn't created before
	{

		cout << "\n Enter maximum applicant age : ";
		cin >> agmx;

		cout << "\n Enter minimum applicant age : ";
		cin >> agmn;

		cout << "\n Enter minimum applicant expiernce : ";
		cin >> minexpe;

		cout << "\n Enter minimum qualification : ";
		cin >> minqual;

		cout << "\n Enter maximum applicants number : ";
		cin >> max_appn;

		cout << "\n Enter applicants required : ";
		cin >> reqapp;

		start = true; //qualifications sepecefied
		app = new applicant[max_appn]; //dynamic allocations for array
		cur_appn = 0; //resets current applicants number to 0
		mangupdate(); //updates manager data file to the new specifications



		cout << "\n qualificatinos specefied .. ";
		system("pause");
		menu(); //back to main menu
	}
	else { //manager choose not to start new specifications
		menu();
	}
}

void chck() //checks status

{

	system("cls");
	if (!done){   //applicants reached maximum capacity or the manager chooses to select now
		system("cls");
		cout << "\n Checking application status ... \n"
			<< "\n Total applicants : " << cur_appn   //views application statistics including current applicants number
			<< "\n undergraduate applicant : " << qual[0]    //number of undergraduate applicants 
			<< "\n bachelor degree applicants : " << qual[1]     //number of bachelor degree applicants 
			<< "\n master degree applicants : " << qual[2]    //number of master degree applicants 
			<< "\n doctorate or higher : " << qual[3]          //number of doctorate degree applicants 
			<< "\n maximum expierence : " << maxexp        //maximum experience among applicants
			<< "\n minimum expierence : " << minexp;       //minimum experience among applicants

		cout << "\n";
		system("pause");
		menu();  //back to main menu
	}

	else if (done && start)  //applicants already chosen
	{
		acc_appn = acc_qual[0] + acc_qual[1] + acc_qual[2] + acc_qual[3]; //all accepted applicatns number acquired
		system("cls");                                                    //by summing accepted applicants 
		//of each qualification
		cout << "\n applicants were successfully chosen ...\n"
			<< "\n Checking application status ... \n"
			<< "\n Total applicants : " << cur_appn //all applied applicants
			<< "\n accepted applicants : " << acc_appn //accepted applicants number
			<< "\n undergraduate applicant accepted : " << acc_qual[0] //accepted undergraduates number
			<< "\n bachelor degree applicants accepted : " << acc_qual[1] //accepted bachelor degree number
			<< "\n master degree applicants accepted : " << acc_qual[2]  //accepted master degree number
			<< "\n doctorate or higher applicants accepted : " << acc_qual[3]  //accepted doctorate degree number
			<< "\n maximum expierence : " << maxexp //maximum accepted experience
			<< "\n minimum expierence : " << minexp << endl  //minimum accepted experience
			<< "\n Data exported to records at \"Accepted applicants.txt\"\n"; //file accepted applicants

		acc_appdata.open("Accepted applicants.txt", ios::out);

		for (int i = 0; i<acc_appn; i++){

			acc_appdata << "name : " << app[i].name << "-";
			acc_appdata << " - age : " << app[i].ag;
			acc_appdata << " - experience : " << app[i].expe;
			acc_appdata << " - qualification : " << app[i].qual;

			acc_appdata << " id : " << app[i].id << "\n";


		}
		acc_appdata.close();

		system("pause");
		menu();

	}

}





void pickapp() //pick applicants function
//this function arranges applicants and selects accepted applicants according to qualifications
{


	maxexp = app[0].expe;
	minexp = app[0].expe; //initial values
	if (cur_appn == 0)  //no one applied
	{
		system("cls");
		cout << "\n No applicants yet ";
		system("pause");
		manager();  //back to managers menu
	}
	else	if (cur_appn >= 2 * reqapp) //current applicants are twice the required applicants or more
	{


		for (int i = 0; i < cur_appn; i++)  //sorts candidates according to experience
		for (int j = i + 1; j < cur_appn; j++)
		{
			if (app[i].expe < app[j].expe)
				swap(app[i], app[j]);
			app[i].accpt = app[j].accpt = false; //sets every value to false no applicants accepted yet
			//markes applicants as rejected
		}

		for (int i = 0; i < cur_appn / 2; i++) //sorts the top half with the most experience according too qualification
		for (int j = i + 1; j < cur_appn / 2; j++)
		{
			if (app[i].qual < app[j].qual)
				swap(app[i], app[j]);


		}



		for (int i = 0; i < reqapp; i++) //selects required applicants with the most expierience and qualifications
		{
			app[i].accpt = true; //mareks applicants as accepted

			if (maxexp<app[i].expe)
				maxexp = app[i].expe; //selects maximum experience

			if (minexp>app[i].expe)
				minexp = app[i].expe; //selects minimum experience


			if (app[i].qual == 1)   //accepted qualifications statistics
				acc_qual[0]++;           //undergraduates

			else if (app[i].qual == 2)
				acc_qual[1]++;  //bachelor degree

			else	if (app[i].qual == 3)
				acc_qual[2]++;   //master degree

			else	if (app[i].qual == 4)
				acc_qual[3]++;  //doctorate


		}
	}
	else if (reqapp<cur_appn) {    //if current applicants is more than required applicants but not more than 
		//twice the current applicants
		for (int i = 0; i < cur_appn; i++)
		for (int j = i + 1; j < cur_appn; j++)
		{
			if (app[i].expe < app[j].expe)   //sorts applicants according to experience
				swap(app[i], app[j]);
			app[i].accpt = app[j].accpt = false; //markes them as not accepted

		}

		for (int i = 0; i < reqapp; i++)
		for (int j = i + 1; j < reqapp; j++)
		{
			if (app[i].qual < app[j].qual) ////sorts applicants according to qualifications
				swap(app[i], app[j]);


		}

		for (int i = 0; i < reqapp; i++)  //selects accepted applicants acoording to required applicants number
		{
			app[i].accpt = true; //markes them as accepted

			if (maxexp<app[i].expe)
				maxexp = app[i].expe; //selects maximum experience

			if (minexp>app[i].expe)
				minexp = app[i].expe; //selects minimum experience

			if (app[i].qual == 1)     //accepted qualifications statistics
				acc_qual[0]++;   //undergraduates

			else if (app[i].qual == 2)
				acc_qual[1]++;    //bachelor degree

			else	if (app[i].qual == 3)
				acc_qual[2]++;  //master degree

			else	if (app[i].qual == 4)
				acc_qual[3]++;  //doctorate

		}
	}

	else {  //if current applicants are less than the required applicants but manager forced selection
		for (int i = 0; i < cur_appn; i++)
		for (int j = i + 1; j < cur_appn; j++)  //sorts applicants by experience according to 
		{                                       // current applicants number
			if (app[i].expe < app[j].expe)
				swap(app[i], app[j]);

			app[i].accpt = app[j].accpt = false; //markes them as not accepted
		}

		for (int i = 0; i < cur_appn; i++)
		for (int j = i + 1; j < cur_appn; j++)  //sorts applicants by qualification
		{
			if (app[i].qual < app[j].qual)
				swap(app[i], app[j]);


		}

		for (int i = 0; i <cur_appn; i++)
		{
			app[i].accpt = true; //markes them as accepted

			if (maxexp<app[i].expe)
				maxexp = app[i].expe; //selects maximum experience

			if (minexp>app[i].expe)
				minexp = app[i].expe;//selects minimum experience

			if (app[i].qual == 1)//accepted qualifications statistics
				acc_qual[0]++; //undergraduates
			else if (app[i].qual == 2)
				acc_qual[1]++; //bachelor degree

			else	if (app[i].qual == 3)
				acc_qual[2]++;//master degree

			else	if (app[i].qual == 4)
				acc_qual[3]++;//doctorate

		}




	}
	update(); //updates reords 
	mangupdate(); //updates manager data
	chck(); //calls check function to check accepted applicants status


}

void endapp() //closes vacancies
//body
{
	system("cls");

	if (reqapp>cur_appn) //required applicants more than applied applicants
	{
		char ch;
		cout << "\n number of applicants hasn't yet reached the required number ..\n Are you sure you want to end application ?"
			<< "\n Enter Y to end application or any other letter to go back to main menu : ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y'){

			done = true; //closes application flag

			pickapp(); //calls pick applicants function
		}
		else
			menu(); //main menu

	}
	else {
		done = true; //if required applicants is more than current applicnats
		pickapp(); //pick applicants function
	}


}
void mangupdate() //update manager records

//body
{
	mangdata.open("mangdata.txt", ios::out); //opens manager data records

	mangdata << idc << " " << open << " " << start << " " << done << " " << max_appn << " " << cur_appn << " " << reqapp << " " << agmx << " " << agmn << " " << minexpe << " " << minqual << " " << passw;
	mangdata.close();

}