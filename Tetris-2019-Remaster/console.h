#pragma once
#include <Windows.h>
#include <thread>
#include <chrono>
#include <conio.h>

namespace console
{
	struct Keycode {
		int first;
		int second;

		Keycode();
		Keycode(int, int);
		bool operator== (const struct Keycode&);
	};

	const int frame_ms = 33;
	const struct Keycode up = {224, 72};
	const struct Keycode down = {224, 80};
	const struct Keycode left = {224, 75};
	const struct Keycode right = {224, 77};
	const int esc = 27;
	const int spacebar = 32;

	void hide_cursor();
	void move_cursor(const int row, const int col);
	void sleep(const int ms);
	void sleep_one_frame();
	Keycode keydown();
}