//
// Created by pierre on 4/4/25.
//

#ifndef PHOENIX_CLICKER_PHOENIX_CLICKER_HPP
#define PHOENIX_CLICKER_PHOENIX_CLICKER_HPP

#include "iostream"
#include "ostream"
#include "string"
#include <fstream>


class Game {
private:
    long _score;
    long _next_score;
    long _temp;
    std::string _score_path;
    std::string _next_score_path;
    std::string _temp_path;


public:
    Game();
    ~Game();
    int initScore();
    void reduceScore();
};



#endif //PHOENIX_CLICKER_PHOENIX_CLICKER_HPP
