//
// Created by pierre on 4/4/25.
//

#include "phoenix_clicker.hpp"
#include <SFML/Graphics.hpp>

#ifndef PHOENIX_CLICKER_WINDOW_HPP
#define PHOENIX_CLICKER_WINDOW_HPP

class Window : Game {
private:
    std::string _egg_path;
    std::string _baby_path;
    std::string _adult_path;
    std::string _font_path;
    sf::RenderWindow _window;
    sf::Texture _phoenix_egg;
    sf::Texture _phoenix_baby;
    sf::Texture _phoenix_adult;
    sf::RectangleShape _place;
    long _baby_phase;
    long _adult_phase;
    sf::Font _font;
    sf::Text _current_score;


public:
    Window();
    ~Window();
    int initWindow();
    void runGame();
    void updatePhoenix();


};

#endif //PHOENIX_CLICKER_WINDOW_HPP
