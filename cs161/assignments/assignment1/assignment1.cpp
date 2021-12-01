#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;


/***************************************************
 *Program: assignment1.cpp
 *Auther: Jackson E. Rollins
 *Date: 01/19/2020
 *Description: The program calculates the gross income, taxes needed to be paid
and the remainder for a car salesman, depending on their salary, how many cars they
sold at a certain price, in a specific state and tax year.
 *Input: Salary, months worked, car cost, cars sold, misconducts, tax year, state
 *Output: Gross income, taxes to be paid, reamining money
 * ************************************************/

int main(){
	//Ask for salary
	int salary;
	cout << "Enter your monthly salary: ";
	cin >> salary;

	//Ask for months work
	int months;
	cout << "Enter months worked this year: ";
	cin >> months;

	//Ask for cost of car
	int ccost;
	cout << "Enter the cost of a car: ";
	cin >> ccost;

	//Ask for number of cars sold
	int csold;
	cout << "Enter number of cars sold: ";
	cin >> csold;

	//Ask for number of misconducts
	int misconducts;
	cout << "Enter number of misconducts: ";
	cin >> misconducts;

	//Ask for the task year, either 2017 or 2018
	int taxYear;
	cout << "Enter the tax year (type 1 for 2017, type 2 for 2018): ";
	cin >> taxYear;

	//Ask for the state, either A, B, or C
	char state;
	cout << "Enter state: ";
	cin >> state;	

	//Random number
	int x;
	int y;
	srand(time(NULL));
	x = rand();
	y = (x % 6) + 5;

	int annualSalary;
	float sellingPrice;
	int deduction;
	int profit;
	int grossIncome;
	int totalTaxes;

	//Calculates gross income
	annualSalary = months * salary;
	sellingPrice = (y/100.0) + 1;
	profit = csold * ((ccost * sellingPrice) - ccost);
	if (misconducts == 0){
		deduction = 0;
	}
	else{
		deduction = 100 * pow(2, (misconducts -1));
	}
	
	grossIncome = annualSalary + (0.02 * profit) - deduction;


	//Calculates amount of taxes based on year & state
	if (taxYear == 1){
		if (state == 'A'){
			totalTaxes = grossIncome * 0.06;
		}
		else if (state == 'B'){
			if (grossIncome < 2000){
				totalTaxes = 0;
			}
			else if ((grossIncome >= 2000) && (grossIncome <= 10000)){
				totalTaxes = 100;
			}
			else if (grossIncome > 10000){
				totalTaxes = (grossIncome * 0.1) + 100;
			}
		}
		else if (state == 'C'){
			if (grossIncome < 3500){
				totalTaxes = grossIncome * 0.05;
			}
			else if ((grossIncome >= 3500) && (grossIncome <= 9000)){
				totalTaxes = (grossIncome * 0.07) + 175;
			}
			else if ((grossIncome > 9000) && (grossIncome <= 125000)){
				totalTaxes = (grossIncome * 0.09) + 560;
			}
			else if (grossIncome > 125000){
				totalTaxes = (grossIncome * 0.099) + 11000;
			}
		}
	}
	else if (taxYear == 2){
		if (state == 'A'){
			totalTaxes = grossIncome * 0.08;
		}
		else if (state == 'B'){
			if (grossIncome < 2500){
				totalTaxes = 0;
			}
			else if ((grossIncome >= 2500) && (grossIncome <=10000)){
				totalTaxes = 115;
			}
			else if (grossIncome > 10000){
				totalTaxes = (grossIncome * 0.105) + 115;
			}
		}
		else if (state == 'C'){
			if (grossIncome < 3450){
				totalTaxes = grossIncome * 0.05;
			}
			else if ((grossIncome >= 3450) && (grossIncome <= 8700)){
				totalTaxes = (grossIncome * 0.07) + 172.5;
			}
			else if ((grossIncome > 8700) && (grossIncome <= 125000)){
				totalTaxes = (grossIncome * 0.09) + 540;
			}
			else if (grossIncome > 125000){
				totalTaxes = (grossIncome * 0.099) + 11007;
			}
		}
	}

	//Calculates the remainder
	int remainder;
	remainder = grossIncome - totalTaxes;

	//Prints out the gross income, taxes, and remainder
	cout << "The gross income is: " << grossIncome << endl;
	cout << "The total taxes is: " << totalTaxes << endl;
	cout << "The remainder is: " << remainder << endl;

	return 0;
}
