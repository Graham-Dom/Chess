#include "ChessPiece.h"
#include "Square.h"
#include <cassert>
#include <iostream>
using namespace std;

int main(){

	Square s(0,0);
	Square s1(1,1);
	Square s2(0,1);
	Square s3(0,2);
	Square s4(1,0);
	Square s5(4,4);
	Square s6(0,3);
	Square s7(1,2);
	
	// PAWN TESTS
	Pawn p(true);
	Pawn p1(false);
	p.place(s);
	p1.place(s7);
	cout << p.letter_representation() << endl;
	cout << p1.letter_representation() << endl;

	assert(!p.is_valid_move(s));
	assert(!p.is_valid_move(s1));
	assert(p.is_valid_move(s2));
	assert(p.is_valid_move(s3));
	assert(!p.is_valid_move(s4));
	assert(!p.is_valid_move(s5));
	assert(!p.is_valid_move(s6));

	p.move_to(s2);

	assert(!p.is_valid_move(s));
	assert(p.is_valid_move(s3));
	assert(!p.is_valid_move(s4));
	assert(!p.is_valid_move(s5));
	assert(!p.is_valid_move(s6));
	assert(p.is_valid_move(s7));

	s.remove_piece();
	s7.remove_piece();
	p.remove_from_play();
	p1.remove_from_play();

	assert(s.is_empty());
	assert(s7.is_empty());

	// Knight Tests
	Knight k1(true);
	k1.place(s5);
	Square s8(5,5);
	Square s9(5,6);
	Square s10(6,5);

	assert(!k1.is_valid_move(s8));
	assert(k1.is_valid_move(s9));
	assert(k1.is_valid_move(s10));

	s5.remove_piece();
	k1.remove_from_play();

	// Bishop Tests
	Bishop b(true);
	b.place(s5);
	assert(b.is_valid_move(s8));
	assert(b.is_valid_move(s));
	assert(!b.is_valid_move(s9));
	assert(!b.is_valid_move(s10));

	s5.remove_piece();
	b.remove_from_play();

	// Rook Tests
	Rook r(true);
	r.place(s8);
	assert(r.is_valid_move(s9));
	assert(r.is_valid_move(s10));
	assert(r.is_valid_move(Square(5,0)));
	assert(r.is_valid_move(Square(0,5)));
	assert(!r.is_valid_move(s5));
	s8.remove_piece();
	r.remove_from_play();

	// Queen Tests
	Queen q(true);
	q.place(s8);
	assert(q.is_valid_move(s9));
	assert(q.is_valid_move(s10));
	assert(q.is_valid_move(Square(5,0)));
	assert(q.is_valid_move(Square(0,5)));
	assert(q.is_valid_move(s5));
	assert(q.is_valid_move(s));
	assert(!q.is_valid_move(Square(6,7)));

	s8.remove_piece();
	q.remove_from_play();


	// King Tests
	King k(true);
	k.place(s8);
	assert(k.is_valid_move(s9));
	assert(k.is_valid_move(s10));
	assert(!k.is_valid_move(Square(5,0)));
	assert(!k.is_valid_move(Square(0,5)));
	assert(k.is_valid_move(s5));
	assert(!k.is_valid_move(s));
	assert(!k.is_valid_move(Square(6,7)));
	assert(!k.is_valid_move(s8));
	s8.remove_piece();
	k.remove_from_play();

	return 0;
}