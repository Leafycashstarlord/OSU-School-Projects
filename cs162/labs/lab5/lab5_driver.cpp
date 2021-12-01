#include <iostream>
#include <string>
#include "lab5.h"

using namespace std;

int main(){
	Date date1;
	Date date2 = Date(26, 6, 1990);

	date1.printDateNum();
	date1.printDateWord();

	date2.printDateNum();
	date2.printDateWord();

	return 0;
}
