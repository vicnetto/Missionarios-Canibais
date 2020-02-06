#include <SFML/Graphics.hpp>
#include <iostream>
#include "jogo.h"

int Jogo::mainMenu () {

    sf::RectangleShape rect(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(sf::Vector2f(100, 100));

    while (window.isOpen()) //Começando o loop principal do menu;
    {

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            
            case sf::Event::Closed:
                window.close();

                break;
            }
        }

        window.clear(sf::Color::Cyan);

        window.draw(rect);

        window.display();
    }

    return 0;
}