#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <array>
#include <SFML/Graphics.hpp>
#include "src/Headers/Global.hpp"
#include "src/Headers/Win.hpp"
#include "src/Headers/DrawBoard.hpp"
#include "src/Headers/DrawText.hpp"
#include "src/Headers/DrawTile.hpp"


int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    start = std::chrono::system_clock::now();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * SCREEN_RESIZE, MAP_HEIGHT * SCREEN_RESIZE), "Connect 4", sf::Style::Close, settings);
    window.setView(sf::View(sf::FloatRect(0, 0, MAP_WIDTH, MAP_HEIGHT)));


    // sf::RectangleShape overlay(sf::Vector2f(630, 630));
    // overlay.setFillColor(sf::Color(150, 150, 150, 150));
    // sf::Text ggText;
    // ggText.setFont(font);
    // ggText.setCharacterSize(80);
    // ggText.setColor(sf::Color::Black);

    sf::Sprite skipButton;
    sf::Texture texture;
    texture.loadFromFile("src/Resources/Images/Skip.png");
    texture.setSmooth(true);
    skipButton.setTexture(texture);
    skipButton.setScale(0.45,0.45);
    skipButton.setPosition(57, 35);

    sf::Sprite restart;
    sf::Texture restartTexture;
    restartTexture.loadFromFile("src/Resources/Images/Restart.png");
    restartTexture.setSmooth(true);
    restart.setTexture(restartTexture);
    restart.setScale(0.44,0.44);
    restart.setPosition(703, 36);

    sf::Sprite timerRect;
    sf::Texture timerTexture;
    timerTexture.loadFromFile("src/Resources/Images/TimeRect.png");
    timerTexture.setSmooth(true);
    timerRect.setTexture(timerTexture);
    timerRect.setScale(0.17,0.15);
    timerRect.setPosition(450, 32);

    bool gameOver = false;
    bool tileDropped = false;
    bool currentRed = true;

    int col = 0;
    int newTile = 0;
    int hoverTile = 0;
    int moveCounter = 0;

    Tile winner = NONE;

    // New tile position.
    Position tilePosition;

    std::array<std::array<Tile, row>, column> grid;
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<6; j++)
        {
            grid[i][j] = NONE;
        }
    }
    

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (event.mouseButton.x > gridStartX && event.mouseButton.x < gridStartX + column * CELL_SIZE && !gameOver)
                {
                    tileDropped = true;
                    col = (event.mouseButton.x - gridStartX)/ CELL_SIZE;
                }

                else if (skipButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !gameOver)
                {
                    currentRed = !currentRed;
                    start = std::chrono::system_clock::now();
                }

                else if (restart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    for(int i=0; i<7; i++)
                    {
                        for(int j=0; j<6; j++)
                        {
                            grid[i][j] = NONE;
                        }
                    }

                    start = std::chrono::system_clock::now();

                    gameOver = false;
                    tileDropped = false;
                    currentRed = true;
                    moveCounter = 0;
                    winner = NONE;
                }
            }



            if (skipButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)  && !gameOver)
            {
                skipButton.setColor(sf::Color(255,255,255,128));
            }

            else if (restart.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) )
            {
                restart.setColor(sf::Color(255,255,255,128));
            }

            else
            {
                skipButton.setColor(sf::Color(255,255,255,255));
                restart.setColor(sf::Color(255,255,255,255));
            }
        }

        if(tileDropped)
        {
            start = std::chrono::system_clock::now();

            tileDropped = false;
            newTile = tileLocation(grid, col);

            if(newTile != -1)
            {
                grid[col][newTile] = static_cast<Tile>(2 - currentRed);
                currentRed = !currentRed;
                tileDropped = false;
                moveCounter++;
                
                if (victoryCheck(grid, newTile, col))
                {
                    gameOver = true;
                    winner = grid[col][newTile];
                }
                else if(moveCounter >= 42)
                {
                    gameOver = true;
                    winner = NONE;
                }
            }
        }


        window.clear();
        draw_board(window);


        // Drawing filled tiles
        for(int i=0; i<7; i++)
        {
            for(int j=0; j<6; j++)
            {
                if(grid[i][j] != NONE)
                {
                    tilePosition.x = i;
                    tilePosition.y = j;
                    sf::Color color;

                    if(grid[i][j] == RED)
                    {
                        color = sf::Color::Red;
                    }
                    else
                    {
                        color = sf::Color::Yellow;
                    }

                    draw_Tile(tilePosition, window, color);
                }
            }
        }

        // Drawing Hower tile
        if (sf::Mouse::getPosition(window).x > gridStartX && sf::Mouse::getPosition(window).x < gridStartX + column * CELL_SIZE && !gameOver)
        {
            col = (sf::Mouse::getPosition(window).x - gridStartX)/ CELL_SIZE;
        
            hoverTile = tileLocation(grid, col);

            if (hoverTile != -1)
            {
                sf::Color color;

                if(currentRed)
                {
                    color = sf::Color(255, 0, 0, 150);
                }
                else
                {
                    color = sf::Color(255, 255, 0, 150);
                }

                tilePosition.x = col;
                tilePosition.y = hoverTile;
                draw_Tile(tilePosition, window, color);
            }
        }


        if(currentRed && !gameOver)
        {
            draw_Text("Player 1's move", {257,50}, 20, window, sf::Color::White);
        }
        else if(!gameOver)
        {
            draw_Text("Player 2's move", {257,50}, 20, window, sf::Color::White);
        }


        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        if(elapsed_seconds.count() > 29)
        {
            start = std::chrono::system_clock::now();
            currentRed = !currentRed;
        }

        int result = static_cast<int>(elapsed_seconds.count());

        if(!gameOver)
        {
            window.draw(timerRect);
            draw_Text(std::to_string(30 - result), {480,51}, 20, window, sf::Color::White);
        }
        
        draw_Text("Skip Turn", {43,88}, 14, window, sf::Color::White);
        draw_Text("New Game", {683,88}, 14, window, sf::Color::White);
    
        window.draw(restart);
        window.draw(skipButton);

        if(gameOver)
        {
            if(winner == RED)
            {
                draw_Text("Player-1 Wins !", {320,50}, 20, window, sf::Color::White);
            }
            else if(winner == YELLOW)
            {
                draw_Text("Player-2 Wins !", {320,50}, 20, window, sf::Color::White);
            }
            else
            {
                draw_Text("Game Draw !", {338,50}, 20, window, sf::Color::White);
            }
        }

        window.display();
    }

    return 0;
}