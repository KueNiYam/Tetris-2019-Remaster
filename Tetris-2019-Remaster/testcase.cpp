#include "testcase.h"

namespace testcase
{
	void tetris_test()
	{
		Tetris tetrisField = Tetris(500);
		tetrisField.test();
		// tetrisField.start();
		// tetrisField.update();
	}

	void console_test()
	{
		console::hide_cursor();
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				console::move_cursor(i, j);
				console::sleep_one_frame();
			}
		}
		std::cout << "z" << std::endl;
		console::sleep(3000);
	}

	void input_test()
	{
		while (true)
		{
			console::sleep(console::frame_ms);
			console::Keycode keycode = console::keydown();
			if (keycode == console::up)
			{
				std::cout << "up" << std::endl;
			}
			else if (keycode == console::down)
			{
				std::cout << "down" << std::endl;
			}
			else if (keycode == console::left)
			{
				std::cout << "left" << std::endl;
			}
			else if (keycode == console::right)
			{
				std::cout << "right" << std::endl;
			}
			else if (keycode.first == console::esc)
			{
				std::cout << "esc" << std::endl;
			}
			else if (keycode.first == console::spacebar)
			{
				std::cout << "spacebar" << std::endl;
			}
		}
	}
}