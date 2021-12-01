#include <iostream>

using namespace std;

int main(){
   int x;
   x = 3;
   int y;
   char myAnswer;

   y = x;
   cout << "Y is set to: " << y << endl;

   cout << "Please input a number: ";
   cin >> y;
   
   
   bool again = true;
   while(again){
      if(x > y){
      	cout << "X is greater than Y\n";
       	cout << "would you lik eto input another number? " << endl;
	cin >> again;	
      }else{
      	cout << "X is less than Y" << endl;
       	cout << "Would you like to input another number?" << endl;
	cin >> again;	
      }
      //hint: what about equal logic      
   } 
   for(int x = 0; x < 10; x++){
	cout << x << endl;
   }
   int num;
   for(int x = num; x > 0; x--){
   	x = x * x;		//hint: is this factorial correct?
   }
   cout << "Are you enjoying cs161? (y or n) " << endl;
   cin >> myAnswer;
   if(myAnswer = y){
   	cout << "YAY" << endl; 
   }else{
   	cout << "YOU WILL SOON!" << endl;  
   } 
}


