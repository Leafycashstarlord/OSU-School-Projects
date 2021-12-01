#include <iostream>
#include <string>
#include "shape.h"
#include "circle.h"

using namespace std;

Circle::Circle(){
	radius = 0;
	name = "Circle";
	color = "";
}

Circle::Circle(float new_radius, string new_color){
	radius = new_radius;
	name = "Circle";
	color = new_color;
}

float Circle::get_area(Circle c){
	float num = c.get_radius();
	num = num*num;

	return num;
}

float Circle::get_radius(){
	return radius;
}

void Circle::set_radius(float new_radius){
	radius = new_radius;
}
