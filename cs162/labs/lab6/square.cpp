#include <iostream>
#include <string>
#include "shape.h"
#include "rectangle.h"
#include "square.h"

using namespace std;

Square::Square(){
	name = "Square";
	color = "";
	set_width(0);
	set_length(0);
}

Square::Square(float new_width, float new_length, string new_color){
	name = "Square";
	color = new_color;
	float side_length = get_side(new_width, new_length);
	set_width(side_length);
	set_length(side_length);
}

float Square::get_side(float new_width, float new_length){
	float num;

	if(new_width == new_length){
		return new_width;
	}else{
		cout << "Give a side length(float): ";
		cin >> num;
		cout << endl;		

		return num;
	}
}
