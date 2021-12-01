#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

Class Circle : public Shape{
	private:
		float radius;
	public:
		Circle();
		Circle(float, string);
		float area(Circle);
		float get_radius();
		void set_radius(float);
};
