/*******************************************
 *Program: assignment5.cpp
 *Author: Jackson E. Rollins
 *Date: 3/15/2020
 *Description: The program is a connect four game
 *Input: Number o fPlayers, and size of board
 *Output: The game
 * ****************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

/**************
 *Function: init()
 *Description: Creates the board array
 *Parameters: char a, int row, int col
 *Pre-Con: takes integer and character parameters
 *Post-Con: None
 * ***************/
void init(char** &a, int row, int col){
	a = new char* [row];
	for(int i = 0; i < row; i++){
		a[i] = new char[col];
	}
	
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			a[i][j] = ' ';
		}
	}
}

/********************
 *Function: print() 
 *Description: Prints out the game board
 *Parameters: char a, int row, int col
 *Pre-Con: takes integers and haracter parameters
 *Post-Con: None
 * ****************/
void print(char** a, int row, int col){
	for(int k = 0; k < col; k++)
		if(k < 9){
			cout << "  " << k + 1 << " ";
		}else{
			cout << " " << k + 1 << " ";
		}

	cout << endl;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(i % 2 == 0 && j % 2 == 0){
	   	   		cout << "|\033[30;47m " << a[i][j] << " ";
			}else if(i % 2 == 1 && j % 2 == 1){
				cout << "|\033[30;47m " << a[i][j] << " ";
			}else{
				cout << "|\033[0m " << a[i][j] << " ";
			}
			cout << "\033[0m";
		}
		cout << endl;
	
	}
}

/****************
 *Function: Winner()
 *Description: Checks the win conditions
 *Parameters: char board, int row, int cols, int turn, int rows, int columns
 *Pre-Con: takes integers and characters
 *Post-Con: returns either true or false
 * *************/
bool winner(char** board, int row, int cols, int turn, int rows, int columns){
	int counter;
	char piece;
	if(turn % 2 == 1){
		piece = 'X';
	}else if(turn % 2 == 0){
		piece = 'O';
	}

	counter = 0;
	for(int i = 0; i < 7; i++){
		if(rows-3+i >= 0 && rows-3+i < row){
			if(board[rows-3+i][columns] == piece){
				counter++;
			}else{
				counter = 0;
			}
			if(counter == 4){
				return true;
			}
		}
	}
	
	counter = 0;
	for(int i = 0; i < 7; i++){
		if(columns-3+i >= 0 && columns-3+i < row){
			if(board[rows][columns-3+i] == piece){
				counter++;
			}else{
				counter = 0;
			}
			if(counter == 4){
				return true;
			}
		}
	}

	counter = 0;
	for(int i = 0; i < 7; i++){
		if((columns-3+i >= 0 && columns-3+i < row) && (rows-3+i >= 0 && rows-3+i < row)){
			if(board[rows-3+i][columns-3+i] == piece){
				counter++;
			}else{
				counter = 0;
			}
			if(counter == 4){
				return true;
			}
		}
	}
	
	counter = 0;
	for(int i = 0; i < 7; i++){
		if((columns-3+i >= 0 && columns-3+i < row) && (rows+3-i >= 0 && rows+3-i < row)){
			if(board[rows+3-i][columns-3+i] == piece){
				counter++;
			}else{
				counter = 0;
			}
			if(counter == 4){
				return true;
			}
		}
	}

	return false;
}

/*********************
 *Function: playerTurn()
 *Description: Runs the user's turn 
 *Parameters: char board, int turn, int row, int cols, int rows, int columns
 *Pre-Con: takes integer and character parameters
 *Post-COn: None
 * *******************/
void playerTurn(char** board, int turn, int row, int cols, int &rows, int &columns){
	int play;
	bool validOne;
	bool validTwo = false;
	do{
   		if(turn % 2 == 1){
			cout << "Player One, where do you want to play? (Pick a column, integer only please): " << endl;
			cin >> play;
		}else if(turn % 2 == 0){
			cout << "Player Two, where do you want to play? (Pick a column, integer only please): " << endl;
			cin >> play;
		}

		if(cin.fail() == true){
			validOne = false;
		}else{
			validOne = true;
		}
		play--;
		for(int j = 0; j < cols; j++){
			if((j == play) && (validOne == true)){
				if((board[0][play] == 'X') || (board[0][play] == 'O')){
			   		validTwo = false;
				}else{
					validTwo = true;
				}
			}
		}
		if(validTwo == false){
			cout << "That is an invalid column." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}while(validTwo == false);
	columns = play;
	for(int i = 0; i < row; i++){
		if(board[i][play] == 'X' || board[i][play] == 'O'){
			if(turn % 2 == 1){
				board[i-1][play] = 'X'; 
			}else if(turn % 2 == 0){
				board[i-1][play] = 'O';
			}
			rows = i-1;
		}else if((i == (row - 1))){
			if(turn % 2 == 1){
				board[i][play] = 'X';
			}else if(turn % 2 == 0){
				board[i][play] = 'O';
			}
			rows = i;
		}
	}
	cout << rows << endl;
}

/**************
 *Function: computerTurn()
 *Description: Runs the computer's turn 
 *Parameters: char board, int turn, int row, int cols, int rows, int columns
 *Pre-Con: integer and character parameters
 *Post-Con: None
 * ************/
void computerTurn(char** board, int turn, int row, int cols, int &rows, int &columns){
	int play;
	play = (rand() % cols);
	while((board[0][play] == 'X') || (board[0][play] == 'O')){
		play = (rand() % cols) + 1;
	}

	columns = play;

	for(int i = 0; i < row; i++){
		if(board[i][play] == 'X' || board[i][play] == 'O'){
			if(turn % 2 == 1){
				board[i-1][play] = 'X';
			}else if(turn % 2 == 0){
				board[i-1][play] = 'O';
			}
			rows = i-1;
		}else if(i = (row - 1)){
			if(turn % 2 == 1){
				board[i][play] = 'X';
			}else if(turn % 2 == 0){
				board[i][play] = 'O'; 
			}
			rows = i;
		}
	}
}

/*****************
 *Function: playerFirst()
 *Description: Figures out which player goes first
 *Parameters: None
 *Pre-Con: None
 *Post-Con: Either true or false
 * *************/
bool playerFirst(){
	int value;
	bool valid;
	do{
   		cout << "Do you want to go first(1), or let the computer go first(2)? Integers please: " << endl;
		cin >> value;

		if((value != 1) && (value != 2)){
			cout << "That is an invalid option." << endl;
			valid = false;
			cin.clear();
			cin.ignore(10000, '\n');
		}else{
			valid = true;
		}
	}while(valid == false);

	if(value == 1){
		return true;
	}else if(value == 2){
		return false; 
	}
}

/***************
 *Function: onePlayerGame()
 *Description: Runs the one player game against the computer
 *Parameters: char board, int row, int cols
 *Pre-Con: Integer and character parameters
 *Post-Con: None
 * *************/
void onePlayerGame(char** board, int row, int cols){
	int turn;
	int rows;
	int columns;
   	bool first = playerFirst();
	if(first == true){
		turn = 1;
	}else if(first  == false){
		turn = 0;
	}
	do{
		if(turn % 2 == 0){
			computerTurn(board, turn, row, cols, rows, columns);
			print(board, row, cols);
			turn++;
		}else if(turn % 2 == 1){
			playerTurn(board, turn, row, cols, rows, columns);
			print(board, row, cols);
			turn++;
		}
	}while(winner(board, row, cols, (turn -1), rows, columns) == false);

	if((turn -1) % 2 == 1){
		cout << "Player One Wins!" << endl;
	}else{
		cout << "Player Two Wins!" << endl;
	}
}

/********************
 *Function: twoPlayerGame()
 *Description: Runs the two player game against each other
 *Parameters: char board, int row, int cols
 *Pre-Con: Integer and character parameters
 *Post-Con: None
 * *******************/
void twoPlayerGame(char** board, int row, int cols){
	int turn = 1;
	int rows;
	int columns;
	do{
		playerTurn(board, turn, row, cols, rows, columns);
		print(board, row, cols);
		turn++;
	}while(winner(board, row, cols, (turn - 1), rows, columns) == false);

	if((turn-1) % 2 == 1){
		cout << "Player One Wins!" << endl;
	}else{
		cout << "Player Two Wins!" << endl;
	}
}

/********************************
 *Function: del()
 *Description: Deletes the games memory from the heap
 *Parameters: char a, int row
 *Pre-Con: Interger and character parameters
 *Post-Con: None
 * ******************************/
void del(char** a, int row){
	for(int i = 0; i < row; i++){
		delete [] a[i];
	}
	delete [] a;
}

/**************
 *Function: get_row()
 *Description: Gets an integer value for the row size
 *Parameters: None
 *Pre-Con: None
 *Post-Con: returns an integer
 * ***************/
int get_row(){
	int rows;
	do{
		cout << "How many rows do you want on your board? (Between 4-20, Integers only please): " << endl;
		cin >> rows;

		if((rows < 4) || (rows > 20)){
			cout << "That is an invalid value." << endl;
			cin.clear();
			cin.ignore(10000, '\n' );
		}
	}while((rows < 4) || (rows > 20));

	return rows;
}

/***************
 *Function: get_cols()
 *Description: Gets an integer value for the column size
 *Parameters: None
 *Pre-Con: none
 *Post-con: return an integer value
 * *************/
int get_cols(){
	int cols;
	do{
		cout << "How many columns do you want on your board? (Between 4-20, Integers only please): " << endl;
		cin >> cols;

		if((cols < 4) || (cols > 20)){
			cout << "That is an invalid value." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}while((cols < 4) || (cols > 20));

	return cols;
}

/**************************
 *Function: get_players()
 *Description: Gets an integer for the number of players playing
 *Parameters: None
 *Pre-Con: None
 *Post-Con: returns an integers
 * ************************/
int get_players(){
	int players;
	do{
		cout << "How many players are there? (Either 1 or 2, Integers only please): " << endl;
		cin >> players;

		if((players != 1) && (players != 2)){
			cout << "That is an invalid value." << endl;
			cin.clear();
		       	cin.ignore(10000, '\n');
		}
	}while((players != 1) && (players != 2));
}

/*********************8
 *Function: main()
 *Description: Main program that runs everything
 *Parameters: int argc, char argv
 *Pre-Conditions: 4 command line arguments
 *Post-Conditions: None
 * *******************/
int main(int argc, char** argv){
	srand(time(NULL));
	int row, cols, players, counter, value;
	bool playAgain;
	do{
		counter = 0;
		if((argc == 4) && (counter == 0)){
			row = atoi(argv[2]);
			if((row < 4) || (row > 20)){
				row = get_row();
			}
			cols = atoi(argv[3]);
			if((cols < 4) || (cols > 20)){
				cols = get_cols();
			}
			players = atoi(argv[1]);
			if((players != 1) && (players != 2)){
				players = get_players();
			}
	
			counter++;
		}else{
			row = get_row();
			cols = get_cols();
			players = get_players();
		}
		char** board;
		init(board, row, cols);
		print(board, row, cols);
	
		if(players == 1){
			onePlayerGame(board, row, cols);
		}else if(players == 2){
			twoPlayerGame(board, row, cols);
		}
		
		do{ 
			cout << "Do you want to play again? (Yes = 1, No = 2): " << endl;
			cin >> value;
			del(board, row);
			if((value != 1) && (value != 2)){
				cout << "That is an invalid value." << endl;
				cin.clear();
			       	cin.ignore(10000, '\n'); 	
			}
		}while((value != 1) && (value != 2));

		if(value == 1){
			playAgain = true;
		}else if(value == 2){
			playAgain = false;
		}
	}while(playAgain == true);

	return 0;
}
