#include "console.h"

namespace console
{
	Keycode::Keycode()
	{
		first = 0;
		second = 0;
	}

	Keycode::Keycode(int first, int second)
	{
		this->first = first;
		this->second = second;
	}

	bool Keycode::operator==(const Keycode& operand)
	{
		if (this->first == operand.first)
			if (this->second == operand.second)
				return true;
		return false;
	}

	void hide_cursor()
	{
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	void move_cursor(const int row, const int col)
	{
		COORD Cur;
		Cur.X = col * 2;
		Cur.Y = row;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	}

	void sleep(const int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void sleep_one_frame()
	{
		sleep(frame_ms);
	}

	Keycode keydown()
	{
		struct Keycode buffer(0,0);
		if (_kbhit())
		{
			buffer.first = _getch();
			if (buffer.first == 224)
				buffer.second = _getch();

		}

		return buffer;
	}

}