#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <string>

using namespace std;

class Rectangle : public Shape{
	private:
		float width;
		float length;
	public:
		Rectangle();
		Rectangle(float, float, string);
		float get_area(Rectangle);
		float get_width();
		float get_length();
		void set_width(float);
		void set_length(float);
};

#endif
