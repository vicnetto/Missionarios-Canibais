#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string> 
#include <bits/stdc++.h> 

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
- Sprites () -> Esse é o construtor, onde é o objetivo principal da criação dessa classe, para deixar as coisas mais organizadas.
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

#endif /* SPRITES_H */