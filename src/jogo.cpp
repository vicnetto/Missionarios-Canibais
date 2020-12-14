#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <bits/stdc++.h>

#include "jogo.h"
#include "phrase.h"
#include "sprites.h"
#include "boat.h"
#include "character.h"
#include "gamedata.h"

#define SLOWNESS 10000 //Lentidão da tela, a velocidade em que ela muda cada frame;
#define DISTANCE 1.7 //A distância que cada frame percorre (não são dados reais);
#define ENDX 3840 //Em qual lugar é finalizado a textura;
#define ENDY 0 //Em qual lugar é iniciado e finalizado a textura no eixo Y (constante);
#define XSTEXTURE 1920  //Qual o tamanho do eixo X de um frame completo na textura;
#define YSTEXTURE 1080 //O tamanho no eixo Y de um frame inteiro;

#define SCALEPRIEST sf::Vector2f(0.32, 0.32) //Tamanho da sprite do padre;
#define SCALECANNIBAL sf::Vector2f(0.385, 0.385) //Tamanho da sprite do canibal;
#define SCALEBOAT sf::Vector2f(0.5, 0.5) //Tamanho da sprite do barco; 
#define LEFTSIDE 0 //O lado esquerdo vale como 0;
#define BOATLEFTSIDE 1 //O barco no lado esqurdo vale 1;
#define BOATRIGHTSIDE 2 //O barco no lado direito vale 2;
#define RIGHTSIDE 3 //Quando está no lado direito, vale 3;
#define BOATXRIGHT 1032 //A posição X inicial do barco é essa, no lado direito;
#define BOATY 900 //Essa é a posição fixa do Y, não varia em nenhum momento;
#define NUMBEROFCHARS 6 //Era 6;

#define CONTINUE 0
#define LOSE 1
#define WIN 2

#define TIMEFORANIMATION 1.5
#define XFINALATTEMPTS 700
#define XFINALMOVES 705
#define XFINALTIME 704.5
#define XFINALTOTALMOVES 704

sf::Color darkBlue (0,72,186); //Colocando uma cor mais harmoniosa no jogo;
sf::Color brown (150, 75, 0); //Setando a cor para utilizala no men;

//--------------------------------------------------------- JOGO --------------------------------------------------------------------------

/*

int Jogo::mainMenu ()

    O motivo principal é o mesmo do nome, serve para fazer o menu de uma forma mais organizada, tendo todos os parâmentros
dentro da classe Jogo.

@param
@return int

*/
int Jogo::mainMenu () {
    sf::Clock clock; //Relógio auxiliador da movimentação da tela no menu inicial;
    sf::Clock secondClock;

    int currentX = 0; //Posição atual da textura, no eixo X;
    bool loading = true;
    bool lightning = true;

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
    Sprites petecoGrande (sf::Vector2f(0.8, 0.8), sf::Vector2f(WIDTH * 0.35, HEIGHT * 0.4));

    sf::SoundBuffer som;

    if (!som.loadFromFile("bin/bigthu.ogg"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the sound." << std::endl;

        return 1;
    }

    sf::Sound raio;
    raio.setBuffer(som);
    raio.setVolume(6.0f);


    //Aqui é a verificação se existem os arquivos das fontes;
    if (!miss.setFont("bin/FFF_Tusj.ttf") || !jogar.setFont("bin/afanan.ttf") || !sair.setFont("bin/afanan.ttf") || !comojogar.setFont("bin/afanan.ttf") || !e.setFont("bin/Vegan.ttf") || !cani.setFont("bin/Nightmare.ttf") || !victornetto.setFont("bin/Amilya.ttf"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    //Verifica se o arquivo da textura está disponível, caso contrário reporta o erro para o main, e para o console;
    if (!fundo.setTexture("bin/Background.png") || !biblia.setTexture("bin/biblia.png") || !faca.setTexture("bin/faca.png") || !peteco.setTexture("bin/LogoPETECO.png") || !petecoGrande.setTexture("bin/LogoPETECO.png")) //Carregando o fundo do menu;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    while (window.isOpen()) {//Começando o loop principal do menu;

        //if (secondClock.getElapsedTime().asSeconds() > 5.4)
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

                    if (jogar.isHovering(mouse.getPosition(window))) //Essa verificação é infelizmente necessária para não apresentar um bug na hora de voltar;
                        jogar.text.setFillColor(sf::Color::Blue);
                    else
                        jogar.text.setFillColor(sf::Color::Yellow);
                }

                if (sair.isHovering(mouse.getPosition(window))) //Essa opção é chamada na saida, caso o botão seja apertado em cima da área de sair;
                    return 0;

                break;

            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                
                window.setView(sf::View(visibleArea));
            break;
            }
        }

        if (secondClock.getElapsedTime().asSeconds() < 5) {
            window.draw(fundo.sprite);

            window.draw(petecoGrande.sprite);
        } else if (secondClock.getElapsedTime().asSeconds() > 5 && secondClock.getElapsedTime().asSeconds() < 6.05) {
            window.draw(fundo.sprite);

            if (secondClock.getElapsedTime().asSeconds() > 5.675) {
                if (lightning == true) {
                    raio.play();

                    lightning = false;
                }
            }
        } else {
            window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

            window.draw(fundo.sprite); //Nessa linha e abaixo, printando os sprites;
            window.draw(biblia.sprite);
            window.draw(faca.sprite);

            window.draw(miss.text); //Escreve a palavra depois de ter limpado;
            window.draw(e.text);
            window.draw(cani.text);
            window.draw(victornetto.text);
            window.draw(peteco.sprite);

            window.draw(jogar.text); //Nessa linha e abaixo, colocando as opções do menu;
            window.draw(sair.text);
            window.draw(comojogar.text);
        }

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

bool Jogo::startScreen()

    Essa função tem como objetivo montar uma tela inicial, para preparar o jogador do início do jogo.

@param
@return


*/

bool Jogo::startScreen()
{
    sf::Mouse mouse; //Instanciando o mouse para pegar seus movimentos;

    sf::Image white; //Colocando uma classe sf::Imagem, que serve para fazer uma mascara transparente, e deixar o fundo visualizavel;
    white.create(WIDTH, HEIGHT, sf::Color::White);
    white.createMaskFromColor(sf::Color::White, 100); //Aqui está colocando a mascara, deixando a imagem transparente;

    Sprites startBackground (sf::Vector2f(1,1), sf::Vector2f(0,0)); //Instanciando o fundo do segundo menu, que basicamente se trata de um fundo cheio de estrelas;
    Sprites whiteWindow (sf::Vector2f(0.5, 0.5), sf::Vector2f(WIDTH * 0.25, HEIGHT * 0.25)); //Dessa vez instanciando a sprite que será colocada a sf::Image transparente;

    Phrase start ("Prontx para iniciar o jogo?", 70, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.31, WIDTH * 0.17)); //Colocando a frase de pergunta, para o jogador;
    Phrase sim ("SIM, SIMBORA!", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.41, WIDTH * 0.25)); //Colocando a opção de iniciar o jogo;
    Phrase aindanao ("DAQUI A POUCO, TALVEZ :(", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.342, WIDTH * 0.34)); //Ou a opção de voltar ao menu;

    whiteWindow.texture.loadFromImage(white); //Nessa parte, estamos colocando a textura futura da sprite, e nesse caso colocamos a imagem transparente;
    whiteWindow.sprite.setTexture(whiteWindow.texture); //Aplicando a textura transparente no sprite;

    //Trazendo alguns dados dos arquivos, carregando fontes..;
    if (!startBackground.setTexture("bin/espaco.png") || !start.setFont("bin/afanan.ttf") || !sim.setFont("bin/Pixel.ttf") || !aindanao.setFont("bin/Pixel.ttf"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //Caso fechar a janela;
                window.close();

                return 0; //Retorna "sucesso";

                break;

            case sf::Event::MouseMoved:
                if (sim.isHovering(mouse.getPosition(window))) //Do mesmo jeito feito no menu, caso ele coloque o mouse em cima, irá mudar de cor;
                    sim.text.setFillColor(darkBlue); //Azul para opção;
                else
                    sim.text.setFillColor(sf::Color::White); //Branco para mouse fora;

                if (aindanao.isHovering(mouse.getPosition(window))) //No mesmo caso do sim, agora trata-se da opção de voltar ao menu;
                    aindanao.text.setFillColor(darkBlue);
                else
                    aindanao.text.setFillColor(sf::Color::White);

                break;

            case sf::Event::MouseButtonPressed:
                if (sim.isHovering(mouse.getPosition(window))) //Caso o jogador clique em cima do sim, retorna true para a função start(), onde o valor será tratado;
                    return true; //Retornando true;

                if (aindanao.isHovering(mouse.getPosition(window))) //Caso contrário o jogador será recolocado no menu;
                    return false; //Retornando false;

                break;
            }
        }

        window.clear(sf::Color::Black);

        //Printando as sprites e textos que foram anunciadas acima;
        window.draw(startBackground.sprite); 
        window.draw(whiteWindow.sprite);
        window.draw(start.text);
        window.draw(sim.text);
        window.draw(aindanao.text);

        window.display(); //Mostrando todas as mudanças que foram feitas;
    }
}

/*

int Jogo::start()

    Essa função é a principal do jogo, pelo menos onde é chamado e organizado todas as verificações do jogo.

@param
@return int

*/
int Jogo::start () {
    bool choose; //Escolha do jogador na 2a tela do menu;x

    choose = startScreen(); //Atribuindo a variavel escolha qual foi a escolha dele no 2o menu;

    if (!choose) { //Caso ele tenha escolhido sair, o jogo não começa;
        return 0;
    }

    int xinitial, xfinal, side;
    bool isCharAllFalse; //Essa variável é para saber se o mouse não está em cima de nenhum personagem, para auxiliar no barco;
    int winOrLose; //Verificação utilizada para ver se o jogador perdeu, para evitar algumas chamadas extras na função;

    GameData gameData;

    std::stack<sf::Vector2f> leftSpaces;
    std::stack<sf::Vector2f> rightSpaces;
    std::stack<sf::Vector2f> boatSpaces;

    gameData.initializeStacks(leftSpaces, boatSpaces);

    sf::Mouse mouse; //Variável para pegar os movimentos do mouse;

    Phrase tempo ("Tempo (seg): ", 50, darkBlue, sf::Vector2f(WIDTH * 0.7, HEIGHT * 0.01));
    Phrase time ("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.83, HEIGHT * 0.01)); //Instânciando um objeto de tempo, onde será atualizado sempre que mudar os segundos;

    Phrase movimentos("Movimentos: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.01));
    Phrase movements ("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.58, HEIGHT * 0.01)); //Esses dois movimentos são a quantidade de movimentos que o jogador realizou;

    Phrase movimentosTotais("Total de Mov.: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.08));
    Phrase totalMovements("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.60, HEIGHT * 0.08));

    Phrase tentativas("Tentativas: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.20, HEIGHT * 0.01));
    Phrase attempts("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.33, HEIGHT * 0.01)); //Aqui são as tentativas, cada vez que o jogador perde soma-se 1 na quantidade;


    //GameData gameData; //Alocando espaço para a classe onde os dados serão armazenados no jogo;

    Sprites background (sf::Vector2f(1, 1), sf::Vector2f(0,0)); //Iniciando o sprite que carregará o fundo;

    Character character[NUMBEROFCHARS]; //Inicializando as variáveis de todos os personagens do jogo.
    Boat boat (false, 0, SCALEBOAT, sf::Vector2f(BOATXRIGHT, BOATY));

    character[0].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1200, 180));
    character[1].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1430, 170));
    character[2].setCharacter(true, RIGHTSIDE, SCALEPRIEST, sf::Vector2f(1420, 450));
    character[3].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 160));
    character[4].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1640, 450));
    character[5].setCharacter(false, RIGHTSIDE, SCALECANNIBAL, sf::Vector2f(1650, 750));

    sf::Image whiteOption; //Colocando uma classe sf::Imagem, que serve para fazer uma mascara transparente, e deixar o fundo visualizavel;
    whiteOption.create(WIDTH, HEIGHT, sf::Color::White);
    whiteOption.createMaskFromColor(sf::Color::White, 100); //Aqui está colocando a mascara, deixando a imagem transparente;

    Sprites whiteWindowOption (sf::Vector2f(0.3, 0.15), sf::Vector2f(WIDTH * 0.34, HEIGHT * 0.4)); //Dessa vez instanciando a sprite que será colocada a sf::Image transparente;

    whiteWindowOption.texture.loadFromImage(whiteOption); //Nessa parte, estamos colocando a textura futura da sprite, e nesse caso colocamos a imagem transparente;
    whiteWindowOption.sprite.setTexture(whiteWindowOption.texture); //Aplicando a textura transparente no sprite;

    //Inicializando as texturas dos textos que agora foram inseridos no jogo, para mostrar o desempenho do jogador;
    if (!time.setFont("bin/afanan.ttf") || !tempo.setFont("bin/afanan.ttf") || !movimentos.setFont("bin/afanan.ttf") || !movements.setFont("bin/afanan.ttf") || !tentativas.setFont("bin/afanan.ttf") || !attempts.setFont("bin/afanan.ttf") || !movimentosTotais.setFont("bin/afanan.ttf") ||!totalMovements.setFont("bin/afanan.ttf")) 
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }
    
    //Verificando se os arquvios estão disponíveis, e se estão abrindo sem problemas;
    if (!background.setTexture("bin/backgame.png") || !character[0].setTexture("bin/padre1.png") || !character[1].setTexture("bin/padre1.png") || !character[2].setTexture("bin/padre1.png") || !character[3].setTexture("bin/canibal1.png") || !character[4].setTexture("bin/canibal1.png") || !character[5].setTexture("bin/canibal1.png") || !boat.setTexture("bin/barco.png")) //Fazendo a verificação do fundo do jogo, vendo se é possível abri-lo sem problemas;
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }
    
    //Aqui estamos carregando as texturas que deixam o jogador brilhando, na hora de passar o mouse por cima dele.
    if (!character[0].setBrightTexture("bin/padre2.png") || !character[1].setBrightTexture("bin/padre2.png") || !character[2].setBrightTexture("bin/padre2.png") || !character[3].setBrightTexture("bin/canibal2.png") || !character[4].setBrightTexture("bin/canibal2.png") || !character[5].setBrightTexture("bin/canibal2.png") || !boat.setBrightTexture("bin/barco2.png"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return 1;
    }

    gameData.gameTime.restart(); //Restartando o relógio por causa do 2o menu;

    while (window.isOpen()) //Enquanto a janela está aberta;
    {
        while (window.pollEvent(event) && boat.moving != true)
        {
            switch (event.type)
            {
                case sf::Event::MouseMoved: 
                    isCharAllFalse = true;

                    for (int i = 0; i < NUMBEROFCHARS; i++) { //Esse laço verifica se o mouse está em cima de algum jogador, e logo em seguida muda as variáveis para trabalhar mais abaixo;
                        if (character[i].isHovering(mouse.getPosition(window))) {
                            character[i].bright = true;

                            isCharAllFalse = false;
                        } else {
                            character[i].bright = false;
                        }
                    }

                    if (boat.isHovering(mouse.getPosition(window)) && isCharAllFalse == true) //Aqui verifica se o mouse está em cima do barco ou não, e caso esteja coloca o brilho como true, ou false, caso seja o caso;
                        boat.bright = true;
                    else
                        boat.bright = false;

                break;

                case sf::Event::Closed: //Caso fechar a janela;
                    window.close();

                    return 0;

                break;
            
                case sf::Event::KeyPressed: //Essa verificação é sobre o teclado, caso o jogador aperte o ESC, para voltar para o menu;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {//ESCAPE == ESC
                        return 0;
                    }

                break;

                case sf::Event::MouseButtonPressed: //Vendo se o jogador apertou em alguma coisa;
                    if (boat.isHovering(mouse.getPosition(window)) && isCharAllFalse == true) {
                        if (boat.quantChar != 0){ //Caso o barco tenha apenas mais de 0 jogadores, pois vazio ele não pode andar;
                            gameData.moves += 1; //Soma um no movimento do barco;
                            gameData.totalMoves += 1; //Soma um nos movimentos totais do barco;

                            boat.moveBoat(); //Chama a função de mover o barco, caso ele clique no barco;
                        }
                    }

                    for (int i = 0; i < NUMBEROFCHARS; i++) { //Loop para percorrer todos os personagens;
                        if (character[i].isHovering(mouse.getPosition(window))) {
                            character[i].moveTo(leftSpaces, boatSpaces, rightSpaces, boat); //Caso o jogador aperte em cima do personagem, essa função move o personagem para o local correto;

                            character[i].bright = false; //Colocando a luz em volta nele de falso novamente;
                        }
                    }
                break;
            }
        }

        if (boat.moving == true && boat.sprite.getPosition().x != boat.xfinal) { //Fazendo a verificação se o barco está andando, e move ele dentro do if;

            boat.bright = false; //Colocando essa variável como falso, para deixar o barco na cor normal quando ele estiver se movendo;

            boat.sprite.move(boat.speed, 0); //Move a sprite do barco mas em uma velocidade bem pequena;
            boat.brightsprite.move(boat.speed, 0); //Move a sprite de opção do barco na mesma velocidade;
            
            for (int i = 0; i < NUMBEROFCHARS; i++){ //Esse laço serve para mover caso existam personagens em cima do barco;
                if (character[i].location == BOATRIGHTSIDE || character[i].location == BOATLEFTSIDE) { //Se ele estiver no barco, em qualquer lado, ele deve ir junto;
                    character[i].sprite.move(boat.speed, 0);
                }
            }
        } else if (boat.moving) { //TRATAMENTO PÓS MOVIMENTAÇÃO, LOGO APOS O BARCO PARAR;
            for (int i = 0; i < NUMBEROFCHARS; i++){ //Para finalizar o movimento do barco, quando ele estiver se movendo mas já chegou no seu objetivo final, devemos mudar a posição dos perso;
                if (character[i].location == BOATRIGHTSIDE) {  //Aqui verifica, caso ele veio do barco na direita, colocamos ele no barco do lado esquerdo;
                    character[i].location = BOATLEFTSIDE;

                    if (character[i].isPriest) //ATUALIZANDO OS DADOS DO GAMEDATA;
                        gameData.rightSidePriests -= 1; //Colocando menos um padre do lado direito, nesse caso ele acabou de ir para o lado esquerdo;
                    else
                        gameData.rightSideCanibals -= 1; //Diminunindo um canibal do lado direito, pois ele acabou de atravessar pelo barco;

                    character[i].brightsprite.setPosition(character[i].sprite.getPosition()); //Arruma a sprite de opção, que não precisa ficar acompanhando todo o tempo;
                }
                else if (character[i].location == BOATLEFTSIDE) { //E caso contrário, colocamos ele no lado direito, porque o barco acabou de andar;
                    character[i].location = BOATRIGHTSIDE;

                    if (character[i].isPriest)
                        gameData.rightSidePriests += 1; //Somando mais um padre caso ele venha do lado esquerdo, para o GameData;
                    else
                        gameData.rightSideCanibals += 1; //Colocando mais um canibal caso ele atravesse pelo barco para o lado direito;

                    character[i].brightsprite.setPosition(character[i].sprite.getPosition()); //Arruma a sprite de opção, que não precisa ficar acompanhando todo o tempo;
                }
            }
            
            boat.moveBoatFreePos(boatSpaces); //Movendo as posições do barco, para colocar elas no local certo agora que o barco se moveu;
            boat.moving = false; //Para finalizar, coloca-se o barco como parado, para não mover mais ele;
        }

        gameData.printStatistics(time, movements, attempts, totalMovements);

        window.clear(sf::Color::Black); //Limpando as representações antigas que estavam dispostas na janela;

        window.draw(background.sprite); //Colocando o fundo do jogo;
        
        //Fazendo os prints gerais do texto;
        window.draw(tempo.text);
        window.draw(time.text);
        window.draw(movimentos.text);
        window.draw(movements.text);
        window.draw(tentativas.text);
        window.draw(attempts.text);
        window.draw(movimentosTotais.text);
        window.draw(totalMovements.text);

        if (boat.bright == false) //Colocando a opção em cima do barco, para o jogador saber que é possível mover o barco;
            window.draw(boat.sprite);
        else
            window.draw(boat.brightsprite);

        //winOrLose = WIN;
        winOrLose = gameData.verifyWinConditions(character); //Verificando se o jogador venceu o ganhou, chamando a função verifyWinConditions();

        for (int i = 0; i < NUMBEROFCHARS; i++) { //Esse laço, bem importante, verifica se o mouse está em cima do personagem, e caso esteja desenha o personagem brilhante.
            if (character[i].bright == false) 
                window.draw(character[i].sprite);
            else
                window.draw(character[i].brightsprite);
        }

        if (winOrLose == WIN || winOrLose == LOSE) { //Agora sim comparando o resultado para ver vitória ou derrota;
            if (winOrLose == LOSE) { //Caso seja uma derrota
                window.draw(whiteWindowOption.sprite); //Desenha a janela transparente;

                gameData.gameOverScreen(window); //Faz a opção de jogar novamente;

                //Reseta algumas variáveis;
                gameData.moves = 0; //Reseta os movimentos do jogador, pois só deixa salvo os movimentos totais;
                gameData.currentMoves = 0; //Reseta os movimentos do momento, pelo mesmo motivo acima;
                gameData.numbAttempts += 1; //Numero de tentativas aumenta um, porque o jogador perdeu o jogo;

                //Essa função reseta toda a stack e coloca tudo novamente, para ajeitar o jogo para ajeitar para o jogador novamente;
                gameData.resetStacksAndReplace(leftSpaces, boatSpaces, rightSpaces, character, boat);
            } else { //É vitória caso o jogador chegue aqui;
                for (int i = 0; i < NUMBEROFCHARS; i++) {
                    if (character[i].location == BOATLEFTSIDE) {
                        character[i].sprite.setPosition(leftSpaces.top());

                        leftSpaces.pop();

                        boat.quantChar -= 1;
                    }
                }

                gameData.totalTime = gameData.gameTime.getElapsedTime().asSeconds();
                gameData.currentMoves = 0;
                gameData.currentNumbAttempts = 0;
                gameData.currentTotalMoves = 0;

                gameWinScreen(character, boat, background, whiteWindowOption, gameData);

                //AQUI VAI SALVAR OS DADOS NO ARQUIVO;

                return 0;
            }
        }

        window.display(); //Mostrando quais foram as alterações no fundo;
    }

    return 0;
}

/*

void Jogo::gameWinScreen()

    Essa função tem o objetivo de mostrar quando o jogador ganhou o jogo, pedir o seu nome e a sua idade
para futuramente tivermos dados suficientes para fazer uma pesquisa.

@param Character character [6] -> Passa todos os personagens como objeto, somente para poder printar eles normalmente.
@param Boat boat -> Para poder printar o barco, ele é passado como objeto.
@param Sprites background -> Evitando um carregamento desnecessário, passa-se também o fundo por objeto.
@param Sprites whiteWindowOption -> A janela de opções instanciada no start() para quando o jogador perde o jogo, é
utilizada novamente porém em um novo formato.
@param GameData gameData -> Para printar os dados do jogo, é passado como objeto o gameData.
@return

*/

void Jogo::gameWinScreen(Character character [6], Boat boat, Sprites background, Sprites whiteWindowOption, GameData gameData)
{
    bool printEverythingOneTime = true; //Essa variável serve para atualizar somente uma vez os dados do jogo, visando que eles não serão mudados durante a tela de derrota;
    bool moving = true; //Enquanto está tendo a animação dos dados do jogo isso permanece true;
    int movingVerficator = 0; //Verificador para ver se todos os parâmetros já chegaram no final, para evitar atualizações desnecessárias;

    sf::Mouse mouse; //Verificador do mouse, para ver onde está sua posição;

    whiteWindowOption.sprite.setScale(sf::Vector2f(0.35, 0.65)); //Aumentando o tamanho da janela e reposicionando ela abaixo para deixar ajeitada para o fim de jogo;
    whiteWindowOption.sprite.setPosition(sf::Vector2f((WIDTH / 2) - (whiteWindowOption.sprite.getGlobalBounds().width / 2), (HEIGHT / 2) - (whiteWindowOption.sprite.getGlobalBounds().height / 2)));

    Phrase tempo ("Tempo (seg): ", 50, darkBlue, sf::Vector2f(WIDTH * 0.7, HEIGHT * 0.01));
    Phrase time ("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.83, HEIGHT * 0.01)); //Instânciando um objeto de tempo, onde será atualizado sempre que mudar os segundos;

    Phrase movimentos("Movimentos: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.01));
    Phrase movements ("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.58, HEIGHT * 0.01)); //Esses dois movimentos são a quantidade de movimentos que o jogador realizou;

    Phrase movimentosTotais("Total de Mov.: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.08));
    Phrase totalMovements("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.60, HEIGHT * 0.08));

    Phrase tentativas("Tentativas: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.20, HEIGHT * 0.01));
    Phrase attempts("0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.33, HEIGHT * 0.01)); //Aqui são as tentativas, cada vez que o jogador perde soma-se 1 na quantidade;

    Phrase fimDeJogo("SUCESSO! FIM DE JOGO!", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.347, HEIGHT * 0.19)); //Instanciando o fim de jogo, frase que ficará escrita no pequeno menu;
    Phrase fimDeJogo1("SUCESSO! FIM DE JOGO!", 50, sf::Color::Blue, sf::Vector2f(WIDTH * 0.3451, HEIGHT * 0.19)); //Instanciando uma "sombra" para dar um efeito diferente na escrita;

    Phrase continuar("Continuar", 40, sf::Color::White, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.70)); //Unica opção disponível nesse menu de finalizar o jogo;

    //Inicializando as texturas dos textos que agora foram inseridos no jogo, para mostrar o desempenho do jogador;
    if (!time.setFont("bin/afanan.ttf") || !tempo.setFont("bin/afanan.ttf") || !movimentos.setFont("bin/afanan.ttf") || !movements.setFont("bin/afanan.ttf") || !tentativas.setFont("bin/afanan.ttf") || !attempts.setFont("bin/afanan.ttf") || !movimentosTotais.setFont("bin/afanan.ttf") ||!totalMovements.setFont("bin/afanan.ttf")) 
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return;
    }
    
    //Setando as fontes de fim de jogo e de continuar;
    if (!fimDeJogo.setFont("bin/Pixel.ttf") || !fimDeJogo1.setFont("bin/Pixel.ttf") || !continuar.setFont("bin/Vegan.ttf"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl;

        return;
    }

    while (window.isOpen()) //Começando o loop principal do menu;
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {

            case sf::Event::Closed: //Evento da janela fechada, no "X" da janela mesmo;
                window.close();

            break;

            case sf::Event::MouseMoved:
                if (continuar.isHovering(mouse.getPosition(window))) //Caso o mouse fique em cima do continuar;
                    continuar.text.setFillColor(sf::Color::Blue); //Muda a cor par azul;
                else
                    continuar.text.setFillColor(sf::Color::White); //Caso contrário, muda para branco;

            break;

            case sf::Event::MouseButtonPressed:
                if (continuar.isHovering(mouse.getPosition(window))) //Se apertar retorna sem valor, dizendo que ele terminou o jogo e está pronto para ir ao menu;
                    return;

            break;
            }
        }

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        window.draw(background.sprite); //Printa o fundo do jogo;

        if (printEverythingOneTime) { //Atualizando somente pela primeira vez;
            gameData.printStatistics(time, movements, attempts, totalMovements); //Atualizando os dados do gameData;

            printEverythingOneTime = false;
        }

        window.draw(boat.sprite); //Printando o barco;

        for (int i = 0; i < NUMBEROFCHARS; i++) //Printando todos os personagens;
            window.draw(character[i].sprite);

        window.draw(whiteWindowOption.sprite); //Colocando a janela branca transparente;

        //Printando as frases que serão apresentadas;
        window.draw(fimDeJogo1.text);
        window.draw(fimDeJogo.text);
        window.draw(continuar.text);

        if (moving == true) { //Caso esteja tendo a animação ainda, entra dentro dessas opções;
            if (tentativas.text.getPosition().x <= XFINALATTEMPTS) { //Enquanto a palavra tentativass não chegou ainda no final da sua animação;
                tentativas.text.move(sf::Vector2f(3.16, 3.3));
                attempts.text.move(sf::Vector2f(3.16, 3.3));
            } else
                movingVerficator += 1; //Quando chegar avisa a variável;
            
            if (movimentos.text.getPosition().x >= XFINALMOVES) { //Enquanto movimentos não chegou ainda também em seu objetivo final;
                movimentos.text.move(sf::Vector2f(-1.64, 4.25)); 
                movements.text.move(sf::Vector2f(-1.64, 4.25));
            } else
                movingVerficator += 1;

            if (tempo.text.getPosition().x >= XFINALTIME) { //Enquanto a palavra tempo não chegou no final da animação;
                tempo.text.move(sf::Vector2f(-6.42, 4.95));
                time.text.move(sf::Vector2f(-6.42, 4.95));
            } else
                movingVerficator += 1;

            if (movimentosTotais.text.getPosition().x >= XFINALTOTALMOVES) { //Enquanto o movimentos totais não chegou no final da animação ainda;
                movimentosTotais.text.move(sf::Vector2f(-1.62, 5.1));
                totalMovements.text.move(sf::Vector2f(-1.62, 5.1));
            } else
                movingVerficator += 1;
            

            if (movingVerficator > 4) //Caso ele já tenha passado por todos, limita de entrar nesse laço para evitar repetições;
                moving = false;
        }

        //Fazendo os prints gerais do texto;
        window.draw(tempo.text);
        window.draw(time.text);
        window.draw(movimentos.text);
        window.draw(movements.text);
        window.draw(tentativas.text);
        window.draw(attempts.text);
        window.draw(movimentosTotais.text);
        window.draw(totalMovements.text);

        window.display(); //Mostra novamente o que está sendo printado na tela;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------
