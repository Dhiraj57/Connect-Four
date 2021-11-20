#pragma once

constexpr float CELL_SIZE = 70.3;

constexpr int MAP_HEIGHT = 630;
constexpr int MAP_WIDTH = 800;

constexpr int row = 6;
constexpr int column = 7;

// Grid start position.
constexpr int gridStartX = 166;
constexpr int gridStartY = 141;

// To change screen size.
constexpr float SCREEN_RESIZE = 1;


// Tile type.
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
