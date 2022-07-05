#ifndef DATA_H // if APPLICANT.h hasn't been included yet...
#define DATA_H //   #define this so the compiler knows it has been included
#include <iostream>
#include<string>
#include<fstream>

using namespace std;
struct applicant //structure to enter informations for applicants
{
	string name;
	int expe, ag, qual, id;
	bool accpt;
};

//using the keyword extern to declare global variables in a header file and use it in the entire program
extern string passw; // creating apassword for manager_hr
extern fstream appdata, acc_appdata, mangdata;// files i will use to keep my data like (applicant information,manager marked selection)
extern applicant *app, temp;//dynamic allocation for data
extern bool start, read, open, del;//false value
extern bool done;//true when applicant are chosen
extern int idc, agmx, agmn, minexpe, minqual;//declare the max age,the min age,the experince of applicant,
extern int acc_appn, cur_appn, max_appn, reqapp;// current applicant number,the max number to stop , number of applicants required
extern int maxexp, minexp;//holds the max and min qualifactins
extern int acc_qual[4];//an array use in the operation when show accpeted applicants
extern int qual[4];//number of applicants with each qualfications

void applicantmn();// briefly it use to show the applicant menu with conditions in it 
void menu();// the main function on the program and use to show the menu for selection
void readfile();//function used to read from mangdata some marked data and some conditions works on it
void manager();//the main function in MANAGER_HR and ask him to enter password and if correct show the menu
void view(int = -1);// fnction used to read qualifications if it exist and print it
void viewtemp();// afuction used to read data from applicant and store it
void delet();// afunction used to delete applications and the id for the applicant and display that
void update();// afunction used to update data for applicants 
void close();// afunction use to close the application when i finished 
void mangupdate();// afunction used to  update data in mangdata file and store it 
void reset();//afunction used to delete all data for applicants and start from beginning

#endif// DATA.h done 