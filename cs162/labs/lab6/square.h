#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>
#include "shape.h"
#include "rectangle.h"

class Square : public Rectangle{
	public:
		Square();
		Square(float, float, string);
		float get_side(float, float);
};

#endif
