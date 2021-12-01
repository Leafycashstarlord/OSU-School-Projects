#include <iostream>
#include <string>
#include "shape.h"
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(){
	width = 0;
	length = 0;
	name = "Rectangle";
	color = "";
}

Rectangle::Rectangle(float new_width, float new_length, string new_color){
	width = new_width;
	length = new_length;
	name = "Rectangle";
	color  = new_color;
}

float Rectangle::get_area(Rectangle rect){
	float num = rect.get_width() * rect.get_length();

	return num;
}

float Rectangle::get_width(){
	return width;
}

float Rectangle::get_length(){
	return length;
}

void Rectangle::set_width(float new_width){
	width = new_width;
}

void Rectangle::set_length(float new_length){
	length = new_length;
}
