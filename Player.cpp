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

Square& Player::king_location() const
{
	return *pieces[0]->get_square();
}

bool Player::is_valid_move(const Move &move) const
{
	if (move.start_square.is_empty()) return false;
	
	const ChessPiece * piece_to_move = move.start_square.get_piece();
	if (!piece_to_move->color == color)	return false;
	
	if (!piece_to_move->is_in_play()) return false;

	if (!is_valid_destination_square(move)) return false;

	if (!piece_to_move->is_valid_move(move.end_square)) return false;
	
	if (!path_is_clear(move)) return false;

	return true;
}

bool Player::is_valid_destination_square(const Move &move) const
{

	return move.end_square.is_empty() || move.end_square.get_piece()->color != color;
}

bool Player::path_is_clear(const Move &move) const
{
	// Check if the squares BETWEEN the start and end square are epmty
	vector<Square*> move_path = squares_on_move_path(move);

	for (auto sqr : move_path)
	{
		if (!sqr->is_empty()){
			return false;
		}
	}

	return true;
}

vector<Square*> Player::squares_on_move_path(const Move &move) const
{
	const int horizontal_squares_traveled = abs(move.end_square.X - move.start_square.X);
	const int vertical_squares_traveled = abs(move.end_square.Y - move.start_square.Y);

	const int h_direction = (move.end_square.X < move.start_square.X)? -1:1;
	const int v_direction = (move.end_square.Y < move.start_square.Y)? -1:1;

	vector<Square*> move_path;

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

bool Player::move_puts_player_in_check(const Move &move) 
{	
	// Temporarily make the move, and see if it gives access to the 
	// king to any of the other players pieces
	ChessPiece *original_piece_at_destination = move.end_square.get_piece();
	move.end_square.remove_piece();

	// Use place instead of move to avoid changing piece.has_moved
	move.start_square.get_piece()->place(move.end_square);
	move.start_square.remove_piece();
	bool results_in_check = false;
	
	for (auto &piece: other_player->pieces)
	{
		if (piece->is_in_play())
		{
			const Move possible_check_move(*(piece->get_square()), king_location());
			if (other_player->is_valid_move(possible_check_move)){
				results_in_check = true;
			}
		}
	}

	move.end_square.get_piece()->place(move.start_square);
	move.end_square.remove_piece();
	if (original_piece_at_destination)
	{
		original_piece_at_destination->place(move.end_square);
	}

	return results_in_check;
}

void Player::move_piece(const Move &move)
{
	if (!move.end_square.is_empty()) move.end_square.get_piece()->remove_from_play();
	move.start_square.get_piece()->move_to(move.end_square);
	// A player can never be in check right after they've moved
	in_check = false;
}

bool Player::checked_other_player(const Move &move) const
{
	const Move possible_check_move(move.end_square, other_player->king_location());
	return is_valid_move(possible_check_move);
}

void Player::call_check()
{
	other_player->in_check = true;
	cout << "Check!" << endl;
}

bool Player::in_check_mate()
{
	return !(king_can_escape() || can_block_capture_path());
}


bool Player::can_block_capture_path()
{
	vector<Square*> path = king_capture_path();

	for (auto &piece: pieces){
		for (auto &square: path){
			Move move(*piece->get_square(), *square);

			if (is_valid_move(move) && !move_puts_player_in_check(move))
			{
				return true;
			}
		}
	}

	return false;
}

vector<Square*> Player::king_capture_path()
{
	// Return a vector with squares that would be used to attack king
	vector<Square*> path;

	for (auto &piece: other_player->pieces)
	{
		Move move(*piece->get_square(), king_location());
		if (is_valid_move(move)){
			path.push_back(piece->get_square());
			vector<Square*> piece_path = squares_on_move_path(move);
			path.insert(path.end(), piece_path.begin(), piece_path.end());
		}
	}

	return path;
}

bool Player::king_can_escape()
{
	for (int i = -1; i <= 1; ++ i){
		for (int j = -1; j <= 1; ++j){

			if ((king_location().X + i >= 0 && king_location().X + i <= 7)
			&&  (king_location().Y + j >= 0 && king_location().Y + j <= 7))
			{
				
				const Move move(king_location(), board[king_location().X+i][king_location().Y+j]);
				if (is_valid_move(move) && !move_puts_player_in_check(move)){
					return true;
				}
			}
		}
	}
	return false;
}

void Player::introduce_other_player(Player *other)
{
	other_player = other;
}

Player * Player::get_other_player()
{
	return other_player;
}

Player::Move Player::get_input_move() const
{
	cout << "Enter a move in the format (x,y) (x,y) e.g. (4,1) (4,3)" << endl;
	string first, second;
	static regex rgx("\\(([0-7])\\,([0-7])\\)"); // e.g. (0,1)
	while (true)
	{
		cin >> first >> second;

		if (regex_match(first, rgx) && regex_match(second, rgx))
		{
			smatch start, end;
			regex_search(first, start, rgx);
			regex_search(second, end, rgx);

			const int start_x = stoi(start[1]);
			const int start_y = stoi(start[2]);
			const int end_x = stoi(end[1]);
			const int end_y = stoi(end[2]);

			return Move(board[start_x][start_y], board[end_x][end_y]);
		}

		else cout << "Invalid Input\nEnter a move in the format (x,y) (x,y) e.g. (4,1) (4,3)" << endl;
		
	}
}

bool Player::take_turn()
{
	// Return false if the player cannot make a move because they are in checkmate
	if (in_check && in_check_mate()) return false;
	bool turn_over = false;
	while (!turn_over)
	{
		Move move = get_input_move();
		if (is_valid_move(move))
		{
			if (!move_puts_player_in_check(move))
			{
				move_piece(move);
				if (checked_other_player(move)) call_check();
				turn_over = true;
			}
			else cout << "Invalid Move: You can't put yourself in check" << endl;
		}
	}
	return true;
}



