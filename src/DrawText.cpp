#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/DrawText.hpp"


void draw_Text(std::string string, Position position, int characterSize, sf::RenderWindow& i_window, sf::Color color)
{
    sf::Font font;
    font.loadFromFile("src/Resources/Fonts/handwriting-draft_free-version.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
    text.setPosition(position.x, position.y);
    i_window.draw(text);
}


