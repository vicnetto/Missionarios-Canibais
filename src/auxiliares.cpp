#include <iostream>
#include <SFML/Graphics.hpp>

#include "auxiliares.h"

Phrase::Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position) {
    text.setString(phrase);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}

/*

-> bool Phrase::setFont(std::string way)
@param way -> Caminho até o arquivo.
@return -> Sucesso da operação.

*/
bool Phrase::setFont(std::string way) {

    if (!font.loadFromFile(way)) //Verificando se é possível acessar o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return false; //Problema em encontrar o arquivo.
    }

    text.setFont(font);

    return true;
}

/*

bool Phrase::isHovering(sf::Vector2i mousePos, Phrase phrase)
@param mousePos -> Posição do mouse na janela.
@return -> Caso esteja em cima é "true", caso contrário "false".

*/
bool Phrase::isHovering(sf::Vector2i mousePos) {

    if (text.getGlobalBounds().contains(mousePos.x, mousePos.y))
        return true;

    return false;
}

Sprites::Sprites(sf::Vector2f size, sf::Vector2f position)
{
    sprite.setScale(size);
    sprite.setPosition(position);
}

/*

bool Sprites::setTexture (std::string way)
@param way -> Caminho até o arquivo.
@return -> Sucesso da operação.

*/
bool Sprites::setTexture (std::string way) {

    if (!texture.loadFromFile(way)) //Verificando se é possível acessar o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return false; //Problema em encontrar o arquivo;
    }

    sprite.setTexture(texture);

    return true;
}