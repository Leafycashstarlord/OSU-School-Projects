#include <iostream>

using namespace std;

void towers(int number_of_disks, int b[][3], int from_col, int to_col, int spare){
	if(disks >= 1){
		towers(disks - 1, b, from_col, to_col, spare);
		move(b, from_col, to_col);
		printBoard(b, number_of_disks);
		towers(disks - 1, b, spare, to_col, from_col);
	}
}

void move(int b[][3], int from_col, int to_col){
	b[][k];
}

void printBoard(int b[][3], int disks){
	int disk = disks - 1;
   	while(disk >= 0){
		cout << b[disk][0] << " " << b[disk][1] << " " << b[disk][0] << endl;
		disk--;
	}
}

int main(){

	return 0;
}
