extern "C"
{
#include "gnugo.h"
}
#include <time.h>
#include <iostream>

#define BOARD_SIZE 7

void printBoard()
{
	int board[19][19];
	gnugo_get_board(board);
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (board[i][j])
			{
				case EMPTY:
					std::cout << " . ";
					break;
				case WHITE:
					std::cout << " O ";
					break;
				case BLACK:
					std::cout << " X ";
					break;
				default:
					std::cout << " " << board[i][j] << " ";
			}
		}
		
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
}

bool computer_player_move(int color)
{
	int i, j;
	int move_val;
	bool pass;
  
	// Generate computer move
	move_val = gnugo_genmove(&i, &j, color);
	
	// Make move
	pass = gnugo_is_pass(i, j);
	gnugo_play_move(i, j, color);
	
	return pass;
}

int main()
{
	// initialize GNU Go engine.
	init_gnugo(8, time(0));
	gnugo_clear_board(BOARD_SIZE);
	int passes = 0;
	int firstPlayerColor = WHITE;
	
	// play until both players pass
	while (passes < 2)
	{
		// computer player 1 moves
		if (computer_player_move(firstPlayerColor))
			passes++;
		
		// computer player 2 moves
		if (computer_player_move(OTHER_COLOR(firstPlayerColor)))
			passes++;
		else
			passes = 0;
			
		printBoard();
	}
	
	return 0;
}
