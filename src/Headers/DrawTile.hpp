#pragma once

void draw_Tile(Position position, sf::RenderWindow& i_window, sf::Color color);

int tileLocation(const std::array<std::array<Tile, row>, column>& grid, int col);