/*
** EPITECH PROJECT, 2025
** phoenix_clicker
** File description:
** main.cpp
*/

#include "../include/phoenix_clicker.hpp"


int main(int argc, char **argv)
{
    Game game;

    if (game.initScore() == 84)
        return 84;
    game.reduceScore();
    return 0;
}