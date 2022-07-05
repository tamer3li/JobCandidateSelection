#include <iostream>
#include <string>
#include <fstream>
#include "applicant.h"// include header file
using namespace std;

void applicantmn()
//body
{

	int ch;
	do {//applicants menu
		system("cls");

		cout << "==========================================" << endl
			<< "            applicantmns menu                   " << endl
			<< "==========================================" << endl
			<< "            1-apply                 " << endl
			<< "            2-inquire about your status (id required)                   " << endl
			<< "            3-cancel application               " << endl
			<< "            4-edit application               " << endl
			<< "            5-back to main menu              " << endl
			<< "            6-EXIT               " << endl
			<< "Enter your choice : ";
		cin >> ch;
	} while (!(ch>0 && ch<7)); //data validation
	switch (ch)
	{//switch
	case 1: fillapp(); //fill applicant function
		break;
	case 2: view(); //view and search function
		break;
	case 3:
		delet(); //delets applicants
		applicantmn(); //calls applicant menu
		break;
	case 4: edit(); //calls edit menu
		break;
	case 5: menu(); //main menu
		break;
	case 6: close(); //saves all data and closes program
	}
	//end switch
}//end function


void fillapp() //allows applicants to fill their application
//body
{
	if (!start)
	{
		system("cls");
		cout << "application are not opened yet ..... \n wait until manager open it to fill applicantion... \n";
		system("pause");
		menu();
	}
	else{
		system("cls");//clear system
		if (cur_appn >= max_appn)  //maximum applicants reached
		{
			cout << "\n sorry .. no more applicantmns needed .. \n";
			system("pause");
			applicantmn();
		}
		else {  //takes all applicant data to a temp structure
			//applicant menu
			cout << "==========================================\n";
			cout << "        fill your application             \n";
			cout << "==========================================\n";
			cout << "\t1.enter your name : ";
			cin >> temp.name;
			cout << "\n\t2.your age : ";
			cin >> temp.ag;
			if (temp.ag > agmx || temp.ag < agmn){ //validates age boundaries
				cout << "\n Sorry .. you don't meet the job requirements regarding age\n"
					<< " .. application denied !\n ";
				system("pause");
				menu();
			}
			do {
				cout << "\n1-undergraduate  -  2-bachelor  -  3-master degree  -  4-doctorate"
					<< "\n\t3.your qualifications : "; //prombts applicant to choose qualifications
				cin >> temp.qual;
				switch (temp.qual) {

				case 1: qual[0]++; //undergraduate
					break;
				case 2: qual[1]++; //bachelor
					break;
				case 3: qual[2]++; //master degree
					break;
				case 4: qual[3]++; //doctorate
					break;




				}
			} while (!(temp.qual > 0 && temp.qual < 5));
			if (temp.qual < minqual){  //validates qualification boundaries
				cout << "\n Sorry .. you don't meet the job requirements regarding qualification\n"
					<< " .. application denied !\n ";
				system("pause");


				applicantmn(); //applicant menu
			}
			cout << "\t4.years of experience : ";
			cin >> temp.expe;
			if (temp.expe < minexpe){ //validates experience boundaries
				cout << "\n Sorry .. you don't meet the job requirements regarding experience\n"
					<< " .. application denied !\n";
				system("pause");
				applicantmn(); //call
			}

			temp.id = idc; //sets applicant id
			app[cur_appn] = temp; //saves id to main array

			cur_appn++; //increments currebt applicant number
			if (cur_appn == max_appn)
				done = true; //done is true when maximum applicants reached
			update();//call
			mangupdate();// call
			cout << "\nApplication received successfully, thanks for applying ..\n please keep this id : " << idc
				<< "\n";
			idc++;
			system("pause");
			applicantmn();//call

		}
	}
}


void edit() //edit application function 
//body
{
	int EDIT; //integer to take data for validation before writing

	system("cls");
	if (!read){
		cout << "\n Error .. data not acquired ... press any key to exit .. ";
		system("pause");
		close();
	}

	else {
		int indx; //integer to hold index to the application
		cout << "\n Enter your application id : ";
		int i, x; // i to hold id, x for choice in the edit menu
		cin >> i;
		for (int y = 0; y <= cur_appn; y++) //searches for applicant id
		{
			if (y == cur_appn) //when id not found
			{
				cout << "\n id not found .. ";
				system("pause");
				applicantmn(); //back to applicant menu
				break;
			}
			else if (i == app[y].id){ //id found
				i = app[y].id;
				indx = y; //holds applicant index in int indx
				break;
			}
		}

		temp = app[indx]; //takes application in temp for modifation
		while (1){
			do {
				system("cls");
				viewtemp(); //views data in temp variables
				cout << "\n==============================\n"
					<< "           Edit menu      \n"
					<< "=============================="
					<< "\n         1-name"
					<< "\n         2-age"
					<< "\n         3-qualifications"
					<< "\n         4-expierence"
					<< "\n         5-save and exit"
					<< "\n         6-Exit and discard changes"
					<< "\n\n Your choice : ";

				cin >> x;
			} while (!(x>0 && x<7)); //choice calidation
			system("cls");

			viewtemp();
			switch (x) //switch choice
			{
			case 1:
				cout << "\n Enter new name : ";
				cin >> temp.name;
				break;
			case 2:
				cout << "\n Enter new age : ";
				cin >> EDIT; //validate age boundaries

				if (EDIT > agmx || EDIT < agmn){
					cout << "\n Sorry .. you don't meet the job requirements regarding age\n"
						<< " .. application denied !\n ";
					system("pause");
				}
				else temp.ag = EDIT; //takes it in temp if accepted

				break;
			case 3: do {
						cout << "\n Enter new qualification : "
							<< "\n1-undergraduate  -  2-bachelor  -  3-master degree  -  4-doctorate";
						cin >> EDIT;
						if (EDIT < minqual){ //validates qualification boundaries
							cout << "\n Sorry .. you don't meet the job requirements regarding qualification\n"
								<< " .. application denied !\n ";
							system("pause");
						}
						else
						{
							temp.qual = EDIT; //takes it in temp if accepted
						}

			} while (temp.qual<0 && temp.qual>4); //validates choice

				break;
			case 4:
				cout << "\n Enter new expierence : ";
				cin >> EDIT;
				if (EDIT < minexpe){ //validates experience 
					cout << "\n Sorry .. you don't meet the job requirements regarding experience\n"
						<< " .. application denied !\n";
					system("pause");
				}
				else
				{
					temp.expe = EDIT; //takes it in temp if accepted
				}
				break;
			case 5:
				app[indx] = temp; //saves changes to application
				cout << "\n application saved ... ";
				system("pause");
				update(); //updates records
				applicantmn(); //back to applicants menu

			case 6: applicantmn(); //back to applicant menu without saving changes
			}

		}
	}

}