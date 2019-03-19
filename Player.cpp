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
	const ChessPiece * piece_to_move = move.start_square.get_piece();
	if (!piece_to_move->color == color) return false;
	if (!piece_to_move->is_in_play()) return false;
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

bool Player::move_puts_player_in_check(const Move &move) 
{	
	// Temporarily make the move, and see if it gives access to the 
	// king to any of the other players pieces
	ChessPiece *current_piece_at_destination = move.end_square.get_piece();
	move.start_square.get_piece()->move_to(move.end_square);
	bool results_in_check = false;
	
	for (auto &piece: other_player->pieces)
	{
		if (piece->is_in_play())
		{
			const Move potential_check_move(*(piece->get_square()), king_location());
			if (other_player->is_valid_move(potential_check_move)){
				results_in_check = true;
			}
		}
	}

	move.end_square.get_piece()->move_to(move.start_square);
	cout << move.end_square.is_empty();
	if (current_piece_at_destination)
	{
		current_piece_at_destination->place(move.end_square);
	}

	return results_in_check;
}

void Player::move_piece(const Move &move)
{
	move.start_square.get_piece()->move_to(move.end_square);
}

void Player::introduce_other_player(Player *other)
{
	other_player = other;
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
			cout << start_x << start_y << ' ' << end_x << end_y << endl;

			return Move(board[start_x][start_y], board[end_x][end_y]);
		}

		else cout << "Invalid Input\nEnter a move in the format (x,y) (x,y) e.g. (4,1) (4,3)" << endl;
		
	}
}

void Player::take_turn()
{
	bool turn_over = false;
	while (!turn_over)
	{
		Move move = get_input_move();
		if (is_valid_move(move))
		{
			if (!move_puts_player_in_check(move))
			{
				move_piece(move);
				turn_over = true;
			}
			else cout << "Invalid Move: You can't put yourself in check" << endl;
		}
		else cout << "Invalid Move" << endl;
	}
}



