#ifndef LAB5_H
#define LAB5_H

#include <iostream>
#include <string>

using namespace std;

class Date{
	private:
		int day;
		int month;
		int year;
	public:
		Date();
		Date(int, int, int);
		void printDateNum();
		void printDateWord();
};

#endif
