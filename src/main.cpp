#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>

#include "jogo.h"

int main () {
    Jogo jogo; //Iniciando com a instância do jogo, onde todas as funções serão chamadas;

    jogo.window.create(sf::VideoMode(WIDTH, HEIGHT), "Missionarios e Canibais", sf::Style::Default); //Colocando os nomes e algumas configurações na janela;

    jogo.window.setFramerateLimit(60); //Diminuindo um pouco o processamento do computador, que para alguns computadores, acaba sendo dificil processar muitos quadros;

    jogo.mainMenu(); //Chamando a função menu, onde irá dar continuação para o resto;

    return 0;
}
