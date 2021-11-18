#pragma once

constexpr int CELL_SIZE = 16;
constexpr int MAP_HEIGHT = 630;
constexpr int MAP_WIDTH = 800;
constexpr float SCREEN_RESIZE = 1;

constexpr int FONT_HEIGHT = 16;
constexpr int FRAME_DURATION = 16667;


// Tile types.
enum Tile
{
	NONE,
	RED,
	YELLOW
};


struct Position
{
	int x;
	int y;

	// '==' is overloded to check position is same or not.
	bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};