//this is how you make a line comment
#include <iostream>  //this is the library for input and output
#include <cmath>  //this is the library for the sqrt function

#define elements 4  //this defines elements to be 4

//function to fill the x and y arrays with a specific number of elements
void fill_arrays(int x[], int y[]) {
   //for each element in x and y
   for(int i=0; i< elements; i++) {
      std::cout << "Enter an element for x: ";  //print a prompt
      std::cin >> x[i];  //get input from user and store in position in x
      std::cout << "Enter an element for y: ";
      std::cin >> y[i];
   }
}

//add corresponding elements of x and y, and store in the corresponding
//elements in z
void sum_elements(int x[], int y[], int z[]) {
   for(int i=0; i< elements; i++) {
      z[i]=x[i]+y[i];
   }
}

//add all the elements in z and return the square root of the sum
int  sqrt_of_sum(int z[]) {
   int sum=0;
   for(int i=0; i< elements; i++) {
      sum=sum+z[i];
   }
   return sqrt(sum);
}

//main function, where the program begins
int main() {
   int x[elements], y[elements], z[elements]; //create 3 arrays
   
   fill_arrays(x, y);  //call fill_arrays function
   sum_elements(x, y, z);  //call sum_elements function
   //print the square root of the sum of the elements in z
   std::cout << "Square root of the sum: " << sqrt_of_sum(z) << std::endl;

   return 0;
}
