#include "Player.h"
using namespace std;

Player::Move::Move(Square &start, Square &end): start_square(start), end_square(end){}

Player::Player(bool in_color, Board &board)
: color(in_color), other_player(nullptr), board(board){
	setup_pieces();
}

void Player::setup_pieces()
{
	set_king();
	set_queen();
	set_rooks();
	set_bishops();
	set_knights();
	set_pawns();
}


void Player::set_pawns()
{
	const int row = (color)? 1:6;
	for (int col = 0; col < 8; ++col){
		pieces.emplace_back(new Pawn(color));
		pieces.back()->place(board[col][row]);
	}
}

void Player::set_knights()
{
	const int row = (color)? 0:7;
	pieces.emplace_back(new Knight(color));
	pieces.back()->place(board[1][row]);
	pieces.emplace_back(new Knight(color));
	pieces.back()->place(board[6][row]);
}


void Player::set_bishops()
{
	const int row = (color)? 0:7;
	pieces.emplace_back(new Bishop(color));
	pieces.back()->place(board[2][row]);
	pieces.emplace_back(new Bishop(color));
	pieces.back()->place(board[5][row]);
}

void Player::set_rooks()
{
	const int row = (color)? 0:7;
	pieces.emplace_back(new Rook(color));
	pieces.back()->place(board[0][row]);
	pieces.emplace_back(new Rook(color));
	pieces.back()->place(board[7][row]);
}

void Player::set_queen()
{
	const int row = (color)? 0:7;
	pieces.emplace_back(new Queen(color));
	pieces.back()->place(board[3][row]);
}

void Player::set_king()
{
	const int row = (color)? 0:7;
	pieces.emplace_back(new King(color));
	pieces.back()->place(board[4][row]);
}

const Square& Player::king_location() const
{
	return *pieces[0]->get_square();
}

bool Player::is_valid_destination_square(const Move &move) const
{
	return move.end_square.is_empty() || move.end_square.get_piece()->color != color;
}

bool Player::path_is_clear(const Move &move) const
{
	const vector<const Square*> move_path = squares_on_move_path(move);

	for (auto sqr : move_path)
	{
		if (!sqr->is_empty()){
			return false;
		}
	}

	return true;
}

vector<const Square*> Player::squares_on_move_path(const Move &move) const
{
	const int horizontal_squares_traveled = abs(move.end_square.X - move.start_square.X);
	const int vertical_squares_traveled = abs(move.end_square.Y - move.start_square.Y);

	const int h_direction = (move.end_square.X < move.start_square.X)? -1:1;
	const int v_direction = (move.end_square.Y < move.start_square.Y)? -1:1;

	vector<const Square*> move_path;

	if (horizontal_squares_traveled == vertical_squares_traveled){
		for (int i = 1; i < horizontal_squares_traveled; ++i){
			move_path.push_back(
				&board[move.start_square.X + (i*h_direction)][move.start_square.Y + i*v_direction]);
		}
	}

	else if (horizontal_squares_traveled == 0 && vertical_squares_traveled > 1){
		for (int i = 1; i < vertical_squares_traveled; ++i){
			move_path.push_back(&board[move.start_square.X][move.start_square.Y + i*v_direction]);
		}
	}

	else if (horizontal_squares_traveled > 1 && vertical_squares_traveled == 0){
		for (int i = 1; i < horizontal_squares_traveled; ++i){
			move_path.push_back(&board[move.start_square.X + i*h_direction][move.start_square.Y]);
		}
	}

	return move_path;
}








