#include "input/Input.h"
#include "core/Time.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "test");
    Time timer;
    timer.start();

    while(window.isOpen())
    {
        KeyInput::update();

        if(KeyInput::isPressed(Action::Brake))
        {
            timer.start();
        }

        std::cout << timer.elapsedTime() << "\n";
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.display();
    }
    
    return 0;
}