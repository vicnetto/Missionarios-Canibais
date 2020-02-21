#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "phrase.h"

//---------------------------------------------------------- PHRASE -------------------------------------------------------------------------

/*

Phrase::Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position)
@param std::string phrase -> Sendo uma string, mostra o real conteúdo do que estará escrito na frase.
@param int scale -> Aqui configura-se o tamanho da escala para a frase.
@param sf::Color color -> Colocando cor na letra, onde pode ser escolhida pela sf::Color.
@param sf::Vector2f position -> Qual a posiçao inicial da frase, no eixo X/Y.

*/
Phrase::Phrase(std::string phrase, int scale, sf::Color color, sf::Vector2f position) {
    text.setString(phrase);
    text.setCharacterSize(scale);
    text.setFillColor(color);
    text.setPosition(position);
}

/*

-> bool Phrase::setFont(std::string way)
@param way -> Caminho até o arquivo.
@return -> Sucesso da operação.

*/
bool Phrase::setFont(std::string way) {

    if (!font.loadFromFile(way)) //Verificando se é possível acessar o arquivo;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return false; //Problema em encontrar o arquivo.
    }

    text.setFont(font);

    return true;
}

/*

bool Phrase::isHovering(sf::Vector2i mousePos, Phrase phrase)
@param mousePos -> Posição do mouse na janela.
@return -> Caso esteja em cima é "true", caso contrário "false".

*/
bool Phrase::isHovering(sf::Vector2i mousePos) {

    if (text.getGlobalBounds().contains(mousePos.x, mousePos.y))
        return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------