//
// Created by pierre on 4/4/25.
//

#include "../include/phoenix_clicker.hpp"

Gioco::Gioco()
{
    _punto_sentiero = "setter/score.txt";
    _prossimo_punto_sentiero = "setter/next_score.txt";
    _temp_sentiero = "setter/temp.txt";
    _punto = 0;
    _temp = 0;
    _prossimo_punto = 0;
}

Gioco::~Gioco()
{

}

void Gioco::bombardino_crocodilo()
{
    _punto = _punto - 1;
    std::ofstream punto_file(_punto_sentiero);
    if (_punto == 0){
        std::ofstream next_punto_file(_prossimo_punto_sentiero);
        std::ofstream temp_file(_temp_sentiero);
        _prossimo_punto = _temp * 1.5;
        _punto = _prossimo_punto;
        _temp = _prossimo_punto;
        next_punto_file << _prossimo_punto;
        temp_file << _temp;
    }
    punto_file << _punto;
}

int Gioco::tralalero_tralala()
{
    std::ifstream punto_file(_punto_sentiero);
    std::ifstream prossimo_punto_file(_prossimo_punto_sentiero);
    std::ifstream temp_file(_temp_sentiero);

    if (!punto_file || !prossimo_punto_file || !temp_file)
        return 84;
    if (!(punto_file >> _punto))
        return 84;
    if (!(prossimo_punto_file >> _prossimo_punto))
        return 84;
    if (!(temp_file >> _temp))
        return 84;
    return 0;
}

