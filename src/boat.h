#ifndef BOAT_H
#define BOAT_H

#include "sprites.h"

class Character;

/*

class Boat : public Sprites
-> Essa classe é uma para auxiliar o barco do jogo, é uma das mais importantes para o funcionamento do jogo.


VARIÁVEIS PÚBLICAS:
- int isOnTheLeft -> Essa variável armazena em qual local está o barco, se é no lado esquerdo (true), se é no lado direito (false).
- int moving -> Essa variável tem a função de saber onde está o barco, se está se movendo ou não. Ou seja, true para movimentando, e false para não movimentando.
- int quantChar -> Nessa, é para representar quantos personagens estão no barco, para colocar um limite de dois.

- int xinitial -> Essa variável serve para saber onde é o x inicial do barco, onde ele está no momento, ela só é alterada quando o barco se move, pela função moveBoat ();
- int xfinal -> Essa variável mostra para o main aonde o barco deve parar, para a sua animação de movimento parar junto.
- int speed -> Essa variável é simplesmente a velocidade, setada por um define dentro do auxiliares.cpp.

FUNÇÕES PÚBLICAS:
- Boat () -> Esse construtor serve para iniciar todas as variáveis e poupar código no jogo.cpp.
- void moveBoat () -> A função moveBoat () tem o objetivo único de mover o barco para o outro lado.
- void moveBoatFreePos () -> Essa função move as posições do barco, faz com que no final de cada movimento do barco elas sejam atualizadas com a nova posição;

*/
class Boat : public Sprites
{
    public:
        bool isOnTheLeft; //True = lado esquerdo, false = lado direito;
        bool moving; //True quando está se movendo, e false quando está parado.
        int quantChar; //Quantidade de pessoas dentro do barco;

        int xinitial; //Essa variável tem função apenas no moveBoat(), para saber onde está seu x inicial;
        int xfinal; //Com o mesmo motivo da de cima, essa é para saber onde fica o x final, ou seja, onde o barco quer chegar;
        int speed; //Essa é a velocidade do barco, que não é bem alterada, é colocada como define no auxiliares.cpp
    
    public:
        Boat(bool isOnTheLeft, int quantChar, sf::Vector2f scale, sf::Vector2f position);
        void moveBoat ();
        void moveBoatFreePos (std::stack<sf::Vector2f> &boatSpaces);
};


#endif /* BOAT_H */