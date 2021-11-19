#pragma once

constexpr float CELL_SIZE = 70.3;

constexpr int MAP_HEIGHT = 630;
constexpr int MAP_WIDTH = 800;

constexpr int row = 6;
constexpr int column = 7;

constexpr int gridStartX = 166;
constexpr int gridStartY = 141;

constexpr float SCREEN_RESIZE = 1;
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
