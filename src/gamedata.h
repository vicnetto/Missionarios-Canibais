#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "phrase.h"

/*

class GameData
-> Essa classe tem como objetivo armazenar todos os dados do jogo, e fazer as verificações necessárias de vitória ou derrota.

VARIÁVEIS PÚBLICAS:
- int moves -> A quantidade de movimentos que foram realizados pelo jogador.
- int rightSideCanibals -> Quantos canibais estão no lado direito nesse momento.
- int rightSidePriests -> Quantos missionários estão do lado direito nesse momento do jogo.

FUNÇÕES PÚBLICAS:
- GameData() -> É o construtor padrão do jogo, nele coloca os dados iniciais do jogo, onde começam os personagens e tudo mais.
- bool verifyWinConditions() -> É o verificador final do jogo, caso o jogador perca ou ganhe. Caso nada tiver acontecido, retorna-se 1. Caso o jogador tenha
perdido, retorna-se 2. Caso o jogador ganhe, retorna-se 3.
- int endGame() -> Essa função irá tratar corretamente as win conditions e irá ver se o jogador ganhou ou perdeu. Caso tenha ocorrido um desses dois, ele irá
printar algumas coisas de fim de jogo, como a pontuação.
- void printStatistics(Phrase &time, Phrase &movements); -> Essa função irá printar quanto tempo tem de jogo, quantos movimentos já foram realizados, na tela de jogo.
*/
class GameData {
    public:
        int moves;
        int rightSideCanibals;
        int rightSidePriests;

    public:
        GameData();
        int verifyWinConditions();
        int endGame();
        void printStatistics(Phrase &time, Phrase &movements);
        
};

#endif /* GAMEDATA_H */