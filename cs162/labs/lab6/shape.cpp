#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

Shape::Shape(){
	name = "";
	color = "";
}

Shape::Shape(string new_name, string new_color){
	if(new_name == "" || new_color == ""){
		throw invalid_argument("Invalid shape constructor argument");
	}
	
	name = new_name;
	color = new_color;
}

string Shape::get_name(){
	return name;
}

string Shape::get_color(){
	return color;
}

void Shape::set_name(string new_name){
	name = new_name;
}

void Shape::set_color(string new_color){
	color = new_color;
}
