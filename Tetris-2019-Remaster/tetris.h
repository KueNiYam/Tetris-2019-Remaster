#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include "console.h"

class TetrisField
{
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

	Array2d map;
	Array2d node;
	Array2d graphic;
	Array2d pregraphic;

	void reset_cursor();
	void init_map();
	void init_map(Array2d& map) const;
	std::vector<bool> get_empty_map_row() const;
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
	std::set<int> check_break_rows() const;
	bool is_gameover() const;
	bool can_move_node(const Direction) const;
	bool move_node(const Direction);
	int next_count(const int) const;
	void deepcopy(Array2d&, const Array2d&);
	std::string get_shape_string(const bool) const;
public:
	const int node_size = 4;
	const int field_width = 18;
	const int field_height = 28;
	const int ingame_width = 10;
	const int ingame_height = 20;
	const int ingame_col_start = 4;
	const int ingame_col_end = ingame_col_start + ingame_width; //< this not include this point like iterator end()
	const int ingame_row_start = 4;
	const int ingame_row_end = ingame_row_start + ingame_height; //< this not include this point like iterator end()
	const Cursor start_point = { 0, (int)(field_width / 2) - 2 };
	TetrisField();
	TetrisField(int);

	void start();
	void update();
	void title(const std::string& input) const;
	std::string array2d_to_string(const Array2d&) const;
	void test();
};
