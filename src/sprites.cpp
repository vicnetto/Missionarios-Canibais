#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "sprites.h"

//-------------------------------------------------------- SPRITES ---------------------------------------------------------------------------

/*

Sprites::Sprites()

    Esse é o construtor, onde é o objetivo principal da criação dessa classe, para deixar as coisas mais organizadas.

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

    Esse é o construtor, onde é o objetivo principal da criação dessa classe, para deixar as coisas mais organizadas.

@param sf::Vector2f scale -> Tamanho da escala, que será aplicada a sprite.
@param sf::Vector2f position -> Posição inicial da sprite.

*/
Sprites::Sprites(sf::Vector2f scale, sf::Vector2f position)
{
    sprite.setScale(scale.x * 0.5, scale.y * 0.5);
    sprite.setPosition(position);
}

/*

bool Character::setBrightTexture(std::string way)

    Essa função tem como objetivo setar e retornar se houve sucesso ao mudar a textura da BrightSprite, ela funciona do mesmo modo da
função da classe Sprites, porém com variáveis diferentes.

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

    O objetivo dessa é colocar a textura no sprite, e principalmente verificar se está com algum problema no arquivo.

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

    Essa função é exatamente a mesma da classe Phrases, mas com uma diferença mínima que se trata de sprites.

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