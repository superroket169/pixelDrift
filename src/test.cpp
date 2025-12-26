#include "resource/ResourceManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "test");

    Resource::loadBackGrounds();
    Resource::loadCarAssets();
    Resource::loadFonts();
    
    sf::Text text("test", Resource::Font, 24);
    text.setPosition(200, 50);
    text.setFillColor(sf::Color::White);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }

        window.clear({0, 0, 0});
        window.draw(text);
        window.display();
    }
    
    return 0;
}