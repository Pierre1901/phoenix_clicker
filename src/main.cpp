/*
** EPITECH PROJECT, 2025
** phoenix_clicker
** File description:
** main.cpp
*/

#include "../include/phoenix_clicker.hpp"
#include "../include/window.hpp"


int main(int argc, char **argv)
{
    Gioco gioco;

    if (gioco.tralalero_tralala() == 84)
        return 84;
    Fenice fenice;
    if (fenice.bobalino_cattolino() == 84)
        return 84;
    fenice.setupMenuParametros();
    fenice.correre(gioco);
    return 0;
}