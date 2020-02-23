#ifndef CHARACTER_H
#define CHARACTER_H

#include "sprites.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <bits/stdc++.h>

class Boat;

/*

class Character : public Sprites
-> Essa classe, filha da classe Sprites, é uma classe para armazenar os dados dos personagens do jogo. Onde eles estão, qual é o personagem, pricipalmente.


VARIÁVEIS PÚBLICAS:
- bool isPriest -> Tem o objetivo único de saber se trata de um missionário (true) ou um canibal (false).
- int location -> Essa variável armazena qual é o local do personagem, se ele está no lado esquerdo (0), no barco (1) ou no lado direito (2).

FUNÇÕES PÚBLICAS:
- Character () -> É o grande construtor, ele inicializa todas as variáveis, até o de sua classe mãe.
- void setCharacter () -> Essa função, importantíssima, serve como um constutor, porém como é instanciado um vetor no main, é necessário uma função para tratar com cada objeto,
onde se encontra essa função.
- void moveTo () -> Essa função serve para organizar os comandos de mover o personagem, para dentro do barco ou para fora.

*/
class Character : public Sprites
{
    public:
        bool isPriest; //False é canibal e true é missionário;
        int location; //1 é para lado esquerdo, 2 é para o barco e 3 é no lado direito;

    public:
        Character(); //Construtor básico da classe;
        void setCharacter(bool isPriest, int location, sf::Vector2f scale, sf::Vector2f position); //É basicamente um construtor com um extra, ele pode ser chamado depois da instância.
        void moveTo (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Boat &boat); //Essa função tem como objetivo recolocar o persongem, caso o jogador tenha clicado nele.
};

#endif /* CHARACTER_H */