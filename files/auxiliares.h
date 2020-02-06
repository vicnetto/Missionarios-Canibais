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

*/
class Phrase {
    public:
        sf::Text text;
        sf::Font font;

    public:
        Phrase(std::string phrase, int size, sf::Color color, sf::Vector2f position);
        bool setFont (std::string way);

};