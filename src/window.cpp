//
// Created by pierre on 4/4/25.
//

#include "../include/window.hpp"

Window::Window() :  _window(sf::VideoMode(1920, 1080), "Phoenix Clicker")
{
    _egg_path = "assets/egg.png";
    _baby_path = "assets/baby.png";
    _adult_path = "assets/adult.png";
    initScore();
    _baby_phase = _temp / 3;
    _adult_phase = _temp / 2;
}

Window::~Window()
{
    return;
}

int Window::initWindow()
{
    if (!_phoenix_egg.loadFromFile(_egg_path))
        return 84;
    if (!_phoenix_baby.loadFromFile(_baby_path))
        return 84;
    if (!_phoenix_adult.loadFromFile(_adult_path))
        return 84;
    _place.setSize(sf::Vector2f(200, 200));
    _place.setPosition(100, 100);
    if (_score >= (_temp - _baby_phase)) {
        _place.setTexture(&_phoenix_egg);
    }
    else if (_score >= (_temp - _adult_phase)) {
        _place.setTexture(&_phoenix_baby);
    } else {
        _place.setTexture(&_phoenix_adult);
    }
    return 0;
}


void Window::runGame()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear(sf::Color::White);
        _window.draw(_place);
        _window.display();
    }
}
