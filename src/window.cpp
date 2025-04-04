//
// Created by pierre on 4/4/25.
//

#include "../include/window.hpp"

Window::Window() :  _window(sf::VideoMode(1920, 1080), "Phoenix Clicker")
{
    _egg_path = "assets/egg.png";
    _baby_path = "assets/baby.png";
    _adult_path = "assets/adult.png";
    _font_path = "assets/Fireflies.otf";
    initScore();
    _baby_phase = _temp / 3;
    _adult_phase = _temp / 2;
}

Window::~Window()
{
    return;
}

void Window::updatePhoenix()
{
    _baby_phase = _temp / 3;
    _adult_phase = _temp / 2;
    if (_score >= (_temp - _baby_phase)) {
        _place.setTexture(&_phoenix_egg);
    }
    else if (_score >= (_temp - _adult_phase)) {
        _place.setTexture(&_phoenix_baby);
    } else {
        _place.setTexture(&_phoenix_adult);
    }
}

int Window::initWindow()
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
    if (_score >= (_temp - _baby_phase)) {
        _place.setTexture(&_phoenix_egg);
    }
    else if (_score >= (_temp - _adult_phase)) {
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



void Window::runGame()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                    if (_place.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        reduceScore();
                    }
                }
            }
        }
        std::string scoreStr = "Score: " + std::to_string(_score);
        _current_score.setString(scoreStr);
        updatePhoenix();
        _window.clear(sf::Color::White);
        _window.draw(_place);
        _window.draw(_current_score);
        _window.display();
    }
}
