#include <iostream>
#include <string>
#include <cstdlib>
#include "person.h"
#include "vehicle.h"

using namespace std;

void printPersonInfo(Person p){
	cout << "Name: " << p.name << endl;
	cout << "Number of Vehicles: " << p.num_vehicle << endl;
	Cout << "Vehicles: ";
	for(int i = 0; i < p.num_vehicle; i ++){
		cout << p.vehicles[i].get_vehicle(); << " ";
	}
	cout << endl;
	printName();
	printNum();
	printVehicle();
}

int main(){
	Person p;
	string name;
	int num;
	string v_type;

	cout << "What is your name? " << endl;
	cin >> name;
	p.set_name(name);

	cout << "How many vehicles do you own?" << endl;
	cin >> num;
	p.set_num_vehicles(num);

	
	for(int i = 0; i < num; i++){
		cout << "What type of vehicle do you have?" << endl;
		cin >> v_type;
		p.vehicles[i].set_vehicle(v_type);
	}

	printPersonInfo(p);

	return 0;
}
