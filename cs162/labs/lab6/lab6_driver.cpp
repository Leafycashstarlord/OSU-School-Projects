#include <iostream>
#include <string>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"

using namespace std;

void print_shape_inf(Shape &shape){
	cout << "Area: " << shape.get_area() << endl;
	cout << "Name: " << shape.get_name() << endl;
	cout << "Color: " << shape.get_color() << endl;
	cout << endl;
}

int main(){
	Circle c1;
	Circle c2;
	c2.set_name("Circle2");
	c2.set_color("Red");
	c2.set_radius(5.5);

	Rectangle r1;
	Rectangle r2;
	r2.set_name("Rectangle2");
	r2.set_color("Yellow");
	r2.set_width(10);
	r2.set_length(30);

	Square sqr1;
	Sqaure sqr2;
	sqr2.set_color("Blue");
	sqr2.set_name("Square 2");
	sqr2.get_side(10, 10);

	Shape *shape1 = &c1;
	print_shape_info(*shape1);
	Shape *shape2 = &c2;
	print_shape_info(*shape2);

	Shape *shape3 = &r1;
	print_shape_info(*shape3);
	Shape *shape4 = &r2;
	print_shape_info(*shape4);

	Shape *shape5 = &sqr1;
	print_shape_info(*shape5);
	Shape *shape6 = &sqr2;
	print_shape_info(*shape6);

	cout << "Exceptions" << endl;
	cout << endl;
	int new_radius;
	cout << "Give Circle radius: ";;
	cin >> new_radius;
	try{
		Circle c3 = Circle(new_radius, "Blue");
		Shape *shape7 = &c3;
		print_shape_info(*shape7);
	}catch(int invalid_argument){
		cout << "Invalid argument!" << endl;
		continue;
	}

	return 0;
}
























	/*Shape triangle = Shape("Triangle", "Yellow");
	float triangle_area = triangle.get_area();
	cout << triangle.get_color() << " " << triangle.get_name() << endl;
	cout << "Area: " << triangle_area << endl;
	cout << endl;

	Circle circ = Circle(5.0, "Red");
	float circle_area = circ.area(circ);
	cout << circ.get_color() << " " << circ.get_name() << endl;
	cout << "Area: " << circle_area << "pi" << endl;
	cout << endl;

	Rectangle rect = Rectangle(25, 35, "Blue");
	float rectangle_area = rect.area(rect);
	cout << rect.get_color() << " " << rect.get_name() << endl;
	cout << "Area: " << rectangle_area << endl;
	cout << endl;

	Square sqr = Square(5, 10, "Orange");
	float side = sqr.get_side(sqr.get_width(), sqr.get_length());
	float sqr_area = sqr.area(sqr);
	cout << sqr.get_color() << " " << sqr.get_name() << endl;
	cout << "Area: " << sqr_area << endl;
	cout << endl;*/
