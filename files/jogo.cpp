#include <SFML/Graphics.hpp>
#include <iostream>

#include "jogo.h"
#include "auxiliares.h"

int Jogo::mainMenu () {

    Phrase missecan ("Missionarios e Canibais", 60, sf::Color::Green, sf::Vector2f(WIDTH * 4 / 13, HEIGHT / 6)); //Colocando a frase título;
    Phrase jogar ("Jogar", 30, sf::Color::Red, sf::Vector2f (WIDTH * 2 / 3, HEIGHT / 2));

    if (!missecan.setFont("archives/FFF_Tusj.ttf")) //Verificando se ela consegue colocar a fonte;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }


    while (window.isOpen()) //Começando o loop principal do menu;
    {

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            
            case sf::Event::Closed:
                window.close();

                break;
            }
        }

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        window.draw(missecan.text); //Escreve a palavra depois de ter limpado;

        window.display(); //Mostra novamente o que está sendo printado na tela;
    }

    return 0;
}