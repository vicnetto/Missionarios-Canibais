#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "gamedata.h"
#include "phrase.h"
#include "character.h"
#include "boat.h"

#define RIGHTSIDE 3
#define SCALEPRIEST sf::Vector2f(0.32, 0.32) //Tamanho da sprite do padre;
#define SCALECANNIBAL sf::Vector2f(0.385, 0.385) //Tamanho da sprite do canibal;

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
    numbAttempts = 0;
    rightSideCanibals = 3;
    rightSidePriests = 3;
    totalMoves = 0;

    currentTime = 0;
    currentMoves = 0;
    currentTotalMoves = 0;
    currentNumbAttempts = 0;
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

void GameData::printStatistics() 

    Essa função irá printar quanto tempo tem de jogo, quantos movimentos já foram realizados, na tela de jogo.

@param Phrase &time -> Passa como referência a frase time, onde armazena o tempo corretamente.
@param Phrase &movements -> Também como referência se passa a frase que armazena a quantidade de movimentos que o jogador
executou.
@return

*/

void GameData::printStatistics(Phrase &time, Phrase &movements, Phrase &attempts, Phrase &totalMovements) 
{
    std::string onStringForm; //Instânciando o tempo como string que será usado para alterar o texto;

    if (gameTime.getElapsedTime().asSeconds() > currentTime) { //Comparando o tempo atual com o antigo que estava printado;
        currentTime = gameTime.getElapsedTime().asSeconds();  //Pegando o tempo atual;

        onStringForm = std::to_string(currentTime); //Transformando para string;

        time.text.setString(onStringForm); //Atribuindo realmente para o texto, para ser printado na proxima execução da tela;
    }

    if (moves > currentMoves || moves == 0) { //Aqui fazendo a mesma verificação do tempo, caso a quantidade de movimentos seja alterada;
        currentMoves = moves; //Atribuindo a quantidade de movimentos alterada;

        onStringForm = std::to_string(currentMoves); //Transformando para string;

        movements.text.setString(onStringForm); //Colocando realmente agora no texto;
    }

    if (totalMoves > currentTotalMoves) {
        currentTotalMoves = totalMoves; //Atribuindo a quantidade de movimentos totais alterada;

        onStringForm = std::to_string(currentTotalMoves); //Transformando para string;

        totalMovements.text.setString(onStringForm); //Colocando realmente agora no texto;

    }

    if (numbAttempts > currentNumbAttempts) {
        currentNumbAttempts = numbAttempts; //Atribuindo a quantidade de tentativas alterada;

        onStringForm = std::to_string(currentNumbAttempts); //Transformando para string;

        attempts.text.setString(onStringForm); //Colocando realmente agora no texto;

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

void GameData::gameOverScreen (sf::RenderWindow &window)

    Essa função tem como objetivo printar para o jogador quais foram os personagens que morreram e perguntar
se o jogador quer iniciar o jogo novamente.

*/
void GameData::gameOverScreen (sf::RenderWindow &window)
{
    Phrase voceperdeu ("TENTAR NOVAMENTE", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.365, HEIGHT * 0.44)); //Texto de tentar novamente que aparece caso o jogador perca;

    sf::Event event; //Instanciando o tratador de evento;
    sf::Mouse mouse; //Instanciando o que vai salvar os movimentos do mouse;

    if (!voceperdeu.setFont("bin/Pixel.ttf")) //Colocando o arquivo da fonte dentro da frase e verificando se é possível abrir o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl; //Frase caso não seja possível abrir o arquivo;

        return;
    }

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //Caso fechar a janela;
                window.close();

                return; //Retorna;;

                break;
            

            case sf::Event::MouseMoved:
                if (voceperdeu.isHovering(mouse.getPosition(window))) { //Faz o tratamento clássico caso o mouse passe por cima da frase;
                    voceperdeu.text.setFillColor(sf::Color::Blue); //Coloca cor azul caso esteja em cima;
                } else {
                    voceperdeu.text.setFillColor(sf::Color::Yellow); //Ou amarelo caso não esteja em cima;
                }
                
            break;

            case sf::Event::MouseButtonPressed:
                if (voceperdeu.isHovering(mouse.getPosition(window))) //Quando aperta, ele verifica se está em cima e retorna diretamente para a função start() novamente;
                    return;
            }
        }

        window.draw(voceperdeu.text); //Printa o texto;

        window.display(); //Mostrando todas as mudanças que foram feitas;
    }
}

/*

void GameData::resetStacksAndReplace (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Character (&character) [6], Boat &boat)

    Essa função, extremamente imporante para o reinício do jogo, serve para resetar todas as posições dos personagens e as
posições disponíveis para o jogador nos outros lados.

@param std::stack<sf::Vector2f> &leftSpaces -> São os espaços livres no lado direito do mapa, ou seja, no lado contrário da onde os personagens
"nascem".
@param std::stack<sf::Vector2f> &boatSpaces -> São os espaços livres dentro do barco.
@param std::stack<sf::Vector2f> &rightSpaces -> São os espaços livres dos personagens no lado direito, que nesse caso, na hora de resetar o jogo
ela deve estar vazia.
@param Character (&character) [6] -> São os 6 personagens, que são passados nessa função para resetar todas as suas posições e localizações.
@param Boat &boat -> Essa parte serve para mexer com o barco, para mudar a sua posição e alterar as posições livres dentro dele.
@return

*/
void GameData::resetStacksAndReplace (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Character (&character) [6], Boat &boat)
{
    rightSideCanibals = 3; //Inicialmente, existem 3 canibais do lado direito;
    rightSidePriests = 3; //E também exitem 3 padres do lado direito;

    //Primeiro resetando todas as stacks;
    while (!leftSpaces.empty())
        leftSpaces.pop();

    while (!boatSpaces.empty())
        boatSpaces.pop();

    while (!rightSpaces.empty())
        rightSpaces.pop();

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

    //Setando todas as localidades dos personagens novamente, para deixar eles no local certo apos o reset do jogo;
    character[0].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1200, 180));
    character[1].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1430, 170));
    character[2].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1420, 450));
    character[3].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 160));
    character[4].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1640, 450));
    character[5].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 750));

    //Tirando as texturas de morte atribuidas para os padres no final do jogo;
    character[0].setTexture("bin/padre1.png");
    character[1].setTexture("bin/padre1.png");
    character[2].setTexture("bin/padre1.png");

    //Mudando todas as configurações do barco para as iniciais novamente;
    boat.sprite.setPosition(sf::Vector2f(1032, 900));
    boat.brightsprite.setPosition(sf::Vector2f(1032, 900));
    boat.isOnTheLeft = false;
    boat.quantChar = 0;
    boat.sprite.setScale(0.5, 0.5);
    boat.brightsprite.setScale(0.5, 0.5);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
