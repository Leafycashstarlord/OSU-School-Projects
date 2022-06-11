/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

//Returns the boards score
int MinimaxPlayer::utilityFunc(OthelloBoard *b){
	int score = b->count_score(b->get_p1_symbol()) - b->count_score(b->get_p2_symbol());
	return score;
}

//Returns the successors of the current board
vector<OthelloBoard*> MinimaxPlayer::successor(char playerSym, OthelloBoard *b){
	vector<OthelloBoard*> board;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(b->is_legal_move(i, j, playerSym)){
				board.push_back(new OthelloBoard(*b));
				board.back()->play_move(i, j, symbol);
				board.back()->row = j;
				board.back()->column = i;
			}
		}
	}
	return board;
}

//Runs the minimax function
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	if(symbol == b->get_p1_symbol()){
		maxFunc(row, col, symbol, b);
	}else if(symbol == b->get_p2_symbol()){
		maxFunc(row, col, symbol, b);
	}
}

//Returns the best maximum value for a given boars state
int MinimaxPlayer::maxFunc(int &row, int&col, char playerSym, OthelloBoard *b){
	vector<OthelloBoard*> board;
	int rows = 0;
	int cols = 0;
	int util = -100000;

	board = successor(playerSym, b);
	if(board.size() == 0){
		return utilityFunc(b);
	}

	for(int i = 0; i < board.size(); i++){
		if(minFunc(row, col, playerSym, board[i]) > util){
			rows = board[i]->row;
			cols = board[i]->column;
			util = minFunc(row, col, playerSym, board[i]);
		}
	}
	row = rows;
	col = cols;
	return util;
}

//Returns the best minimum value for a given board state.
int MinimaxPlayer::minFunc(int &row, int &col, char playerSym, OthelloBoard *b){
	vector<OthelloBoard*> board;
	int rows = 0;
	int cols = 0;
	int util = 100000;

	board = successor(playerSym, b);
	if(board.size() == 0){
		return utilityFunc(b);
	}

	for(int i = 0; i < board.size(); i++){
		if(minFunc(row, col, playerSym, board[i]) > util){
			rows = board[i]->row;
			cols = board[i]->column;
			util = minFunc(row, col, playerSym, board[i]);
		}
	}
	row = rows;
	col = cols;
	return util;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
