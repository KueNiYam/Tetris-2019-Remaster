#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include "console.h"

class Tetris
{
#pragma region Attribute
private:
	typedef std::vector<std::vector<bool>> Array2d;

	struct Cursor
	{
		int row;
		int col;

		Cursor();
		Cursor(const struct Cursor&);
		Cursor(int, int);
	};
	enum class Direction
	{
		down, left, right
	};

	Cursor cursor;
	int cycle; //< print out cycle

	Array2d* map;

	Array2d node;
	Array2d graphic;
	Array2d pregraphic;
public:
	static const int node_size;
	static const int field_width;
	static const int field_height;
	static const int ingame_width;
	static const int ingame_height;
	static const int ingame_col_start;
	static const int ingame_col_end; //< this not include this point like iterator end()
	static const int ingame_row_start;
	static const int ingame_row_end; //< this not include this point like iterator end()
	static const Cursor start_point;
#pragma endregion
#pragma region Method
private:
	void reset_cursor();
	void init_map();
	void init_map(Array2d& map) const;
	std::vector<bool> *get_empty_map_row() const;
	void init_node();
	void init_node(Array2d&) const;
	void set_node_shape();
	void set_node_shape(const int);
	void clear_node();
	bool can_rotate_node(const Array2d&) const;
	void rotate_node();
	bool is_node(const Array2d&) const;
	void init_graphic();
	void render_graphic();
	void print_out(const bool) const;
	void apply_to_map();
	void break_floor(const std::set<int>&);
	std::set<int> *check_break_rows() const;
	bool is_gameover() const;
	bool can_move_node(const Direction) const;
	bool move_node(const Direction);
	int next_count(const int) const;
	void deepcopy(Array2d&, const Array2d&);
	std::string get_shape_string(const bool) const;
public:
	Tetris();
	Tetris(int);
	~Tetris(); // Important!!!
	void start();
	void update();
	void title(const std::string& input) const;
	void test();
#pragma endregion
};
