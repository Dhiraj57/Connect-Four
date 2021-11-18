#include <iostream>
#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "src/Headers/Global.hpp"
int main()
{
    bool game_won = 0;
    int lag = 0;
    int level = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * SCREEN_RESIZE, MAP_HEIGHT * SCREEN_RESIZE), "Connect 4", sf::Style::Close, settings);
    window.setView(sf::View(sf::FloatRect(0, 0, MAP_WIDTH, MAP_HEIGHT)));

    sf::Font font;
    if (!font.loadFromFile("src/Resources/Fonts/andlso.ttf"))
    {
        std::cout << "Failed to load resources.\n\n";
        return 0;
    }

    sf::RectangleShape background(sf::Vector2f(MAP_WIDTH, MAP_HEIGHT));
    background.setFillColor(sf::Color(138,138,138));




    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}