#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "phrase.h"
#include "character.h"
#include "boat.h"



/*

class GameData
-> Essa classe tem como objetivo armazenar todos os dados do jogo, e fazer as verificações necessárias de vitória ou derrota.

VARIÁVEIS PÚBLICAS:
- int moves -> A quantidade de movimentos que foram realizados pelo jogador.
- int rightSideCanibals -> Quantos canibais estão no lado direito nesse momento.
- int rightSidePriests -> Quantos missionários estão do lado direito nesse momento do jogo.

- int currentTime -> Esse é o tempo atual do jogo, em inteiros, ou seja, ele só vai ser alterado quando a unidade inteira for alterada.
- int currentMoves -> Do mesmo jeito que o currentTime, esse só será alterado caso a quantidade de movimentos forem alteradas.

- sf::Clock gameTime -> Esse é o tempo total do jogo, desde o começo da partida.

FUNÇÕES PÚBLICAS:
- GameData() -> É o construtor padrão do jogo, nele coloca os dados iniciais do jogo, onde começam os personagens e tudo mais.
- bool verifyWinConditions() -> É o verificador final do jogo, caso o jogador perca ou ganhe. Caso nada tiver acontecido, retorna-se 1. Caso o jogador tenha
perdido, retorna-se 2. Caso o jogador ganhe, retorna-se 3.
- void printTime(Phrase &time, sf::Clock &currentGameTime) -> Essa função irá printar quanto tempo tem de jogo.
- void initializeStacks (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces) -> Essa função serve para tirar um pouco de instanciações
do jogo.cpp, para descarregar um pouco aquela função.
- void resetStacksAndReplace (...) -> Essa função, extremamente imporante para o reinício do jogo, serve para resetar todas as posições dos personagens e as
posições disponíveis para o jogador nos outros lados.
- void gameOverScreen (sf::Window &window) -> Essa função tem como objetivo printar para o jogador quais foram os personagens que morreram e perguntar
se o jogador quer iniciar o jogo novamente.
*/
class GameData {
    public:
        int moves;
        int totalMoves;
        int numbAttempts;
        int rightSideCanibals;
        int rightSidePriests;

        int currentTime;
        int currentMoves;
        int currentTotalMoves;
        int currentNumbAttempts;

        sf::Clock gameTime;

    public:
        GameData();
        int verifyWinConditions(Character (&character) [6]);
        void printStatistics(Phrase &time, Phrase &movements, Phrase &attempts, Phrase &totalMovements);
        void initializeStacks (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces);
        void resetStacksAndReplace (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Character (&character) [6], Boat &boat);
        void gameOverScreen (sf::RenderWindow &window);
};

#endif /* GAMEDATA_H */