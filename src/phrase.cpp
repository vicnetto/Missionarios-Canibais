#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "phrase.h"

//---------------------------------------------------------- PHRASE -------------------------------------------------------------------------

/*

Phrase::Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position)

    É o construtor da classe Phrase, seta inicialmente tudo o que será necessário, para logo em seguida colocar a fonte.

@param std::string phrase -> Sendo uma string, mostra o real conteúdo do que estará escrito na frase.
@param int scale -> Aqui configura-se o tamanho da escala para a frase.
@param sf::Color color -> Colocando cor na letra, onde pode ser escolhida pela sf::Color.
@param sf::Vector2f position -> Qual a posiçao inicial da frase, no eixo X/Y.
@return

*/
Phrase::Phrase(std::string phrase, int scale, sf::Color color, sf::Vector2f position) {
    text.setString(phrase);
    text.setCharacterSize(scale);
    text.setFillColor(color);
    text.setPosition(position);
}

/*

-> bool Phrase::setFont(std::string way)

    Tem como parâmetro o caminho até o arquivo, onde tenta aplicar essa fonte para o texto.

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

    Essa função é para ver se o mouse está em cima de alguma coisa, para fazer o click no local certo.

@param mousePos -> Posição do mouse na janela.
@return -> Caso esteja em cima é "true", caso contrário "false".

*/
bool Phrase::isHovering(sf::Vector2i mousePos) {

    if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) //Pega a posição que está o texto e compara com a atual do mouse, caso esteja em cima, retorna true;
        return true;

    return false; //Ou false caso esteja fora;
}

//-------------------------------------------------------------------------------------------------------------------------------------------