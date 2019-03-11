#include "Board.h"
using namespace std;

Board::Board()
{
	for (int x = 0; x < NUM_SQUARES; ++x){
		board.push_back(vector<Square>());
		for (int y = 0; y < NUM_SQUARES; ++y){
			board[x].push_back(Square(x,y));
		}
	}
}

void Board::display()
{
	cout << "_________________________________________________" << endl;

	for (int i = 0; i < 8; ++i){
		cout << "|     |     |     |     |     |     |     |     |" << endl;
		cout << "|  ";
		for (int j = 0; j < 8; ++j){
			char letter = (board[j][i].is_empty())?' ':board[j][i].get_piece()->letter_representation();
			cout << letter << "  |  ";
		}
		cout << endl;
		cout << "|_____|_____|_____|_____|_____|_____|_____|_____|" << endl;

	}
}

vector<Square> & Board::operator[](int x)
{
	return board[x];
}

const vector<Square> & Board::operator[](int x) const 
{
	return board[x];
}