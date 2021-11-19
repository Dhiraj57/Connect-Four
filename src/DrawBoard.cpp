#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/DrawBoard.hpp"


void draw_board(sf::RenderWindow& i_window)
{
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    backgroundTexture.loadFromFile("src/Resources/Images/Back1.png");
    backgroundTexture.setSmooth(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(MAP_WIDTH/backgroundSprite.getLocalBounds().width, MAP_HEIGHT/backgroundSprite.getLocalBounds().height);

    sf::Sprite boardSprite;
    sf::Texture boardTexture;

    boardTexture.loadFromFile("src/Resources/Images/Board2.png");
    boardTexture.setSmooth(true);

    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(0.6, 0.6);
    boardSprite.setPosition(MAP_WIDTH/5.4, MAP_HEIGHT/5);

    i_window.draw(backgroundSprite);
    i_window.draw(boardSprite);
}