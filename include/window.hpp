//
// Created by pierre on 4/4/25.
//

#include "phoenix_clicker.hpp"
#include <SFML/Graphics.hpp>

#ifndef PHOENIX_CLICKER_WINDOW_HPP
#define PHOENIX_CLICKER_WINDOW_HPP

class Fenice : Gioco {
private:
    std::string _uovo_sentiero;
    std::string _bambino_sentiero;
    std::string _adulta_sentiero;
    std::string _font_sentiero;
    sf::RenderWindow _fenice;
    sf::Texture _fenice_uovo;
    sf::Texture _fenice_bambino;
    sf::Texture _fenice_adulta;
    sf::RectangleShape _posto;
    long _bambino_fase;
    long _adulta_fase;
    sf::Font _font;
    sf::Text _attuale_punto;


public:
    Fenice();
    ~Fenice();
    int bobalino_cattolino();
    void correre();
    void aggiornaFenice();


};

#endif //PHOENIX_CLICKER_WINDOW_HPP
