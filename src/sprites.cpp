#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "sprites.h"


//-------------------------------------------------------- SPRITES ---------------------------------------------------------------------------

/*

Sprites::Sprites()
@param
@return

*/
Sprites::Sprites()
{
    sprite.setScale(1, 1); 
    sprite.setPosition(0 ,0);
}

/*

Sprites::Sprites(sf::Vector2f size, sf::Vector2f position)
@param sf::Vector2f scale -> Tamanho da escala, que será aplicada a sprite.
@param sf::Vector2f position -> Posição inicial da sprite.

*/
Sprites::Sprites(sf::Vector2f scale, sf::Vector2f position)
{
    sprite.setScale(scale);
    sprite.setPosition(position);
}

/*

bool Character::setBrightTexture(std::string way)
@param std::string way -> É o caminho percorrido para chegar até a sprite com cor.
@return bool -> Retorna se foi possível fazer a aplicação da textura ou não.

*/
bool Sprites::setBrightTexture(std::string way)
{
    if (!brighttexture.loadFromFile(way)) //Verificando se é possível acessar o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return false; //Problema em encontrar o arquivo;
    }

    brightsprite.setTexture(brighttexture);

    return true;
}

/*

bool Sprites::setTexture (std::string way)
@param srd::string way -> Caminho até o arquivo.
@return bool -> Sucesso da operação.

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

/*

bool Sprites::isHovering (sf::Vector2i mousePos)
@param sf::Vector2i mousePos -> Isso é a posição atual do mouse.
@return bool -> True para contém, e false para não contido.

*/
bool Sprites::isHovering (sf::Vector2i mousePos)
{
    if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) //Pega a localização do  mouse e verifica se contêm ou não dentro do sprite;
        return true;

    return false; 
}

//--------------------------------------------------------------------------------------------------------------------------------------------