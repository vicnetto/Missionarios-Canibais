#include <iostream>
#include <SFML/Graphics.hpp>
#include "jogo.h"

int main () {

    Jogo jogo;

    jogo.window.create(sf::VideoMode(1920, 1080), "Missionarios e Canibais", sf::Style::Fullscreen);

    jogo.mainMenu();

    return 0;
}