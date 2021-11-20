#include <array>

#include "Headers/Global.hpp"
#include "Headers/Win.hpp"


bool victoryCheck(const std::array<std::array<Tile, row>, column>& grid, int newTile, int col)
{
    int maxLeft = col % 7;
    int maxRight = 6 - maxLeft;

    int maxUp = newTile % 6;
    int maxDown = 5 - maxUp;

    // Number of same tiles.
    int counter = 1;

    // Type of tile to be checked.
    Tile color = static_cast<Tile>(grid[col][newTile]);


    // Horizontal :
    // We loop through all tiles at left side.
    for(int i = 1; i <= maxLeft; i++)
    {
        if(grid[col-i][newTile] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }
    // We loop through all tiles at right side.
    for(int i = 1; i <= maxRight; i++)
    {
        if(grid[col+i][newTile] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter >= 4) return true;


    // Vertical :
    counter = 1;

    // We loop through all tiles above.
    for(int i = 1; i <= maxUp; i++)
    {
        if(grid[col][newTile-i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    // We loop through all tiles below.
    for(int i = 1; i <= maxDown; i++)
    {
        if(grid[col][newTile+i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter >= 4) return true;


    // Diagonal : Top-left
    counter = 1;

    for(int i = 1; i <= maxLeft && i<= maxUp; i++)
    {
        if(grid[col-i][newTile-i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    for(int i = 1; i <= maxRight && i <= maxDown; i++)
    {
        if(grid[col+i][newTile+i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter >= 4) return true;


    // Diagonal : Bottom-left
    counter = 1;

    for(int i = 1; i <= maxLeft && i<= maxDown; i++)
    {
        if(grid[col-i][newTile+i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    for(int i = 1; i <= maxRight && i <= maxUp; i++)
    {
        if(grid[col+i][newTile-i] == color)
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter >= 4) return true;

    // Not won
    return false;
}