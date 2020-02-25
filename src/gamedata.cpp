#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "gamedata.h"
#include "phrase.h"
#include "character.h"

#define MAXIMUMCHARSINONESIDE 3
#define CONTINUE 0 
#define YOULOSE 1
#define YOUWIN 2

#define NUMBEROFPRIESTS 3

#define LEFTSIDE 0
#define LEFTBOATSIDE 1
#define RIGHTBOATSIDE 2
#define RIGHTSIDE 3


//------------------------------------------------------ GAMEDATA ----------------------------------------------------------------------------

/*

GameData::GameData()

    É o construtor padrão do jogo, nele coloca os dados iniciais do jogo, onde começam os personagens e tudo mais.

@param
@return

*/
GameData::GameData() 
{
    moves = 0;
    rightSideCanibals = 3;
    rightSidePriests = 3;

    currentTime = 0;
    currentMoves = 0;
}

/*

int GameData::gameOver()

    É o verificador final do jogo, caso o jogador perca ou ganhe. Caso nada tiver acontecido, retorna-se 1. Caso o jogador tenha
perdido, retorna-se 2. Caso o jogador ganhe, retorna-se 3.

@param Character (&character) [6] -> Esse parãmetro pega os personagens, porém por endereço, sendo assim possível alterar a sua textura.
@return int -> 0 para continuação do jogo, 1 para jogador perdeu o jogo e 2 para jogador ganhou o jogo.

*/
int GameData::verifyWinConditions(Character (&character) [6]) 
{
    bool isAtLeastOne = false; //Colocando uma verificação para ver se ele passa por pelo menos uma verificação;

    if (rightSideCanibals > rightSidePriests && rightSidePriests != 0) { //Caso existam mais canibais do que padres em um lado, o jogo termina, pois o jogador perdeu;
        isAtLeastOne = true; //Pelo menos 1 é verdade;

        for (int i = 0; i < NUMBEROFPRIESTS; i++ ) { //Aqui ele passa pelos padres e verifica quais deles estão do lado direito, para colocar suas texturas de "morte";
            if (character[i].location == RIGHTSIDE || character[i].location == RIGHTBOATSIDE)
                character[i].setTexture("bin/padre3.png");
        }
    }
    
    //Aqui caso tenham mais canibais do que missionários do lado esquerdo, quer dizer que o jogo está perdido;
    if (MAXIMUMCHARSINONESIDE - rightSideCanibals > MAXIMUMCHARSINONESIDE - rightSidePriests && MAXIMUMCHARSINONESIDE - rightSidePriests != 0) {
        isAtLeastOne = true;

        for (int i = 0; i < NUMBEROFPRIESTS; i++ ) { //Aqui agora está passando por todos e verificando quais estão mortos do lado direito, para assim colocar a textura deles como escura;
            if (character[i].location == LEFTSIDE || character[i].location == LEFTBOATSIDE) 
                character[i].setTexture("bin/padre3.png");
        }
    }

    if (isAtLeastOne == true) { //Caso tenha passado por pelo menos de uma verificação, quer dizer que o jogador perdeu;
        return YOULOSE; //Retornando 1 como derrota;
    }
    
    //Caso existam 6 personagens no lado esquerdo, 3 padres e 3 canibais, o jogo está finalizado;
    if (MAXIMUMCHARSINONESIDE - rightSideCanibals == MAXIMUMCHARSINONESIDE && MAXIMUMCHARSINONESIDE - rightSidePriests == MAXIMUMCHARSINONESIDE) {
        return YOUWIN; //Jogador ganhou o jogo;
    }

    return CONTINUE;
}

/*

void GameData::printTime() 

    Essa função irá printar quanto tempo tem de jogo, quantos movimentos já foram realizados, na tela de jogo.

@param Phrase &time -> Passa como referência a frase time, onde armazena o tempo corretamente.
@param Phrase &movements -> Também como referência se passa a frase que armazena a quantidade de movimentos que o jogador
executou.
@return

*/

void GameData::printStatistics(Phrase &time, Phrase &movements) 
{
    std::string timeOnStringForm; //Instânciando o tempo como string que será usado para alterar o texto;
    std::string movesOnStringForm; //Colocando a quantidade de movimentos em string para colocar na frente em texto;

    if (gameTime.getElapsedTime().asSeconds() > currentTime) { //Comparando o tempo atual com o antigo que estava printado;
        currentTime = gameTime.getElapsedTime().asSeconds();  //Pegando o tempo atual;

        timeOnStringForm = std::to_string(currentTime); //Transformando para string;

        time.text.setString(timeOnStringForm); //Atribuindo realmente para o texto, para ser printado na proxima execução da tela;
    }

    if (moves > currentMoves) { //Aqui fazendo a mesma verificação do tempo, caso a quantidade de movimentos seja alterada;
        currentMoves = moves; //Atribuindo a quantidade de movimentos alterada;

        movesOnStringForm = std::to_string(currentMoves); //Transformando para string;

        movements.text.setString(movesOnStringForm); //Colocando realmente agora no texto;
    }

}

/*

void GameData::initializeStacks (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces)

    Essa função serve para tirar um pouco de instanciações do jogo.cpp, para descarregar um pouco aquela função.

@param std::stack<sf::Vector2f> &leftSpaces -> São os espaços que estão vazios no lado direito do mapa.
@param std::stack<sf::Vector2f> &boatSpaces -> Os espaços vazios no barco.
@return

*/

void GameData::initializeStacks (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces)
{
    //Atribuindo os lugares escolhidos para os personagens no lado esquerdo;
    leftSpaces.push(sf::Vector2f(100, 150));
    leftSpaces.push(sf::Vector2f(300, 140));
    leftSpaces.push(sf::Vector2f(500, 130));
    leftSpaces.push(sf::Vector2f(120, 450));
    leftSpaces.push(sf::Vector2f(360, 450));
    leftSpaces.push(sf::Vector2f(110, 740));

    //Atribuindo os lugares dos barcos, iniciais pelo menos;
    boatSpaces.push(sf::Vector2f(1240, 680));
    boatSpaces.push(sf::Vector2f(1065, 680));
}

/*

void GameData::gameOverScreen (sf::Window &window)

*/
void GameData::gameOverScreen (sf::Window &window)
{




}

//--------------------------------------------------------------------------------------------------------------------------------------------