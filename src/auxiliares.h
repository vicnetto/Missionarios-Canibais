#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <bits/stdc++.h>

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
        Phrase(std::string phrase, int scale, sf::Color color, sf::Vector2f position);
        bool setFont (std::string way);
        bool isHovering (sf::Vector2i mousePos);
};

/*

class Sprites
-> Classe feita para facilitar o processo de criação dos sprites, resumindo basicamente ele em um construtor e futuramente adicionando algumas novas variáveis.


VARIÁVEIS PÚBLICAS:
- sf::Sprite sprite -> Serve para declarar o sprite.
- sf::Texture texture -> Serve para adicionar a textura do sprite e deixar ela salva dentro da struct, caso seja necessário acessar ela novamente.
- sf::Sprite brightsprite -> O objetivo dessa variável é moldar a sprite brilhante do persoangem, quando ele estiver prestes a ser selecionado.
- sf::Texture brighttexture -> Essa variável serve para setar a textura da brightsprite, com a textura mais brilhante para opção.
- bool bright -> Já esta variável serve para indicar se o mouse está em cima ou não, ou seja, true para sim, e false para não.

FUNÇÕES PÚBLICAS:
- Sprites () -> Esse é o construtor, onde é o objetivo principal da criação dessa struct, para deixar as coisas mais organizadas.
- bool setBrightTexture (std::string way) -> Essa função tem como objetivo setar e retornar se houve sucesso ao mudar a textura da BrightSprite, ela funciona do mesmo modo da
função da classe Sprites, porém com variáveis diferentes.
- bool setTexture () -> O objetivo dessa é colocar a textura no sprite, e principalmente verificar se está com algum problema no arquivo.
- bool isHovering () -> Essa função é exatamente a mesma da classe Phrases, mas com uma diferença mínima que se trata de sprites.

*/
class Sprites
{
    public:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Sprite brightsprite; //Esse é o sprite do personagem como opção;
        sf::Texture brighttexture; //Essa é a textura do personagem como opção;
        bool bright; //Modifica ao saber que o mouse está em cima;

    public:
        Sprites();
        Sprites(sf::Vector2f scale, sf::Vector2f position);
        bool setBrightTexture (std::string way); //Função para configurar a textura da opção.
        bool setTexture (std::string way);
        bool isHovering (sf::Vector2i mousePos);
};

/*

class Boat : public Sprites
-> Essa classe é uma para auxiliar o barco do jogo, é uma das mais importantes para o funcionamento do jogo.


VARIÁVEIS PÚBLICAS:
- int location -> Essa variável armazena em qual local está o barco, se é no lado esquerdo (true), se é no lado direito (false).
- int moving -> Essa variável tem a função de saber onde está o barco, se está se movendo ou não. Ou seja, true para movimentando, e false para não movimentando.
- int quantChar -> Nessa, é para representar quantos personagens estão no barco, para colocar um limite de dois.

- int xinitial -> Essa variável serve para saber onde é o x inicial do barco, onde ele está no momento, ela só é alterada quando o barco se move, pela função moveBoat ();
- int xfinal -> Essa variável mostra para o main aonde o barco deve parar, para a sua animação de movimento parar junto.
- int speed -> Essa variável é simplesmente a velocidade, setada por um define dentro do auxiliares.cpp.

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

        int xinitial; //Essa variável tem função apenas no moveBoat(), para saber onde está seu x inicial;
        int xfinal; //Com o mesmo motivo da de cima, essa é para saber onde fica o x final, ou seja, onde o barco quer chegar;
        int speed; //Essa é a velocidade do barco, que não é bem alterada, é colocada como define no auxiliares.cpp
    
    public:
        Boat(bool location, int quantChar, sf::Vector2f scale, sf::Vector2f position);
        void moveBoat ();

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
- void moveTo () -> Essa função serve para organizar os comandos de mover o personagem, para dentro do barco ou para fora.

*/
class Character : public Sprites
{
    public:
        bool type; //False é canibal e true é missionário;
        int location; //1 é para lado esquerdo, 2 é para o barco e 3 é no lado direito;

    public:
        Character(); //Construtor básico da classe;
        void setCharacter(bool type, int location, sf::Vector2f scale, sf::Vector2f position); //É basicamente um construtor com um extra, ele pode ser chamado depois da instância.
        void moveTo (std::stack<sf::Vector2f> &leftSpaces, std::stack<sf::Vector2f> &boatSpaces, std::stack<sf::Vector2f> &rightSpaces, Boat &boat); //Essa função tem como objetivo recolocar o persongem, caso o jogador tenha clicado nele.
};

#endif /* AUXILIARES_H */
