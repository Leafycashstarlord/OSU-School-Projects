#include "./vector.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

int main(){
	vector<int> v;
	std::vector<int> stdv;

	v.push_back(23);
	stdv.push_back(23);

	cout << "Our vector size: " << v.size() << endl;
	cout << "STL vector size: " << stdv.size() << endl;

	vector<int>new_v = v;
	std::vector<int>new_stdv = stdv;

	cout << "Our new vector size: " << new_v.size() << endl;
	cout << "STL new vector size: " << new_stdv.size() << endl;

	v.push_back(10);
	new_v = v;
	stdv.push_back(10);
	new_stdv = stdv;

	cout << "Our new vector size: " << new_v.size() << endl;
	cout << "STL new vector size: " << new_stdv.size() << endl;

	cout << "Out vector at 1: " << v[1] << endl;
	cout << "STL vector at 1: " << stdv[1] << endl;

	return 0;
}
