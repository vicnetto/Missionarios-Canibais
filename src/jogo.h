#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "gamedata.h"

#define WIDTH 1920
#define HEIGHT 1080

/*

class Jogo
-> Classe principal do jogo, com TODAS as informações principais.

VARIÁVEIS PÚBLICAS:
- sf::RenderWindow window -> Instancia a janela, coloca todas as suas configurações para ser usado por todo o jogo.
- sf::Event event -> Serve para o tratamento de eventos, ele foi colocado dentro da struct para poder ser utilizado com mais facilidade.


FUNÇÕES PÚBLICAS:
- int mainMenu () -> O motivo principal é o mesmo do nome, serve para fazer o menu de uma forma mais organizada, tendo todos os parâmentros
dentro da classe Jogo.
- int jogar () -> Essa função é a principal do jogo, pelo menos onde é chamado e organizado todas as verificações do jogo.
- bool startScreen () -> Essa função tem como objetivo montar uma tela inicial, para preparar o jogador do início do jogo.

*/

class Jogo {
    public:
        sf::RenderWindow window;
        sf::Event event;

    public:
        int mainMenu ();
        int start (GameData &gameData, std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &rightSpaces, std::stack<sf::Vector2f> &boatSpaces);
        bool startScreen ();
};

#endif /* JOGO_H */