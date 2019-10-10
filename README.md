# Tetris 2019 Remaster
## Introduction
Remaster version of my freshman project tetris 2014.

## Video Clip
[![Video Label](http://img.youtube.com/vi/pjGOYjE6QsY/0.jpg)](https://youtu.be/pjGOYjE6QsY?t=0s)

https://youtu.be/pjGOYjE6QsY?t=0s

## Installation
    git clone https://github.com/KueNiYam/Tetris-2019-Remaster

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
 **Brief**
 
 - The instance saves an ascii code of char. Only special character has a second ascii code.
	
```c++
    Keycode::Keycode();
    Keycode::Keycode(int first, int second);
```

**Brief**

 - Constructor of struct Keycode.
 
**Param**

 - Initialize the field to parameter.
 
```c++
	bool Keycode::operator== (const struct Keycode&);
```

**Brief**

 - Compare values not references.
 
```c++
const int frame_ms = 33;
```

**Brief**

 - Time per frame.

```c++
const struct Keycode up = {224, 72};
const struct Keycode down = {224, 80};
const struct Keycode left = {224, 75};
const struct Keycode right = {224, 77};
const int esc = 27;
const int spacebar = 32;
```

**Brief**

- Keycode value of specific keys.

```c++
void hide_cursor();
```

**Brief**

- Hide cursor.

```c++
void move_cursor(const int row, const int col);
```

**Brief**

- Move cursor.

**Param**

- Destination row and col.

```c++	
void sleep(const int ms);
```

**Brief**

- Sleep.

**Param**

- Time for sleep.

```c++
void sleep_one_frame();
```

**Brief**

- Sleep for time of one frame(const int frame_ms).

```c++
Keycode keydown();
```

**Brief**

 - When key down, check ascii code and return this using Keycode.

------

## Class Tetris
### Private Field: 

```c++
typedef std::vector<std::vector<bool>> Array2d;
```

```c++
struct Cursor
{
	int row;
	int col;
	...
};
```
		
```c++
Cursor::Cursor(int row, int col);
Cursor::Cursor();
Cursor::Cursor(const struct Cursor& cursor);
```

```c++
enum class Direction
{
	down, left, right
};
```

```c++
Cursor cursor;
```

```c++
int cycle;
```

```c++
Array2d* map;
```

```c++
Array2d node;
```

```c++
Array2d graphic;
```

```c++
Array2d pregraphic;
```

### Public Field:
```c++
static const int node_size;
```
```c++
static const int field_width;
static const int field_height;
```
```c++
static const int ingame_width;
static const int ingame_height;
```
```c++
static const int ingame_col_start;
static const int ingame_col_end;
```
```c++
static const int ingame_row_start;
static const int ingame_row_end;
```
```c++
static const Cursor start_point;
```








------
