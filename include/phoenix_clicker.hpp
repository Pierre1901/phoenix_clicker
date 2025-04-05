#ifndef PHOENIX_CLICKER_PHOENIX_CLICKER_HPP
#define PHOENIX_CLICKER_PHOENIX_CLICKER_HPP

#include "iostream"
#include "ostream"
#include "string"
#include <fstream>
#include <vector>

struct DatiSpada {
    long costo;
    long bonus_click;
    std::string nome;
};


class Gioco {
protected:
    long _punto;
    long _prossimo_punto;
    long _temp;
    long _money;
    std::string _punto_sentiero;
    std::string _prossimo_punto_sentiero;
    std::string _temp_sentiero;
    std::string _progresso_sentiero; // Nuovo: Percorso file salvataggio

    long _click_potenza;
    long _punti_per_secondo;
    int _livello_spada;

    long calcolaBonusSpada() const;

    static const std::vector<DatiSpada> DATI_SPADE;

public:
    Gioco();
    ~Gioco();
    int tralalero_tralala();
    void salvaProgresso();
    void bombardino_crocodilo();
    void applicaPuntiPerSecondo();
    int getLivelloSpada() const;
    void setLivelloSpada(int livello);
    static const DatiSpada& getDatiSpada(int livello);
};

#endif //PHOENIX_CLICKER_PHOENIX_CLICKER_HPP