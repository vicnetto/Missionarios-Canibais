#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "auxiliares.h"

#define BOATXRIGHT 1032
#define BOATXLEFT 500
#define BOATVELOCITY 4
#define BOATY 900

//---------------------------------------------------------- PHRASE -------------------------------------------------------------------------

/*

Phrase::Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position)
@param std::string phrase -> Sendo uma string, mostra o real conteúdo do que estará escrito na frase.
@param int scale -> Aqui configura-se o tamanho da escala para a frase.
@param sf::Color color -> Colocando cor na letra, onde pode ser escolhida pela sf::Color.
@param sf::Vector2f position -> Qual a posiçao inicial da frase, no eixo X/Y.

*/
Phrase::Phrase(std::string phrase, int scale, sf::Color color, sf::Vector2f position) {
    text.setString(phrase);
    text.setCharacterSize(scale);
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

//------------------------------------------------------ CHARACTER ----------------------------------------------------------------------------

/*

Character::Character()
@param
@return

*/
Character::Character()
{
    type = false;
    location = 2;
    sprite.setScale(1, 1);
    sprite.setPosition(0 ,0);
}

/*

void Character::setCharacter(bool t, int l, sf::Vector2f scale, sf::Vector2f position)
@param bool type -> É o tipo do personagem, se é um missionário (1) ou um canibal (0).
@param int location -> Serve para saber que lado o personagem está, no lado esquerdo (0), no meio (1) ou no lado direito (2).
@param sf::Vector2f scale -> Tem objetivo de colocar a escala, ou seja, qual será o tamanho do sprite.
@param sf::Vector2f position -> É a posição que está o personagem, em pixels.

*/
void Character::setCharacter(bool type, int location, sf::Vector2f scale, sf::Vector2f position)
{
    this->type = type;
    this->location = location;

    sprite.setScale(scale);
    sprite.setPosition(position);

    brightsprite.setScale(scale);
    brightsprite.setPosition(position);
}

//-------------------------------------------------------- BOAT ---------------------------------------------------------------------------

/*

Boat::Boat(bool location, int quantChar, sf::Vector2f scale, sf::Vector2f position)
@param bool location -> Onde está localizado o barco, se é no lado true (esquerdo) ou no lado false (direito).
@param int quantChar -> Quantos persongens estão em cima do barco atualmente.
@param sf::Vector2f scale -> Qual a escala do barco.
@param sf::Vector2f position -> Onde é a posição inicial do barco.

*/
Boat::Boat(bool location, int quantChar, sf::Vector2f scale, sf::Vector2f position)
{
    this->location = location;
    this->quantChar = quantChar;
    moving = false;

    sprite.setScale(scale);
    sprite.setPosition(position);

    brightsprite.setScale(scale);
    brightsprite.setPosition(position);

    xfinal = 0;
    xinitial = 0;
    speed = 0;
}

/*

void Boat::moveBoat ()
@param
@return

*/
void Boat::moveBoat ()
{
    if (location == false) {
        xinitial = BOATXRIGHT; //Setando as configurações para o movimento do barco;
        xfinal = BOATXLEFT;

        speed = -BOATVELOCITY; //Velocidade que o barco andará.
        location = true; //Informando que o lado foi trocado;
        moving = true;

        sprite.setPosition(xinitial, BOATY); //Para fazer o espelhamento do barco, é necessário essas duas ultimas linhas no código;
        sprite.setScale(0.5, 0.5); //Essa espelha o barco, e a de cima corrige a sua posição;

        brightsprite.setPosition(xinitial, BOATY);
        brightsprite.setScale(0.5, 0.5);
    } else {
        xinitial = BOATXLEFT; //Colocando outras configurações caso ele esteja do lado direito;
        xfinal = BOATXRIGHT + sprite.getGlobalBounds().width;

        speed = BOATVELOCITY;  
        location = false;  //Informando que o lado foi trocado;
        moving = true;
                            
        sprite.setPosition(xinitial + sprite.getGlobalBounds().width, BOATY); //Do mesmo jeito que na ida para o lado esquerdo, precisa dessas duas linhas;
        sprite.setScale(-0.5, 0.5); //A primeira corrige a posição do x, e a segunda espelha o barco para ir em sentido da volta;

        brightsprite.setPosition(xinitial + sprite.getGlobalBounds().width, BOATY);
        brightsprite.setScale(-0.5, 0.5);
    }   
}

//-----------------------------------------------------------------------------------------------------------------------------------