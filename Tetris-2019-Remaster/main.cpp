#include "main.h"

int main()
{
	Tetris tetrisGame(10);
	tetrisGame.title(std::string("Tetris Remaster 2019 By Kuenhwi"));
	tetrisGame.start();
	tetrisGame.update();

	return 0;
}