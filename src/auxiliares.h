#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

/*

class Pharase
-> Classe feita para palavras, com todas as suas organizações.


DECLARAÇÕES PÚBLICAS:
- sf::Text text -> Tem basicamente tudo sobre o texto, pode ser alterado com tudo.
- sf::Font font -> Serve para mudar a fonte do texto.

FUNÇÕES PÚBLICAS:
- Phrase -> É o construtor da classe Phrase, seta inicialmente tudo o que será necessário, para logo em seguida colocar a fonte.
- bool setFont -> Tem como parâmetro o caminho até o arquivo, onde tenta aplicar essa fonte para o texto.
- int isHovering () -> Essa função é para ver se o mouse está em cima de alguma coisa, para fazer o click no local certo.

*/
class Phrase 
{
    public:
        sf::Text text;
        sf::Font font;
        bool hovering;

    public:
        Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position);
        bool setFont (std::string way);
        bool isHovering (sf::Vector2i mousePos);
};

/*

class Sprites
-> Classe feita para facilitar o processo de criação dos sprites, resumindo basicamente ele em um construtor e futuramente adicionando algumas novas variáveis.


DECLARAÇÕES PÚBLICAS:
- sf::Sprite sprite -> Serve para declarar o sprite.
- sf::Texture texture -> Serve para adicionar a textura do sprite e deixar ela salva dentro da struct, caso seja necessário acessar ela novamente.

FUNÇÕES PÚBLICAS:
- Sprites -> Esse é o construtor, onde é o objetivo principal da criação dessa struct, para deixar as coisas mais organizadas.
- bool setTexture () -> O objetivo dessa é colocar a textura no sprite, e principalmente verificar se está com algum problema no arquivo.

*/
class Sprites
{
    public:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Sprites();
        Sprites(sf::Vector2f size, sf::Vector2f position);
        bool setTexture (std::string way);
};

#endif /* AUXILIARES_H */
