#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "gamedata.h"
#include "phrase.h"

#define MAXIMUMCHARSINONESIDE 3
#define CONTINUE 0 
#define YOULOSE 1
#define YOUWIN 2


//------------------------------------------------------ GAMEDATA ----------------------------------------------------------------------------

/*

GameData::GameData()
@param
@return

*/
GameData::GameData() {
    moves = 0;
    rightSideCanibals = 3;
    rightSidePriests = 3;
}

/*

int GameData::gameOver()

    É o verificador final do jogo, caso o jogador perca ou ganhe. Caso nada tiver acontecido, retorna-se 1. Caso o jogador tenha
perdido, retorna-se 2. Caso o jogador ganhe, retorna-se 3.

@param
@return int -> 0 para continuação do jogo, 1 para jogador perdeu o jogo e 2 para jogador ganhou o jogo.

*/
int GameData::verifyWinConditions() {
    bool isAtLeastOne = false;

    //Caso existam mais canibais do que padres em um lado, o jogo termina, pois o jogador perdeu;
    if (rightSideCanibals > rightSidePriests && rightSidePriests != 0)
        isAtLeastOne = true;
    
    if (MAXIMUMCHARSINONESIDE - rightSideCanibals > MAXIMUMCHARSINONESIDE - rightSidePriests && MAXIMUMCHARSINONESIDE - rightSidePriests != 0)
        isAtLeastOne = true;

    if (isAtLeastOne == true) {
        return YOULOSE; //Retornando 1 como derrota;
    }
    
    //Caso existam 6 personagens no lado esquerdo, 3 padres e 3 canibais, o jogo está finalizado;
    if (MAXIMUMCHARSINONESIDE - rightSideCanibals == MAXIMUMCHARSINONESIDE && MAXIMUMCHARSINONESIDE - rightSidePriests == MAXIMUMCHARSINONESIDE) {
        return YOUWIN; //Jogador ganhou o jogo;
    }

    return CONTINUE;
}

/*

int GameData::endGame();

    Essa função irá tratar corretamente as win conditions e irá ver se o jogador ganhou ou perdeu. Caso tenha ocorrido um desses dois, ele irá
printar algumas coisas de fim de jogo, como a pontuação.

@param
@return int -> Retorna caso o jogador tenha ganho (valor 1), caso ele tenha perdido (valor 2) ou para o jogo continuar normalmente (valor 0).

*/

int GameData::endGame() {
    if (verifyWinConditions() == YOUWIN) {
        return YOUWIN;
    }

    if (verifyWinConditions() == YOULOSE) {
        return YOULOSE;
    }

    return CONTINUE;
}

/*

void GameData::printStatistics() 

    Essa função irá printar quanto tempo tem de jogo, quantos movimentos já foram realizados, na tela de jogo.

@param Phrase &time -> Passa como referência a frase time, onde armazena o tempo corretamente.
@param Phrase &movements -> Passa como referências os movimentos, pois eles terão que ser alterados dentro de seu texto principal.
@return

*/

void GameData::printStatistics(Phrase &time, Phrase &movements) {

}

//--------------------------------------------------------------------------------------------------------------------------------------------