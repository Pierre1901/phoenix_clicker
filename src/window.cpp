//
// Created by pierre on 4/4/25.
//

#include "../include/window.hpp"

Fenice::Fenice() :  _fenice(sf::VideoMode(1920, 1080), "Phoenix Clicker")
{
    _uovo_sentiero = "assets/egg.png";
    _bambino_sentiero = "assets/baby.png";
    _adulta_sentiero = "assets/adult.png";
    _font_sentiero = "assets/Fireflies.otf";
    tralalero_tralala();
    _bambino_fase = _temp / 3;
    _adulta_fase = _temp / 2;
}

Fenice::~Fenice()
{
    return;
}

void Fenice::aggiornaFenice()
{
    _bambino_fase = _temp / 3;
    _adulta_fase = _temp / 2;
    if (_punto >= (_temp - _bambino_fase)) {
        _posto.setTexture(&_fenice_uovo);
    }
    else if (_punto >= (_temp - _adulta_fase)) {
        _posto.setTexture(&_fenice_bambino);
    } else {
        _posto.setTexture(&_fenice_adulta);
    }
}

int Fenice::bobalino_cattolino()
{
    if (!_fenice_uovo.loadFromFile(_uovo_sentiero))
        return 84;
    if (!_fenice_bambino.loadFromFile(_bambino_sentiero))
        return 84;
    if (!_fenice_adulta.loadFromFile(_adulta_sentiero))
        return 84;
    if (!_font.loadFromFile(_font_sentiero))
        return 84;
    _posto.setSize(sf::Vector2f(500, 500));
    _posto.setPosition(670, 250);
    if (_punto >= (_temp - _bambino_fase)) {
        _posto.setTexture(&_fenice_uovo);
    }
    else if (_punto >= (_temp - _adulta_fase)) {
        _posto.setTexture(&_fenice_bambino);
    } else {
        _posto.setTexture(&_fenice_adulta);
    }

    _attuale_punto.setFont(_font);
    _attuale_punto.setPosition(780, 10);
    _attuale_punto.setCharacterSize(100);
    _attuale_punto.setFillColor(sf::Color::Black);
    return 0;
}



void Fenice::correre()
{
    while (_fenice.isOpen()) {
        sf::Event event;
        while (_fenice.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _fenice.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_fenice);
                    if (_posto.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        bombardino_crocodilo();
                    }
                }
            }
        }
        std::string scoreStr = "Score: " + std::to_string(_punto);
        _attuale_punto.setString(scoreStr);
        aggiornaFenice();
        _fenice.clear(sf::Color::White);
        _fenice.draw(_posto);
        _fenice.draw(_attuale_punto);
        _fenice.display();
    }
}
