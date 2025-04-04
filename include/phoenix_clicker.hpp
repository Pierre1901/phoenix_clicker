//
// Created by pierre on 4/4/25.
//

#ifndef PHOENIX_CLICKER_PHOENIX_CLICKER_HPP
#define PHOENIX_CLICKER_PHOENIX_CLICKER_HPP

#include "iostream"
#include "ostream"
#include "string"
#include <fstream>


class Gioco {
protected:
    long _punto;
    long _prossimo_punto;
    long _temp;
    std::string _punto_sentiero;
    std::string _prossimo_punto_sentiero;
    std::string _temp_sentiero;


public:
    Gioco();
    ~Gioco();
    int tralalero_tralala();
    void bombardino_crocodilo();
};



#endif //PHOENIX_CLICKER_PHOENIX_CLICKER_HPP
