#include <iostream>
#include <SFML/Graphics.hpp>

#include "jogo.h"
#include "auxiliares.h"

int main () {

    Jogo jogo;  

    jogo.window.create(sf::VideoMode(WIDTH, HEIGHT), "Missionarios e Canibais", sf::Style::Default);

    jogo.window.setFramerateLimit(60);

    jogo.mainMenu();

    return 0;
}