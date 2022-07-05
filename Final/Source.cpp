#include <iostream>
#include<string>
#include<fstream>
#include"MANAGER_HR.h" //include for  this header files


using namespace std;

int main()//main
{


	readfile();//calling for function used to read from mangdata some marked data and some conditions works on it

	menu();// calling for function used to show main menu to choose from them
	close();
	system("pause");
	return 0;
}// end main 