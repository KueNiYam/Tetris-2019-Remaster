# Tetris 2019 Remaster
## Introduction
Remaster version of my freshman project tetris 2014.

## Video Clip
[![Video Label](http://img.youtube.com/vi/pjGOYjE6QsY/0.jpg)](https://youtu.be/pjGOYjE6QsY?t=0s)

https://youtu.be/pjGOYjE6QsY?t=0s

## Requirements
**OS**
 - Windows

## Installation
**If you use git bash or wsl,**
``` 
git clone https://github.com/KueNiYam/Tetris-2019-Remaster
```
**else, just click "Clone or download" in https://github.com/KueNiYam/Tetris-2019-Remaster.**

## Improvements
 - Improve input response rate
 - Change block from 3\*3 to 4\*4
 - Resolve memory leak
 - Remove output delay

------
# Documentation
## Example Usage
```c++
int main()
{
    TetrisField tetrisGame(10);
    tetrisGame.title(std::string("Tetris Remaster 2019 By Kuenhwi"));
    tetrisGame.start();
    tetrisGame.update();
    
    return 0;
}
```
------

## Namespace console
```c++
struct Keycode {
    int first;
    int second;
    
    ...
};
```
> **Brief**
 
> - The instance saves an ascii code of char. Only special character has a second ascii code.
	
```c++
Keycode::Keycode();
Keycode::Keycode(int first, int second);
```

> **Brief**

> - Constructor of struct Keycode.
 
> **Param**

> - Initialize the field to parameter.
 
```c++
bool Keycode::operator== (const struct Keycode&);
```

> **Brief**

> - Compare values not references.
 
```c++
const int frame_ms = 33;
```

> **Brief**

> - Time per frame.

```c++
const struct Keycode up = {224, 72};
const struct Keycode down = {224, 80};
const struct Keycode left = {224, 75};
const struct Keycode right = {224, 77};
const int esc = 27;
const int spacebar = 32;
```

> **Brief**

> - Keycode value of specific keys.

```c++
void hide_cursor();
```

> **Brief**

> - Hide cursor.

```c++
void move_cursor(const int row, const int col);
```

> **Brief**

> - Move cursor.

> **Param**

> - Destination row and col.

```c++	
void sleep(const int ms);
```

> **Brief**

> - Sleep.

> **Param**

> - Time for sleep.

```c++
void sleep_one_frame();
```

> **Brief**

> - Sleep for time of one frame(const int frame_ms).

```c++
Keycode keydown();
```

> **Return**
>  - When key down, check ascii code and return this using Keycode.
>  - else {0, 0}

------

## Class Tetris
### @Private FIELD

```c++
typedef std::vector<std::vector<bool>> Array2d;
```

> **Brief**
>  - Array2d is data format of block or map.

```c++
struct Cursor
{
	int row;
	int col;
	...
};
```

> **Brief**

>  - Cursor is the top left of block.
>  - Block's coordinate is represented using cursor in map.
		
```c++
Cursor::Cursor(int row, int col);
Cursor::Cursor();
Cursor::Cursor(const struct Cursor& cursor);
```

> **Brief**

>  - Cursor's constructor.

```c++
enum class Direction
{
	down, left, right
};
```

> **Brief**
>  - Direction means the direction to move.

```c++
Cursor cursor;
```
> **Brief**
>  - Cursor's instance.

```c++
int cycle;
```
> **Brief**
>  - cycle means frame time interval between outputs. 

```c++
Array2d* map;
```
> **Brief**
>  - This points to map data.
>  - map data is divided into three parts: the hidden part, the wall, and the game internal space.
 
> **Warning**
>  - When using this, be careful about memory leak.
>  - This should points meaningful value. Not nullptr or deallocated memory.

```c++
Array2d node;
```
> **Brief**
>  - This points to map data.

> **Warning**
>  - When using this, be careful about memory leak.
>  - This should points meaningful value. Not nullptr or deallocated memory.

```c++
Array2d graphic;
```
> **Brief**
>  - This means what will be printout.
>  - This is the result of calculating a map and a node.

```c++
Array2d pregraphic;
```
> **Brief**
>  - Previous graphic.
 
> **See** 
>  - "Array2d Tetris::graphic"

### @Public FIELD
```c++
static const int node_size;
```
> **Brief**
>  - This means size of block.
 
```c++
static const int field_width;
static const int field_height;
```
> **Brief**
>  - These mean width and height of a entire "Array2d Tetris::map".

```c++
static const int ingame_width;
static const int ingame_height;
```
> **Brief**
>  - These mean width and height of map's internal game space.

```c++
static const int ingame_col_start;
static const int ingame_col_end;
static const int ingame_row_start;
static const int ingame_row_end;
```
> **Brief**
>  - These means [starting index, ending index).

```c++
static const Cursor start_point;
```
> **Brief**
>  - This means the position where the block is created.
 
### @Private METHOD
```c++
void reset_cursor();
```
> **Brief**

>  - This set cursor(block's position) to starting position.
 
```c++
void init_map();
void init_map(Array2d& map) const;
```
> **Brief**
>  - These create the basic foundation of an empty map.
 
> **Exception**
>  - The \*Tetris::map or param map should be empty. In other words, "(\*map).empty()" should be true.

```c++
std::vector<bool> *get_empty_map_row() const;
```
> **Return**
>  - This return an array of empty map data.
>  - For example, {1, 1, 1, 1, 0, 0, ... , 0, 1, 1, 1, 1}
 
> **Warning**
>  - You should deallocate return pointer!!
 
```c++
void init_node();
void init_node(Array2d&) const;
```
> **Brief**
>  - These create the basic foundation of an empty block.
>  - These don't include a shape of block.

> **Exception**
>  - The Tetris::node or param node should be empty. In other words, "node.empty()" should be true.

```c++
void set_node_shape();
void set_node_shape(const int);
```
> **Brief**
>  - Set node's shape.

> **Param**
>  - \[0, 7): The shape number.
>  - If no param, This randomly determine the shape number.

> **Exception**
>  - "Tetris::is_node(node)" should be true.

```c++
void clear_node();
```
> **Brief**
>  - This erase the shape of node. In other words, set the node's interval values to zero.

> **Exception**
>  - "Tetris::is_node(node)" should be true.

```c++
bool can_rotate_node(const Array2d&) const;
```

> **Brief**
>  - Check node can rotate in the map state.
 
> **Param**
>  - The shape after rotation.

```c++
void rotate_node();
```
> **Brief**
>  - If can rotate node, rotate node. In other words, set node to right rotation matrix of node.
>  - else, nothing.

> **Exception**
>  - "Tetris::is_node()" should be true.
 
```c++
bool is_node(const Array2d&) const;
```
> **Return**
>  - If size fits block specification, true.
>  - else, false
 
```c++
void init_graphic();
```
> **Brief**
>  - Just deep copy "map" data to "graphic".

```c++
void render_graphic();
```
> **Brief**
>  - This calculate "map" and "node" to printout, and save result to "Array2d Tetris::graphic".
>  - The previous "graphic" is saved to "Array2d Tetris::pregraphic".

```c++
void print_out(const bool) const;
```
> **Brief**
>  - This print out the game on the screen.
 
> **Param**
>  - true -> print out whole.
>  - false -> print out partially(only changed parts).

```c++
void apply_to_map();
```
> **Brief**
>  - Copy "graphic" to "map".
>  - This means node lose control of the player and be part of the map.

```c++
void break_floor(const std::set<int>&);
```
> **Brief**
>  - Break floor if can.

> **Usage**
>  - Use after "apply_to_map()".
>  - This don't need to check condition wherther floor should be breaked or no.

```c++
std::set<int> *check_break_rows() const;
```
> **Return**
>  - Set of row numbers where should break

> **Warning**
>  - You should deallocate return pointer!!
 
```c++
bool is_gameover() const;
```
> **Brief**
>  - Check the gameover.
 
> **Usage**
>  - Use after "break_floor()"

```c++
bool can_move_node(const Direction) const;
```
> **Return**
>  - If can move node, true.
>  - else, false.

> **Param**
>  - Where to move.

```c++
bool move_node(const Direction);
```
> **Brief**
>  - This move nodes. In other words, Change "Cursor Tetris::cursor".

> **Param**
>  - Where to move.
 
> **Return**
>  - If can't move, false.
>  - else, true.

```c++
int next_count(const int) const;
```
> **Return**
>  - The frame of the number for each cycle.
>  - Range `[0, cycle).
 
```c++
std::string get_shape_string(const bool) const;
```
> **Param**
>  - true -> return '■'
>  - false -> return '　' (In korean keyboard, 'ㄱ' + 한자 + 1)

### @Public METHOD:





------
