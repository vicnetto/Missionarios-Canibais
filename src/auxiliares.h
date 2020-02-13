#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

/*

class Pharase
-> Classe feita para palavras, com todas as suas organizações.


VARIÁVEIS PÚBLICAS:
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


VARIÁVEIS PÚBLICAS:
- sf::Sprite sprite -> Serve para declarar o sprite.
- sf::Texture texture -> Serve para adicionar a textura do sprite e deixar ela salva dentro da struct, caso seja necessário acessar ela novamente.

FUNÇÕES PÚBLICAS:
- Sprites -> Esse é o construtor, onde é o objetivo principal da criação dessa struct, para deixar as coisas mais organizadas.
- bool setTexture () -> O objetivo dessa é colocar a textura no sprite, e principalmente verificar se está com algum problema no arquivo.
- bool isHovering () -> Essa função é exatamente a mesma da classe Phrases, mas com uma diferença mínima que se trata de sprites.

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
        bool isHovering (sf::Vector2i mousePos);
};

/*

class Character : public Sprites
-> Essa classe, filha da classe Sprites, é uma classe para armazenar os dados dos personagens do jogo. Onde eles estão, qual é o personagem, pricipalmente.


VARIÁVEIS PÚBLICAS:
- bool type -> Tem o objetivo único de saber se trata de um missionário (true) ou um canibal (false).
- int location -> Essa variável armazena qual é o local do personagem, se ele está no lado esquerdo (0), no barco (1) ou no lado direito (2).

FUNÇÕES PÚBLICAS:
- Character () -> É o grande construtor, ele inicializa todas as variáveis, até o de sua classe mãe.
- void setCharacter () -> Essa função, importantíssima, serve como um constutor, porém como é instanciado um vetor no main, é necessário uma função para tratar com cada objeto,
onde se encontra essa função.

*/
class Character : public Sprites
{
    public:
        bool type; //False é canibal e true é missionário;
        int location; //1 é para lado esquerdo, 2 é para o barco e 3 é no lado direito;

    public:
        Character();
        void setCharacter(bool t, int l, sf::Vector2f scale, sf::Vector2f position);
};

/*

class Boat : public Sprites
-> Essa classe é uma para auxiliar o barco do jogo, é uma das mais importantes para o funcionamento do jogo.


VARIÁVEIS PÚBLICAS:
- int location -> Essa variável armazena em qual local está o barco, se é no lado esquerdo (true), se é no lado direito (false).
- int quantChar -> Nessa, é para representar quantos personagens estão no barco, para colocar um limite de dois.

FUNÇÕES PÚBLICAS:
- Boat () -> Esse construtor serve para iniciar todas as variáveis e poupar código no jogo.cpp.
- void moveBoat () -> A função moveBoat () tem o objetivo único de mover o barco para o outro lado.

*/
class Boat : public Sprites
{
    public:
        bool location; //True = lado esquerdo, false = lado direito;
        bool moving; //True quando está se movendo, e false quando está parado.
        int quantChar; //Quantidade de pessoas dentro do barco;

        int xinitial;
        int xfinal;
        int speed;
    
    public:
        Boat(bool location, int quantChar, sf::Vector2f scale, sf::Vector2f position);
        void moveBoat ();

};

#endif /* AUXILIARES_H */
