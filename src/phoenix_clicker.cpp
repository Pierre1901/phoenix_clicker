//
// Created by pierre on 4/4/25.
//

#include "../include/phoenix_clicker.hpp"

Game::Game()
{
    _score_path = "setter/score.txt";
    _next_score_path = "setter/next_score.txt";
    _temp_path = "setter/temp.txt";
    _score = 0;
    _temp = 0;
    _next_score = 0;
}

Game::~Game()
{

}

void Game::reduceScore()
{
    _score = _score - 1;
    std::ofstream score_file(_score_path);
    if (_score == 0){
        std::ofstream next_score_file(_next_score_path);
        std::ofstream temp_file(_temp_path);
        _next_score = _temp * 1.5;
        _score = _next_score;
        _temp = _next_score;
        next_score_file << _next_score;
        temp_file << _temp;
    }
    score_file << _score;
}

int Game::initScore()
{
    std::ifstream score_file(_score_path);
    std::ifstream next_score_file(_next_score_path);
    std::ifstream temp_file(_temp_path);

    if (!score_file || !next_score_file || !temp_file)
        return 84;
    if (!(score_file >> _score))
        return 84;
    if (!(next_score_file >> _next_score))
        return 84;
    if (!(temp_file >> _temp))
        return 84;
    return 0;
}

