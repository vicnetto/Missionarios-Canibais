#include <SFML/Graphics.hpp>
#include <iostream>

#define SLOWNESS 10000 //Lentidão da tela, a velocidade em que ela muda cada frame;
#define DISTANCE 1.7 //A distância que cada frame percorre (não são dados reais);
#define ENDX 3840 //Em qual lugar é finalizado a textura;
#define ENDY 0 //Em qual lugar é iniciado e finalizado a textura no eixo Y (constante);
#define XSTEXTURE 1920  //Qual o tamanho do eixo X de um frame completo na textura;
#define YSTEXTURE 1080 //O tamanho no eixo Y de um frame inteiro;

#define SCALEPRIEST sf::Vector2f(0.32, 0.32)
#define SCALECANNIBAL sf::Vector2f(0.42, 0.42)
#define SCALEBOAT sf::Vector2f(0.5, 0.5)
#define LEFTSIDE 0
#define MOVING 1
#define RIGHTSIDE 2
#define BOATXRIGHT 1032
#define BOATY 900

#include "jogo.h"
#include "auxiliares.h"

/*

int Jogo::mainMenu ()

*/
int Jogo::mainMenu () {
    sf::Clock clock; //Relógio auxiliador da movimentação da tela no menu inicial;

    int currentX = 0; //Posição atual da textura, no eixo X;

    sf::Color brown (150, 75, 0); //Setando a cor para utilizala no men;

    sf::Mouse mouse; //Declarando o mouse, para pegar as suas posições no futuro;

    Phrase miss ("Missionarios", 70, brown, sf::Vector2f(WIDTH * 4 / 17, HEIGHT / 9)); //Colocando a frase título;
    Phrase e ("e", 70, sf::Color::Yellow, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 45)); //Colocando um "e", que pertence ao menu;
    Phrase cani ("CANIBAIS", 70, sf::Color::Blue, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 100)); //Colocando a ultima peça faltante, o canibais;

    Phrase jogar ("Jogar", 65, sf::Color::Yellow, sf::Vector2f (WIDTH * 4 / 9, HEIGHT / 2)); //Colocando as três opções abaixo, que podem ser escolhidasd no menu;
    Phrase comojogar ("Como jogar", 65, sf::Color:: Yellow, sf::Vector2f (WIDTH * 4 / 9.9, HEIGHT * 2 / 3.065));
    Phrase sair ("Sair", 65, sf::Color::Yellow, sf::Vector2f (WIDTH * 4 / 8.7, HEIGHT * 2 / 2.5));
    Phrase victornetto ("POR: Victor Netto", 25, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.14, HEIGHT * 0.93));

    Sprites fundo (sf::Vector2f(1, 1), sf::Vector2f(0,0)); //Instanciando o fundo, com a primeira parte da textura;
    Sprites biblia (sf::Vector2f(0.3, 0.3), sf::Vector2f(WIDTH / 6.2, HEIGHT / 9)); //Colocando um pequeno detalhe de biblia ao lado do nome dos missionários.
    Sprites faca (sf::Vector2f(0.25, 0.25), sf::Vector2f(WIDTH * 3 / 5.3, (HEIGHT / 5.3))); //Sprite de faca ao lado do nome dos canibais.
    Sprites peteco (sf::Vector2f(0.2, 0.2), sf::Vector2f(WIDTH * 0.05, HEIGHT * 0.92)); //Logo do PETECO, o grande influenciador do projeto.

    //Aqui é a verificação se existem os arquivos das fontes;
    if (!miss.setFont("bin/FFF_Tusj.ttf") || !jogar.setFont("bin/afanan.ttf") || !sair.setFont("bin/afanan.ttf") || !comojogar.setFont("bin/afanan.ttf") || !e.setFont("bin/Vegan.ttf") || !cani.setFont("bin/Nightmare.ttf") || !victornetto.setFont("bin/Amilya.ttf"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    //Verifica se o arquivo da textura está disponível, caso contrário reporta o erro para o main, e para o console;
    if (!fundo.setTexture("bin/Background.png") || !biblia.setTexture("bin/biblia.png") || !faca.setTexture("bin/faca.png") || !peteco.setTexture("bin/LogoPETECO.png")) //Carregando o fundo do menu;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    //fundo.texture.setSmooth(true); //Colocando uma suavidade na textura;

    while (window.isOpen()) //Começando o loop principal do menu;
    {

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            
            case sf::Event::MouseMoved: //Tratando todas as possibilidades na hora de trocar as cores, caso tenha ou não tenha palavras.
                if (jogar.isHovering(mouse.getPosition(window))) {
                    jogar.text.setFillColor(sf::Color::Blue);
                }
                else
                    jogar.text.setFillColor(sf::Color::Yellow);

                if (comojogar.isHovering(mouse.getPosition(window)))
                    comojogar.text.setFillColor(sf::Color::Blue);
                else
                    comojogar.text.setFillColor(sf::Color::Yellow);

                if (sair.isHovering(mouse.getPosition(window)))
                    sair.text.setFillColor(sf::Color::Blue);
                else
                    sair.text.setFillColor(sf::Color::Yellow);

                break;

            case sf::Event::Closed: //Evento da janela fechada, no "X" da janela mesmo;
                window.close();

                break;

            case sf::Event::MouseButtonPressed: //Caso alguma tecla do mouse seja ativada;
                if (jogar.isHovering(mouse.getPosition(window))) {
                    start(); //Chama a função principal do jogo;

                    if (jogar.isHovering(mouse.getPosition(window))) { //Essa verificação é infelizmente necessária para não apresentar um bug na hora de voltar;
                        jogar.text.setFillColor(sf::Color::Blue);
                    }
                    else
                        jogar.text.setFillColor(sf::Color::Yellow);
                }

                if (sair.isHovering(mouse.getPosition(window))) //Essa opção é chamada na saida, caso o botão seja apertado em cima da área de sair;
                    return 0;

                break;
            }
        }

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        window.draw(fundo.sprite); //Nessa linha e abaixo, printando os sprites;
        window.draw(biblia.sprite);
        window.draw(faca.sprite);
        window.draw(peteco.sprite);

        window.draw(miss.text); //Escreve a palavra depois de ter limpado;
        window.draw(e.text);
        window.draw(cani.text);
        window.draw(victornetto.text);

        window.draw(jogar.text); //Nessa linha e abaixo, colocando as opções do menu;
        window.draw(sair.text);
        window.draw(comojogar.text);

        window.display(); //Mostra novamente o que está sendo printado na tela;

        
        if (clock.getElapsedTime().asMicroseconds() > SLOWNESS) { //Fazendo aqui como o fundo irá se mover;

            if (currentX + XSTEXTURE == ENDX) { //Essa parte retorna a textura para seu ponto inicial;
                currentX = 0;
            }

            else 
                currentX += DISTANCE; //Aumenta uma constante DISTÂNCIA, que vai ser basicamente a distância entre os frames;

            clock.restart();

            fundo.sprite.setTextureRect(sf::IntRect(currentX, ENDY, XSTEXTURE, YSTEXTURE)); //Coloca a textura em seu devido lugar, atualiza todo o tempo;
        }
    }

    return 0; //TODO: Futuramente, caso seja necessário essa função deve retornar algum valor;
}

/*

int Jogo::start()

*/
int Jogo::start() {
    int xinitial, xfinal, side;

    sf::Mouse mouse; //Variável para pegar os movimentos do mouse;

    Sprites background (sf::Vector2f(1, 1), sf::Vector2f(0,0)); //Iniciando o sprite que carregará o fundo;

    Character character[6]; //Inicializando as variáveis de todos os personagens do jogo.
    Boat boat (false, 0, SCALEBOAT, sf::Vector2f(BOATXRIGHT, BOATY));

    character[0].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1200, 180));
    character[1].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1430, 190));
    character[2].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1330, 450));
    character[3].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 200));
    character[4].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1590, 450));
    character[5].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 700));
    

    if (!background.setTexture("bin/backgame.png") || !character[0].setTexture("bin/padre1.png") || !character[1].setTexture("bin/padre1.png") || !character[2].setTexture("bin/padre1.png") || !character[3].setTexture("bin/canibal1.png") || !character[4].setTexture("bin/canibal1.png") || !character[5].setTexture("bin/canibal1.png") || !boat.setTexture("bin/barco.png")) //Fazendo a verificação do fundo do jogo, vendo se é possível abri-lo sem problemas;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    while (window.isOpen()) //Enquanto a janela está aberta;
    {
        while (window.pollEvent(event) && boat.moving != true)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();

                    return 0;

                break;
            
                case sf::Event::KeyPressed: //Essa verificação é sobre o teclado, caso o jogador aperte o ESC, para voltar para o menu;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //ESCAPE == ESC
                       return 0;

                break;

                case sf::Event::MouseButtonPressed: //Vendo se o jogador apertou em alguma coisa;
                    if (boat.isHovering(mouse.getPosition(window))) {
                        boat.moveBoat(); //Chama a função de mover o barco, caso ele clique no barco;
                    }
                break;
            }
        }

        if (boat.moving == true && boat.sprite.getPosition().x != boat.xfinal) //Fazendo a verificação se o barco está andando, e move ele dentro do if;
            boat.sprite.move(boat.speed, 0);
        else
            boat.moving = false; //Caso o barco parou de andar, coloca que ele não está em movimento, para poupar processamento;      
        

        window.clear(sf::Color::Black); //Limpando as representações antigas que estavam dispostas na janela;

        window.draw(background.sprite); //Colocando o fundo do jogo;

        window.draw(boat.sprite);

        window.draw(character[0].sprite);
        window.draw(character[1].sprite);
        window.draw(character[2].sprite);
        window.draw(character[3].sprite);
        window.draw(character[4].sprite);
        window.draw(character[5].sprite);

        window.display(); //Mostrando quais foram as alterações no fundo;
    }




    return 0;
}