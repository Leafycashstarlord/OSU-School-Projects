#include <iostream>
#include <string>
#include "lab5.h"

using namespace std;

Date::Date(){
	day = 1;
	month = 1;
	year = 2001;
}

Date::Date(int num1, int num2, int num3){
	day = num1;
	month = num2;
	year = num3;
}

void Date::printDateNum(){
	cout << month;
	cout << "/" << day;
	cout << "/" << year << endl;
}

void Date::printDateWord(){
	if(month == 1){
		cout << "January";
	}else if(month == 2){
		cout << "February";
	}else if(month == 3){
		cout << "March";
	}else if(month == 4){
		cout << "April";
	}else if(month == 5){
		cout << "May";
	}else if(month == 6){
		cout << "June";
	}else if(month == 7){
		cout << "July";
	}else if(month == 8){
		cout << "August";
	}else if(month == 9){
		cout << "September";
	}else if(month == 10){
		cout << "October";
	}else if(month == 11){
		cout << "November";
	}else if(month == 12){
		cout << "December";
	}

	cout << " " << day;
	cout << ", " << year << endl;
}
