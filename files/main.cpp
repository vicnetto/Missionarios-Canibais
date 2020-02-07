#include <iostream>
#include <SFML/Graphics.hpp>

#include "jogo.h"
#include "auxiliares.h"

int main () {

    Jogo jogo;

    jogo.window.create(sf::VideoMode(WIDTH, HEIGHT), "Missionarios e Canibais");

    jogo.window.setFramerateLimit(100);

    jogo.mainMenu();

    return 0;
}