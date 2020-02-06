#include <SFML/Graphics.hpp>
#include <iostream>

#include "jogo.h"
#include "auxiliares.h"

int Jogo::mainMenu () {

    Phrase missecan ("Missionarios e Canibais", 60, sf::Color::Blue, sf::Vector2f(WIDTH * 4 / 13, HEIGHT / 6)); //Colocando a frase título;
    Phrase jogar ("Jogar", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 9, HEIGHT / 2)); //Colocando as três opções abaixo, que podem ser escolhidasd no menu;
    Phrase sair ("Sair", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 8.7, HEIGHT * 2 / 2.5));
    Phrase comojogar ("Como jogar", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 9.9, HEIGHT * 2 / 3.1));

    //Aqui é a verificação se existem os arquivos das fontes;
    if (!missecan.setFont("archives/FFF_Tusj.ttf") || !jogar.setFont("archives/good times rg.ttf") || !sair.setFont("archives/good times rg.ttf") || !comojogar.setFont("archives/good times rg.ttf"))
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
        window.draw(jogar.text);
        window.draw(sair.text);
        window.draw(comojogar.text);

        window.display(); //Mostra novamente o que está sendo printado na tela;
    }

    return 0;
}