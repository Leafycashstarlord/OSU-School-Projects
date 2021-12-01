#ifndef CIRCLE_H
#define CRICLE_H

#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

class Circle : public Shape{
	private:
		float radius;
	public:
		Circle();
		Circle(float, string);
		float get_area(Circle);
		float get_radius();
		void set_radius(float);
};

#endif
