#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "gamedata.h"

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
int GameData::gameOver() {
    if (rightSideCanibals > rightSidePriests || 3 - rightSideCanibals > 3 - rightSidePriests) //Caso existam mais canibais do que padres em um lado, o jogo termina, pois o jogador perdeu;
        return 1; //Retornando 1 como derrota;
    
    if (3 - rightSideCanibals == 3 && 3 - rightSidePriests == 3) //Caso existam 6 personagens no lado esquerdo, 3 padres e 3 canibais, o jogo está finalizado;
        return 2; //Jogador ganhou o jogo;

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------