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


Sprites::Sprites()
{
    sprite.setScale(1, 1);
    sprite.setPosition(0 ,0);
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
bool Sprites::setTexture (std::string way)
{

    if (!texture.loadFromFile(way)) //Verificando se é possível acessar o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return false; //Problema em encontrar o arquivo;
    }

    sprite.setTexture(texture);

    return true;
}


Character::Character()
{
    type = false;
    location = 2;
    sprite.setScale(1, 1);
    sprite.setPosition(0 ,0);
}

/*

void Character::setCharacter(bool t, int l, sf::Vector2f scale, sf::Vector2f position)
@param bool t -> É o tipo do personagem, se é um missionário (1) ou um canibal (0).
@param int l -> Serve para saber que lado o personagem está, no lado esquerdo (0), no meio (1) ou no lado direito (2).
@param sf::Vector2f scale -> Tem objetivo de colocar a escala, ou seja, qual será o tamanho do sprite.
@param sf::Vector2f position -> É a posição que está o personagem, em pixels.

*/
void Character::setCharacter(bool t, int l, sf::Vector2f scale, sf::Vector2f position)
{
    type = t;
    location = l;

    sprite.setScale(scale);
    sprite.setPosition(position);
}

Boat::Boat(int location, int quantChar, sf::Vector2f scale, sf::Vector2f position)
{
    this->location = location;
    this->quantChar = quantChar;
    sprite.setScale(scale);
    sprite.setPosition(position);
}