#include <array>
#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/DrawTile.hpp"

void draw_Tile(Position position, sf::RenderWindow& i_window, sf::Color color)
{
    sf::CircleShape circle;
    circle.setRadius(27.5);
    circle.setPointCount(300);
    circle.setFillColor(color);
    circle.setOutlineThickness(-3);
    circle.setOutlineColor(sf::Color(30,30,30));
    circle.setPosition(gridStartX + CELL_SIZE * position.x, gridStartY + CELL_SIZE * position.y);
    i_window.draw(circle);
}


int tileLocation(const std::array<std::array<Tile, row>, column>& grid, int col)
{
    int i = 5;

    // Checking all rows for selected column, to find empty grid position.
    while(i >= 0)
    {
        if(grid[col][i] == NONE)
        {
            return i;
        }

        i--; 
    }
    
    // Selected column is full.
    return -1;
}