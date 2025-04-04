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

void Game::setTemp(long score)
{
    _temp = score;
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

