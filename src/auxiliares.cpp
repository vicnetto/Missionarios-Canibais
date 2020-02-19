#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "auxiliares.h"

#define BOATXRIGHT 1032
#define BOATXLEFT 500
#define BOATVELOCITY 4
#define BOATY 900

#define LEFTSIDE 0 //O lado esquerdo vale como 0;
#define BOATLEFTSIDE 1 //O barco no lado esqurdo vale 1;
#define BOATRIGHTSIDE 2 //O barco no lado direito vale 2;
#define RIGHTSIDE 3 //Quando está no lado direito, vale 3;

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

/*

void moveTo (std::stack boatSpaces)
@param std::stack<sf::Vector2f> &leftSpaces -> Como parâmetro, tem os espaços livres no lado esquerdo do rio.
@param std::stack<sf::Vector2f> &boatSpaces -> Nesse, não muito diferente, são os espaços livres dentro do barco.
@param std::stack<sf::Vector2f> &rightSpaces -> Também, nesse estão os lugares livres no lado direito do rio.
@param Boat &boat -> Passando o endereço de boat, onde será alterado alguns valores dentro do barco.
@return

*/
void Character::moveTo (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Boat &boat) 
{
    bool isPossible = false; //Fazendo uma condição, caso ele passe dessa condição quer dizer que é um movimento válido.

    if (location == LEFTSIDE || location == RIGHTSIDE) {
        if (location == RIGHTSIDE && boat.location == false && boat.quantChar != 2) //Primeira situação, caso o jogador esteja na terra e o barco esteja no seu lado, no lado direito;
            isPossible = true;

        if (location == LEFTSIDE && boat.location == true && boat.quantChar != 2) //Segunda situação, os dois no mesmo lado, porém esse no lado esquerdo;
            isPossible = true;

        if (isPossible) { //Aqui só entra se passou pelo menos em uma das verificações;
            if (location == RIGHTSIDE) { //Faz as devidas arrumações com o barco e com as pilhas;
                rightSpaces.push(sprite.getPosition()); //Caso ele esteja saindo do lado direito, colocando a posição que ele estava na pilha;

                location = BOATRIGHTSIDE; //Colocando sua nova posição, no barco na esquerda;
            } else {
                leftSpaces.push(sprite.getPosition()); //Colocando na pilha a sua posição antiga, no lado direito;

                location = BOATLEFTSIDE; //Sua nova posição, se localizando no barco no lado esquerdo;
            }

            sprite.setPosition(boatSpaces.top()); //Colocando o sprite no local disponível do barco;
            brightsprite.setPosition(boatSpaces.top()); //Colocando sua sprite de opção dentro do barco;

            boat.quantChar += 1; //Aumentando 1 na quantidade de pessoas que estão dentro do barco;

            boatSpaces.pop(); //Tirando a posição que agora ele ocupa dentro do barco;
        }
    } else { //Caso ele não esteja em nenhuma das duas posições, ele necessáriamente está no barco então é necessário tratar essas duas opções;
        boatSpaces.push(sprite.getPosition()); //Colocando uma nova opção disponível no barco;

        if (location == BOATRIGHTSIDE) {
            location = RIGHTSIDE; //Sua nova posição é na terra do lado direito;

            sprite.setPosition(rightSpaces.top()); //Colocando o seu sprite no lado direto na vaga que está livre;
            brightsprite.setPosition(rightSpaces.top()); //Colocando a sua sprite de opção também dentro da vaga livre;

            rightSpaces.pop(); //Tirando o espaço que estava livre, que agora está sendo ocupado pelo personagem;
        } else {
            location = LEFTSIDE; //Sua nova posição é no lado esquerdo;

            sprite.setPosition(leftSpaces.top()); //Colocando sua sprite no lado esquerdo, na vaga que está livre;
            brightsprite.setPosition(leftSpaces.top()); //Colocando a sua sprite de opção no lado direito também;

            leftSpaces.pop(); //Tirando a posição que agora está sendo ocupada agora pelo personagem;
        }

        boat.quantChar -= 1; //Tirando o personagem que acabamos de tirar do barco;
    }
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