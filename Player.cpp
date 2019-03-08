#include "Player.h"
using namespace std;

Player::Move::Move(Square &start, Square &end): start_square(start), end_square(end){}

Player::Player(bool in_color): color(in_color), other_player(nullptr){}

const Square& Player::king_location() const
{
	return *pieces[0].get_square();
}

/*
Move get_input_move() const
{
	TODO
}
*/

void Player::give_set_of_pieces(vector<ChessPiece> in_pieces)
{
	pieces.swap(in_pieces);
}

/*
bool is_valid_move(const Move &move) const
{

}

bool is_valid_destination_square(const Move &move)
{

}
*/