#include <iostream>
#include <SFML/Graphics.hpp>

#include "auxiliares.h"

Phrase::Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position) {
    text.setString(phrase);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}

bool Phrase::setFont(std::string way) {

    if (!font.loadFromFile(way))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        exit;
    }

    text.setFont(font);

    return true;
}