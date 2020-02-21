#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <bits/stdc++.h>

#include "character.h"
#include "sprites.h"
#include "boat.h"

#define LEFTSIDE 0 //O lado esquerdo vale como 0;
#define BOATLEFTSIDE 1 //O barco no lado esqurdo vale 1;
#define BOATRIGHTSIDE 2 //O barco no lado direito vale 2;
#define RIGHTSIDE 3 //Quando está no lado direito, vale 3;

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
@return

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
        if (location == RIGHTSIDE && boat.isOnTheLeft == false && boat.quantChar != 2) //Primeira situação, caso o jogador esteja na terra e o barco esteja no seu lado, no lado direito;
            isPossible = true;

        if (location == LEFTSIDE && boat.isOnTheLeft == true && boat.quantChar != 2) //Segunda situação, os dois no mesmo lado, porém esse no lado esquerdo;
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

//---------------------------------------------------------------------------------------------------------------------------------------------