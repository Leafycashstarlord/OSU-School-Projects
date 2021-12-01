/****************************************
 *
 *
 *
 *
 *
 *
 *
 *
 * *************************************/
#include <iostream>

using namespace std;

int main(){
   int value;

   cout << "Do you like vi? (1 for yes, 0 for no): " << endl;
   cin >> value;

   if (value == 1){
      cout << "You love vi!";
   }
   else if (value == 0){
      cout << "You hate vi!";
   }
}
