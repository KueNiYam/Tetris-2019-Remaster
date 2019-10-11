#include "tetris.h"

const int Tetris::node_size = 4;
const int Tetris::field_width = 18;
const int Tetris::field_height = 28;
const int Tetris::ingame_width = 10;
const int Tetris::ingame_height = 20;
const int Tetris::ingame_col_start = 4;
const int Tetris::ingame_col_end = 14;
const int Tetris::ingame_row_start = 4;
const int Tetris::ingame_row_end = 24;

const Tetris::Cursor Tetris::start_point = { 0, (int)(field_width / 2) - 2 };

Tetris::Cursor::Cursor()
{
	row = 0;
	col = 0;
}

Tetris::Cursor::Cursor(const struct Cursor& cursor)
{
	col = cursor.col;
	row = cursor.row;
}

Tetris::Cursor::Cursor(int row, int col)
{
	this->row = row;
	this->col = col;
}

void Tetris::reset_cursor()
{
	cursor = start_point;
}

void Tetris::init_map()
{
	init_map(*map);
}

void Tetris::init_map(Array2d& map) const
{
	if (!map.empty())
	{
		std::cerr << "init_map(): param must be empty array2d" << std::endl;
		exit(1);
	}

	std::vector<bool> area1(field_width, false);
	std::vector<bool> area2(field_width, true);

	for (unsigned int i = 0; i < area1.size(); i++)
	{
		if (i < ingame_col_start)
			area1[i] = true;
		else if (i >= ingame_col_end)
			area1[i] = true;
	}

	for (unsigned int i = 0; i < field_height; i++)
	{
		if (i < ingame_row_end)
			map.push_back(area1);
		else
			map.push_back(area2);
	}
}

// @warning you should deallocate return pointer!!
std::vector<bool> *Tetris::get_empty_map_row() const
{
	try {
		std::vector<bool>* answer = new std::vector<bool>;
		for (int i = 0; i < ingame_col_start; i++)
			answer->push_back(true);
		for (int i = ingame_col_start; i < ingame_col_end; i++)
			answer->push_back(false);
		for (int i = ingame_col_end; i < field_width; i++)
			answer->push_back(true);
		return answer;
	}
	catch(const std::bad_alloc& e){
		std::cerr << "TetrisField::get_empty_map_row(): dynamic allocation error" << std::endl;
		exit(1);
	}
}

// @brief init this->current_node to node
void Tetris::init_node()
{
	init_node(*node);
}

// @brief init array2d to node
// @param new_array2d is 2d array that has no size
void Tetris::init_node(Array2d& other) const
{
	if (!other.empty())
	{
		std::cerr << "init_node(): param must be empty array2d" << std::endl;
		exit(1);
	}

	std::vector<bool> temp;
	for (int i = 0; i < node_size; i++)
		temp.push_back(false);
	for (int i = 0; i < node_size; i++)
		other.push_back(temp);
}

void Tetris::set_node_shape()
{
	set_node_shape(rand() % 7);
}

// @lparam [0,7)
void Tetris::set_node_shape(const int shape_num)
{
	if (!is_node(*node))
	{
		std::cerr << "set_node_shape(): lparam must be node" << std::endl;
		exit(1);
	}

	if (shape_num < 0 || shape_num >= 7)
	{
		std::cerr << "set_node_shape(): rparam must be [0,7)" << std::endl;
		exit(1);
	}

	switch (shape_num)
	{
	case 0:
		for (unsigned int i = 0; i < node->size(); i++)
			(*node)[i][1] = true;
		break;
	case 1:
		(*node)[0][2] = true;
		(*node)[1][2] = true;
		(*node)[2][1] = true;
		(*node)[2][2] = true;
		break;
	case 2:
		(*node)[0][1] = true;
		(*node)[1][1] = true;
		(*node)[2][1] = true;
		(*node)[2][2] = true;
		break;
	case 3:
		(*node)[0][1] = true;
		(*node)[1][1] = true;
		(*node)[1][2] = true;
		(*node)[2][2] = true;
		break;
	case 4:
		(*node)[1][1] = true;
		(*node)[1][2] = true;
		(*node)[2][1] = true;
		(*node)[2][2] = true;
		break;
	case 5:
		(*node)[0][2] = true;
		(*node)[1][2] = true;
		(*node)[1][1] = true;
		(*node)[2][1] = true;
		break;
	case 6:
		(*node)[1][0] = true;
		(*node)[1][1] = true;
		(*node)[1][2] = true;
		(*node)[2][1] = true;
		break;
	}
}

// @brief make all node value false(0)
void Tetris::clear_node()
{
	if (!is_node(*node))
	{
		std::cerr << "clear_node(): param must be node" << std::endl;
		exit(1);
	}

	for (unsigned int i = 0; i < node->size(); i++)
		for (unsigned int j = 0; j < node->front().size(); j++)
			(*node)[i][j] = false;
}

bool Tetris::can_rotate_node(const Array2d& next_shape) const
{
	for (int i = 0; i < node_size; i++)
	{
		for (int j = 0; j < node_size; j++)
		{
			if ((*map)[cursor.row + i][cursor.col + j] & next_shape[i][j])
				return false;
		}
	}

	return true;
}

// @brief rotate node to right
void Tetris::rotate_node()
{
	if (!is_node(*node))
	{
		std::cerr << "rotate_node(): param must be node" << std::endl;
		exit(1);
	}

	try
	{
		Array2d* new_node = new Array2d;
		Array2d* temp = nullptr;
		init_node(*new_node);

		int new_i, new_j;
		for (unsigned int i = 0; i < node->size(); i++)
		{
			for (unsigned int j = 0; j < node->front().size(); j++)
			{
				new_i = j;
				new_j = node->size() - i - 1;
				(*new_node)[new_i][new_j] = (*node)[i][j];
			}
		}

		if (can_rotate_node(*new_node))
		{
			temp = node;
			node = new_node;
			delete temp;
			temp = nullptr;
		}
		else
		{
			delete new_node;
			new_node = nullptr;
		}
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "TetrisField::rotate_node(): dynamic allocation error" << std::endl;
		exit(1);
	}
}

bool Tetris::is_node(const Array2d& node) const
{
	if (node.size() != node_size)
		return false;
	if (node.front().size() != node_size)
		return false;

	return true;
}

void Tetris::init_graphic()
{
	graphic = *map;
}

void Tetris::render_graphic()
{
	pregraphic = graphic;
	init_graphic();

	for (int i = cursor.row; i < cursor.row + node_size; i++)
	{
		for (int j = cursor.col; j < cursor.col + node_size; j++)
		{
			graphic[i][j] = (graphic[i][j] | (*node)[i - cursor.row][j - cursor.col]);
		}
	}
}

// @param
// true -> print out whole
// false -> print out partially
void Tetris::print_out(const bool whole) const
{
	if (whole)
	{
		for (unsigned int i = ingame_row_start; i < ingame_row_end + 1; i++)
		{
			for (unsigned int j = ingame_col_start - 1; j < ingame_col_end + 1; j++)
			{
				console::move_cursor(i, j);
				std::cout << get_shape_string(graphic[i][j]);
			}
		}
	}
	else
	{
		for (unsigned int i = ingame_row_start; i < ingame_row_end; i++)
		{
			for (unsigned int j = ingame_col_start; j < ingame_col_end; j++)
			{
				if (graphic[i][j] ^ pregraphic[i][j])
				{
					console::move_cursor(i, j);
					std::cout << get_shape_string(graphic[i][j]);
				}
			}
		}
	}
}

// @brief graphic to map
void Tetris::apply_to_map()
{
	*map = graphic;
}

// @usage 
// use after apply_to_map
// don't need to check condition
void Tetris::break_floor(const std::set<int>& break_rows)
{
	if (break_rows.size() == 0)
		return;

	try {
		Array2d* new_map = new Array2d;
		Array2d* old_map = map;
		for (unsigned int i = 0; i < break_rows.size(); i++)
		{
			try
			{
				std::vector<bool>* empty_row = get_empty_map_row();
				new_map->push_back(*empty_row);
				delete empty_row;
				empty_row = nullptr;
			}
			catch(const std::bad_alloc &e)
			{
				std::cerr << "TetrisField::break_floor(): dynamic allocation error" << std::endl;
				exit(1);
			}
		}

		for (unsigned int i = 0; i < map->size(); i++)
		{
			if (break_rows.find(i) == break_rows.end()) //< no exist
				new_map->push_back((*map)[i]);
		}
		map = new_map;
		delete old_map;
		old_map = nullptr;
	}
	catch (const std::bad_alloc & e) {
		std::cerr << "TetrisField(): dynamic allocation error" << std::endl;
		exit(1);
	}
}

// @return where should break
// @warning you should delete return pointer!!
std::set<int> *Tetris::check_break_rows() const
{
	try
	{
		std::set<int>* break_rows = new std::set<int>;
		for (int i = cursor.row; i < cursor.row + 4; i++)
		{
			if (i >= ingame_row_end)
				continue;
			for (int j = ingame_col_start; j < ingame_col_end; j++)
			{
				if (!(*map)[i][j])
					break;
				if (j == ingame_col_end - 1)
					break_rows->insert(i);
			}
		}

		return break_rows;
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "TetrisField::check_break_rows(): dynamic allocation error" << std::endl;
		exit(1);
	}
	
}

// @usage use after break_floor()
bool Tetris::is_gameover() const
{
	for (int i = ingame_col_start; i < ingame_col_end; i++)
	{
		if ((*map)[ingame_row_start - 1][i])
			return true;
	}

	return false;
}

bool Tetris::can_move_node(const Direction direction) const
{
	struct Cursor next = cursor;

	switch (direction)
	{
	case Tetris::Direction::down:
		next.row += 1;
		break;
	case Tetris::Direction::left:
		next.col -= 1;
		break;
	case Tetris::Direction::right:
		next.col += 1;
		break;
	}

	for (int i = next.row; i < next.row + node_size; i++)
	{
		for (int j = next.col; j < next.col + node_size; j++)
		{
			if ((*map)[i][j] & (*node)[i - next.row][j - next.col])
				return false;
		}
	}

	return true;
}

bool Tetris::move_node(const Direction direction)
{
	if (!can_move_node(direction))
		return false;

	switch (direction)
	{
	case Tetris::Direction::down:
		cursor.row += 1;
		break;
	case Tetris::Direction::left:
		cursor.col -= 1;
		break;
	case Tetris::Direction::right:
		cursor.col += 1;
		break;
	}

	return true;
}

int Tetris::next_count(const int count) const
{
	if (count < cycle)
		return count + 1;
	else
		return 0;
}

void Tetris::deepcopy(Array2d& destination, const Array2d& source)
{
	destination.clear();
	std::vector<bool> temp(source.front().size(), false);

	for (unsigned int i = 0; i < source.size(); i++)
		destination.push_back(temp);

	for (unsigned int i = 0; i < source.size(); i++)
		for (unsigned int j = 0; j < source.front().size(); j++)
			destination[i][j] = source[i][j];
}

// @return
// true -> '¡á'
// false -> '¡¡'
std::string Tetris::get_shape_string(const bool value) const
{
	if (value)
		return std::string("¡á");
	else
		return std::string("¡¡");
}

Tetris::Tetris()
{
	try {
		map = new Array2d;
		node = new Array2d;
	}
	catch (const std::bad_alloc & e)
	{
		std::cerr << "TetrisField::TetrisField(): dynamic allocation error" << std::endl;
		exit(1);
	}

	reset_cursor();
	cycle = 10;
	init_map();
	init_node();
	init_graphic();
	srand((unsigned int)time(NULL));
}

// @param the cycle of game proceed
Tetris::Tetris(int cycle) : Tetris()
{
	this->cycle = cycle;
}

Tetris::~Tetris()
{
	delete map;
	map = nullptr;
	delete node;
	node = nullptr;
}

void Tetris::start()
{
	console::hide_cursor();

	set_node_shape();
	print_out(true);
}

void Tetris::update()
{
	int count = 0;
	while (true)
	{
		console::sleep_one_frame();
		console::Keycode keycode = console::keydown();
		if (keycode == console::up)
		{
			rotate_node();
		}
		else if (keycode == console::down)
		{
			move_node(Direction::down);
		}
		else if (keycode == console::left)
		{
			move_node(Direction::left);
		}
		else if (keycode == console::right)
		{
			move_node(Direction::right);
		}
		else if (keycode.first == console::esc)
		{
			break;
		}
		else if (keycode.first == console::spacebar)
		{
			while (move_node(Direction::down))
			{
				/* empty */
			}
		}

		render_graphic();

		if (count == 0)
		{
			if (!move_node(Direction::down))
			{
				apply_to_map();
				try
				{
					std::set<int>* should_break_rows = check_break_rows();
					break_floor(*should_break_rows);
					delete should_break_rows;
					should_break_rows = nullptr;
				}
				catch (const std::bad_alloc& e)
				{
					std::cerr << "TetrisField::update(): dynamic allocation error" << std::endl;
					exit(1);
				}
				
				if (is_gameover())
					break;
				reset_cursor();
				clear_node();
				set_node_shape();
			}
		}

		print_out(false);
		count = next_count(count);
	}
}

// @warning maybe it not work correctly if input is long
void Tetris::title(const std::string& input) const
{
	std::string str;
	// int pre_space = (field_width * 2 - input.size()) / 2;
	int pre_space = (field_width * 2 - input.size());
	pre_space /= 2;
	for (int i = 0; i < pre_space; i++)
	{
		str.append(" ");
	}
	str.append(input);
	std::cout << str;
}

// @brief ignore this
void Tetris::test()
{
	start();
	update();
}
