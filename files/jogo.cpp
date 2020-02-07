#include <SFML/Graphics.hpp>
#include <iostream>

#define FRAMETIME 0.01

#include "jogo.h"
#include "auxiliares.h"

int Jogo::mainMenu () {
    sf::Clock clock; //Relógio auxiliador da movimentação da tela no menu inicial;

    sf::Clock test;

    int currentX = 0, currentY = 0;

    sf::Color brown (150, 75, 0); //Setando a cor para utilizala no men;

    Phrase miss ("Missionarios", 70, brown, sf::Vector2f(WIDTH * 4 / 17, HEIGHT / 9)); //Colocando a frase título;
    Phrase e ("e", 70, sf::Color::Red, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 45)); //Colocando um "e", que pertence ao menu;
    Phrase cani ("CANIBAIS", 70, sf::Color::Blue, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 100)); //Colocando a ultima peça faltante, o canibais;

    Phrase jogar ("Jogar", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 9, HEIGHT / 2)); //Colocando as três opções abaixo, que podem ser escolhidasd no menu;
    Phrase sair ("Sair", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 8.7, HEIGHT * 2 / 2.5));
    Phrase comojogar ("Como jogar", 40, sf::Color::Cyan, sf::Vector2f (WIDTH * 4 / 9.9, HEIGHT * 2 / 3.1));

    Sprites fundo (sf::Vector2f(1, 1), sf::Vector2f(0,0)); //Instanciando o fundo, com a primeira parte da textura;

    //Aqui é a verificação se existem os arquivos das fontes;
    if (!miss.setFont("archives/FFF_Tusj.ttf") || !jogar.setFont("archives/good times rg.ttf") || !sair.setFont("archives/good times rg.ttf") || !comojogar.setFont("archives/good times rg.ttf") || !e.setFont("archives/Vegan.ttf") || !cani.setFont("archives/Nightmare.ttf"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    if (!fundo.setTexture("archives/Frames1.png")) //Carregando o fundo do menu;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    fundo.texture.setSmooth(true); //Colocando uma suavidade na textura;

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

        fundo.sprite.setTextureRect(sf::IntRect(XTEXT * currentX, YTEXT * currentY, XTEXT, YTEXT));

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        window.draw(fundo.sprite);

        window.draw(miss.text); //Escreve a palavra depois de ter limpado;
        window.draw(e.text);
        window.draw(cani.text);

        window.draw(jogar.text);
        window.draw(sair.text);
        window.draw(comojogar.text);

        window.display(); //Mostra novamente o que está sendo printado na tela;

        if (clock.getElapsedTime().asSeconds() > FRAMETIME) { //Fazendo aqui como o fundo irá se mover;

            if (currentY * YTEXT == 23760) {
                currentY = -1;
                currentX += 1;
            }

            if (currentY * YTEXT == 22680 && currentX == 2) {
                currentY = -1;
                currentX = 0;
            }

            if (currentY * YTEXT != 23760) {
                if (currentY * YTEXT != 22680)
                    currentY += 1;

                if (currentY * YTEXT == 22680 && currentX != 2)
                    currentY += 1;
            }

            std::cout << currentX * XTEXT << "   " << currentY * YTEXT << std::endl;

            clock.restart();
        }
    }

    return 0;
}