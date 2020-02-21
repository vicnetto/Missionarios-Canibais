#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "boat.h"
#include "sprites.h"

#define BOATXRIGHT 1032
#define BOATXLEFT 500
#define BOATVELOCITY 4
#define BOATY 900

#define XAXISBOATDISTANCE 532


//-------------------------------------------------------- BOAT ---------------------------------------------------------------------------

/*

Boat::Boat(bool isOnTheLeft, int quantChar, sf::Vector2f scale, sf::Vector2f position)
@param bool isOnTheLeft -> Onde está localizado o barco, se é no lado true (esquerdo) ou no lado false (direito).
@param int quantChar -> Quantos persongens estão em cima do barco atualmente.
@param sf::Vector2f scale -> Qual a escala do barco.
@param sf::Vector2f position -> Onde é a posição inicial do barco.
@return

*/
Boat::Boat(bool isOnTheLeft, int quantChar, sf::Vector2f scale, sf::Vector2f position)
{
    this->isOnTheLeft = isOnTheLeft;
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
    if (isOnTheLeft == false) {
        xinitial = BOATXRIGHT; //Setando as configurações para o movimento do barco;
        xfinal = BOATXLEFT;

        speed = -BOATVELOCITY; //Velocidade que o barco andará.
        isOnTheLeft = true; //Informando que o lado foi trocado;
        moving = true;

        sprite.setPosition(xinitial, BOATY); //Para fazer o espelhamento do barco, é necessário essas duas ultimas linhas no código;
        sprite.setScale(0.5, 0.5); //Essa espelha o barco, e a de cima corrige a sua posição;

        brightsprite.setPosition(xinitial, BOATY);
        brightsprite.setScale(0.5, 0.5);
    } else {
        xinitial = BOATXLEFT; //Colocando outras configurações caso ele esteja do lado direito;
        xfinal = BOATXRIGHT + sprite.getGlobalBounds().width;

        speed = BOATVELOCITY;  
        isOnTheLeft = false;  //Informando que o lado foi trocado;
        moving = true;
                            
        sprite.setPosition(xinitial + sprite.getGlobalBounds().width, BOATY); //Do mesmo jeito que na ida para o lado esquerdo, precisa dessas duas linhas;
        sprite.setScale(-0.5, 0.5); //A primeira corrige a posição do x, e a segunda espelha o barco para ir em sentido da volta;

        brightsprite.setPosition(xinitial + sprite.getGlobalBounds().width, BOATY);
        brightsprite.setScale(-0.5, 0.5);
    }   
}

/*

void Boat::moveBoatFreePos (std::stack<sf::Vector2f> &boatSpaces)
@param std::stack<sf::Vector2f> &boatSpaces -> Aqui ficam as posições livres do barco;
@return

*/
void Boat::moveBoatFreePos (std::stack<sf::Vector2f> &boatSpaces)
{
    int distance = -XAXISBOATDISTANCE; //Deixando pronto caso ele esteja na direita;

    std::stack<sf::Vector2f> correctedStack; //Essa é a stack que estará corrigida;
    sf::Vector2<float> vectorForChange; //Esse é o vetor corretor, onde vamos colocar o valor corrigido antes de colocar na stack corrigida;

    if (isOnTheLeft) //Aqui ta corrigindo para diferenciar as distâncias, pois para a direita ele move positivamente;
        distance = -distance;

    while (!boatSpaces.empty()) { //Enquanto o barco não está vazio;
        vectorForChange = boatSpaces.top(); //Coloca no vetor de mudança, para colocar a distância nova na posição, que é feito na linha abaixo;
        vectorForChange.x -= distance;

        correctedStack.push(vectorForChange); //Aqui coloca tudo na stack corrigida;

        boatSpaces.pop(); //E tira esse posição do barco, pois agora ela está atualizada;
    }

    while (!correctedStack.empty()) { //Esse loop serve basicamente para tirar os elementos da corrigida e levar para a boatSpaces, onde estará atualizada;
        boatSpaces.push(correctedStack.top()); 

        correctedStack.pop();
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------