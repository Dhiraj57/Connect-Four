#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/Headers/Global.hpp"
#include "src/Headers/Win.hpp"
#include "src/Headers/DrawBoard.hpp"
#include "src/Headers/DrawText.hpp"
#include "src/Headers/DrawTile.hpp"


int main()
{
    // To create timer.
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    // Starting the timer.
    start = std::chrono::system_clock::now();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * SCREEN_RESIZE, MAP_HEIGHT * SCREEN_RESIZE), "Connect 4", sf::Style::Close, settings);
    window.setView(sf::View(sf::FloatRect(0, 0, MAP_WIDTH, MAP_HEIGHT)));

    // Sound addition.
    sf::SoundBuffer buffer;
    sf::SoundBuffer bufferMusic;
    bufferMusic.loadFromFile("src/Resources/Audio/GameMusic2.wav");

    sf::Sound sound;
    sf::Sound music;
    music.setBuffer(bufferMusic);
    music.setLoop(true);
    music.play();

    // Skip button.
    sf::Sprite skipButton;
    sf::Texture texture;
    texture.loadFromFile("src/Resources/Images/Skip.png");
    texture.setSmooth(true);
    skipButton.setTexture(texture);
    skipButton.setScale(0.45,0.45);
    skipButton.setPosition(57, 35);

    // Restart button.
    sf::Sprite restart;
    sf::Texture restartTexture;
    restartTexture.loadFromFile("src/Resources/Images/Restart.png");
    restartTexture.setSmooth(true);
    restart.setTexture(restartTexture);
    restart.setScale(0.44,0.44);
    restart.setPosition(703, 36);

    // Timer rectangle.
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

    int soundCounter = 1;
    int col = 0;
    int newTile = 0;
    int hoverTile = 0;
    
    // Number of tiles filled.
    int moveCounter = 0; 

    Tile winner = NONE;

    // New tile position.
    Position tilePosition;

    // Grid to store information about tiles.
    std::array<std::array<Tile, row>, column> grid;

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<6; j++)
        {
            grid[i][j] = NONE;
        }
    }
    

    // Game loop.
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            // To detect left mouse button click.
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                // Checking mouse position.
                if (event.mouseButton.x > gridStartX && event.mouseButton.x < gridStartX + column * CELL_SIZE && !gameOver)
                {
                    tileDropped = true;
                    // Column in which tile is to be dropped.
                    col = (event.mouseButton.x - gridStartX)/ CELL_SIZE;
                }

                // Skip button pressed.
                else if (skipButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !gameOver) 
                {
                    // Changing player turn.
                    currentRed = !currentRed;
                    start = std::chrono::system_clock::now();

                    buffer.loadFromFile("src/Resources/Audio/ButtonOver.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                }

                // Restart button pressed.
                else if (restart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Reseting all values.
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
                    soundCounter = 1;
                    moveCounter = 0;
                    winner = NONE;

                    buffer.loadFromFile("src/Resources/Audio/ButtonOver.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                }
            }


            // To detect button hover. 
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


        // To place the tile inside grid as per input.
        if(tileDropped)
        {
            start = std::chrono::system_clock::now();

            tileDropped = false;

            // To get the 'y' position of empty tile.
            newTile = tileLocation(grid, col);

            // If column is not filled, we can put the tile.
            if(newTile != -1)
            {
                buffer.loadFromFile("src/Resources/Audio/TilePlace.wav");
                sound.setBuffer(buffer);
                sound.play();

                grid[col][newTile] = static_cast<Tile>(2 - currentRed);
                currentRed = !currentRed;
                tileDropped = false;
                moveCounter++;
                
                // Win condition check.
                if (victoryCheck(grid, newTile, col))
                {
                    gameOver = true;
                    winner = grid[col][newTile];
                }

                // Draw condition check.
                else if(moveCounter >= 42)
                {
                    gameOver = true;
                    winner = NONE;
                }
            }
        }

        // Drawing all things to window.
        window.clear();

        // To draw board.
        draw_board(window);

        // To draw all filled tiles.
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

        // To draw hover tile.
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

        // Setting the value of timer.
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        // To reset the timer.
        if(elapsed_seconds.count() > 30)
        {
            start = std::chrono::system_clock::now();
            currentRed = !currentRed;

            if(!gameOver)
            {
                buffer.loadFromFile("src/Resources/Audio/TimeOver.wav");
                sound.setBuffer(buffer);
                sound.play();
            }
        }

        int result = static_cast<int>(elapsed_seconds.count());

        // To draw the timer to window.
        if(!gameOver)
        {
            window.draw(timerRect);
            draw_Text(std::to_string(30 - result), {480,51}, 20, window, sf::Color::White);
        }
        
        window.draw(restart);
        window.draw(skipButton);
        draw_Text("Skip Turn", {43,88}, 14, window, sf::Color::White);
        draw_Text("New Game", {683,88}, 14, window, sf::Color::White);

        // Game over text.
        if(gameOver)
        {       
            if(winner == RED)
            {
                draw_Text("Player-1 Wins !", {320,50}, 20, window, sf::Color::White);
                if(soundCounter)
                {
                    soundCounter = 0;
                    buffer.loadFromFile("src/Resources/Audio/GameWon.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                }
            }

            else if(winner == YELLOW)
            {
                draw_Text("Player-2 Wins !", {320,50}, 20, window, sf::Color::White);
                if(soundCounter)
                {
                    soundCounter = 0;
                    buffer.loadFromFile("src/Resources/Audio/GameWon.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                }
            }

            else
            {
                draw_Text("Game Draw !", {338,50}, 20, window, sf::Color::White);
                if(soundCounter)
                {
                    soundCounter = 0;
                    buffer.loadFromFile("src/Resources/Audio/Draw.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                }
            }
        }

        window.display();
    }

    return 0;
}