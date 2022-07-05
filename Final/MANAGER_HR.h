#ifndef MANAGER_HR_H // if APPLICANT.h hasn't been included yet...
#define MANAGER_HR_H //   #define this so the compiler knows it has been included

#include <iostream>
#include <string>
#include <fstream>
#include"APPLICANT.h"// this  header file has been inculded 

using namespace std;



void specqual();// afunction used to ask manager to enter the data he want to be limits for apply job
void chck();//display all informations about all applicants 
void pickapp();//function used briefly to arrange the applicants 
void endapp();// function used to end application and exit program 


#endif //MANAGER_HR done