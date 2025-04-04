//
// Created by pierre on 4/4/25.
//

#include "../include/window.hpp"

Fenice::Fenice() :  _fenice(sf::VideoMode(1920, 1080), "Phoenix Clicker")
{
    _egg_path = "assets/egg.png";
    _baby_path = "assets/baby.png";
    _adult_path = "assets/adult.png";
    _font_path = "assets/Fireflies.otf";
    tralalero_tralala();
    _baby_phase = _temp / 3;
    _adult_phase = _temp / 2;
}

Fenice::~Fenice()
{
    return;
}

void Fenice::aggiornaFenice()
{
    _baby_phase = _temp / 3;
    _adult_phase = _temp / 2;
    if (_punto >= (_temp - _baby_phase)) {
        _place.setTexture(&_phoenix_egg);
    }
    else if (_punto >= (_temp - _adult_phase)) {
        _place.setTexture(&_phoenix_baby);
    } else {
        _place.setTexture(&_phoenix_adult);
    }
}

int Fenice::bobalino_cattolino()
{
    if (!_phoenix_egg.loadFromFile(_egg_path))
        return 84;
    if (!_phoenix_baby.loadFromFile(_baby_path))
        return 84;
    if (!_phoenix_adult.loadFromFile(_adult_path))
        return 84;
    if (!_font.loadFromFile(_font_path))
        return 84;
    _place.setSize(sf::Vector2f(500, 500));
    _place.setPosition(670, 250);
    if (_punto >= (_temp - _baby_phase)) {
        _place.setTexture(&_phoenix_egg);
    }
    else if (_punto >= (_temp - _adult_phase)) {
        _place.setTexture(&_phoenix_baby);
    } else {
        _place.setTexture(&_phoenix_adult);
    }

    _current_score.setFont(_font);
    _current_score.setPosition(780, 10);
    _current_score.setCharacterSize(100);
    _current_score.setFillColor(sf::Color::Black);
    return 0;
}



void Fenice::runGame()
{
    while (_fenice.isOpen()) {
        sf::Event event;
        while (_fenice.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _fenice.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_fenice);
                    if (_place.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        bombardino_crocodilo();
                    }
                }
            }
        }
        std::string scoreStr = "Score: " + std::to_string(_punto);
        _current_score.setString(scoreStr);
        aggiornaFenice();
        _fenice.clear(sf::Color::White);
        _fenice.draw(_place);
        _fenice.draw(_current_score);
        _fenice.display();
    }
}
