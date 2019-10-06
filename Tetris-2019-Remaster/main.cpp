#include "main.h"

int main()
{
	TetrisField tetrisGame(10);
	tetrisGame.title(std::string("Tetris Remaster 2019 By Kuenhwi"));
	tetrisGame.start();
	tetrisGame.update();

	return 0;
}