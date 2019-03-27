#include "Player.h"
#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
	Board board;

	Player p1(true, board);
	Player p2(false, board);
	p1.introduce_other_player(&p2);
	p2.introduce_other_player(&p1);
	Player* players[2] = {&p1, &p2};
	

	int current_player = 0;
	board.display();

	while (players[current_player]->take_turn())
	{		
		current_player = (current_player + 1) % 2;
		board.display();
	}
	return 0;
}