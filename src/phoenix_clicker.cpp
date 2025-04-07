/*
** EPITECH PROJECT, 2025
** phoenix_clicker
** File description:
** phoenix_clicker
*/
#include "../include/phoenix_clicker.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

const std::vector<DatiSpada> Gioco::DATI_SPADE = {
        {0, 0, "Nessuna"},
        {50, 1, "Legno"},
        {250, 3, "Pietra"},
        {1000, 10, "Diamante"},
        {5000, 30, "Netherite"},
        {25000, 100, "???"}
};


Gioco::Gioco() {
    _punto_sentiero = "setter/score.txt";
    _prossimo_punto_sentiero = "setter/next_score.txt";
    _temp_sentiero = "setter/temp.txt";
    _progresso_sentiero = "setter/upgrades.txt"; // Inizializza percorso save file
    _punto = 0;
    _temp = 0;
    _prossimo_punto = 0;
    _moneda = 0;
    _click_potenza = 1;
    _punti_per_secondo = 0;
    _livello_spada = 0;
}

Gioco::~Gioco() {}

long Gioco::calcolaBonusSpada() const {
    if (_livello_spada > 0 && _livello_spada < DATI_SPADE.size()) {
        return DATI_SPADE[_livello_spada].bonus_click;
    }
    return 0;
}


void Gioco::bombardino_crocodilo() {
    if (_punto > 0) {
        long potenza_totale_click = _click_potenza + calcolaBonusSpada();
        _punto -= potenza_totale_click;
        if (_punto < 0) _punto = 0;
    }

    if (_punto <= 0) {
        std::ofstream punto_file(_punto_sentiero);
        if (!punto_file.is_open()) { return; }
        punto_file << 0;
        punto_file.close();

        std::ofstream next_punto_file(_prossimo_punto_sentiero);
        if (!next_punto_file.is_open()) { return; }
        std::ofstream temp_file(_temp_sentiero);
        if (!temp_file.is_open()) { next_punto_file.close(); return; }

        if (_temp == 0) {
            _prossimo_punto = 10;
        } else {
            _prossimo_punto = static_cast<long>(_temp * 1.5);
            if (_prossimo_punto <= _temp) {
                _prossimo_punto = _temp + 1;
            }
        }

        _punto = _prossimo_punto;
        _temp = _prossimo_punto;
        next_punto_file << _prossimo_punto;
        temp_file << _temp;

        next_punto_file.close();
        temp_file.close();

        std::ofstream punto_file_after_rebirth(_punto_sentiero);
        if (!punto_file_after_rebirth.is_open()) { return; }
        punto_file_after_rebirth << _punto;
        punto_file_after_rebirth.close();

    } else {
        std::ofstream punto_file(_punto_sentiero);
        if (!punto_file.is_open()) { return; }
        punto_file << _punto;
        punto_file.close();
    }
}

void Gioco::applicaPuntiPerSecondo() {
    if (_punti_per_secondo <= 0 || _punto <= 0) {
        return;
    }
    _moneda += _punti_per_secondo;
    _punto -= _punti_per_secondo;
    if (_punto < 0) _punto = 0;
}

void Gioco::salvaProgresso() {
    std::ofstream save_file(_progresso_sentiero);
    if (!save_file.is_open()) {
        std::cerr << "ERRORE: Impossibile aprire il file di salvataggio: " << _progresso_sentiero << std::endl;
        return;
    }
    save_file << _click_potenza << std::endl;
    save_file << _punti_per_secondo << std::endl;
    save_file << _livello_spada << std::endl;
    save_file << _moneda << std::endl; // Salva anche i soldi

    if (save_file.fail()) {
        std::cerr << "ERRORE: Scrittura fallita nel file di salvataggio: " << _progresso_sentiero << std::endl;
    } else {
        std::cout << "Progresso salvato in " << _progresso_sentiero << std::endl;
    }
    save_file.close();
}

int Gioco::tralalero_tralala() {
    bool score_files_ok = true;
    long default_start_score = 10;

    try {
        if (!std::filesystem::exists("setter")) {
            std::filesystem::create_directory("setter");
        }
    } catch (const std::filesystem::filesystem_error& e) {
    }

    std::ifstream punto_file(_punto_sentiero);
    if (!punto_file.is_open() || !(punto_file >> _punto)) {
        _punto = default_start_score; score_files_ok = false;
    }
    if(punto_file.is_open()) punto_file.close();

    std::ifstream prossimo_punto_file(_prossimo_punto_sentiero);
    if (!prossimo_punto_file.is_open() || !(prossimo_punto_file >> _prossimo_punto)) {
        _prossimo_punto = default_start_score; score_files_ok = false;
    }
    if(prossimo_punto_file.is_open()) prossimo_punto_file.close();

    std::ifstream temp_file(_temp_sentiero);
    if (!temp_file.is_open() || !(temp_file >> _temp)) {
        _temp = default_start_score; score_files_ok = false;
    }
    if(temp_file.is_open()) temp_file.close();

    if (_prossimo_punto <= 0) _prossimo_punto = default_start_score;
    if (_temp <= 0) _temp = _prossimo_punto;
    if (_punto <= 0) _punto = _prossimo_punto;

    if (!score_files_ok) {
        std::ofstream out_punto(_punto_sentiero); if(out_punto.is_open()) out_punto << _punto;
        std::ofstream out_prossimo(_prossimo_punto_sentiero); if(out_prossimo.is_open()) out_prossimo << _prossimo_punto;
        std::ofstream out_temp(_temp_sentiero); if(out_temp.is_open()) out_temp << _temp;
    }

    _click_potenza = 1;
    _punti_per_secondo = 0;
    _livello_spada = 0;
    _moneda = 0;

    std::ifstream load_file(_progresso_sentiero);
    if (load_file.is_open()) {
        long temp_click, temp_pps, temp_moneda;
        int temp_spada;

        if (load_file >> temp_click >> temp_pps >> temp_spada >> temp_moneda) {
            _click_potenza = temp_click;
            _punti_per_secondo = temp_pps;
            _livello_spada = temp_spada;
            _moneda = temp_moneda;
            std::cout << "Progresso caricato da " << _progresso_sentiero << std::endl;
        } else {
            std::cerr << "ATTENZIONE: Lettura fallita dal file di salvataggio: " << _progresso_sentiero << ". Uso valori di default." << std::endl;
        }
        load_file.close();
    } else {
        std::cout << "File di salvataggio " << _progresso_sentiero << " non trovato. Inizio nuova partita." << std::endl;
    }

    return 0;
}

void Gioco::resetGioco()
{
//    _punto = 10;
//    _temp = 10;
//    _prossimo_punto = 10;
//    _money = 0;
//    _click_potenza = 1;
//    _punti_per_secondo = 0;
//    _livello_spada = 0;
//    setLivelloSpada(0);
//    salvaProgresso();
}

int Gioco::getLivelloSpada() const {
    return _livello_spada;
}

void Gioco::setLivelloSpada(int livello) {
    _livello_spada = livello;
}

const DatiSpada& Gioco::getDatiSpada(int livello) {
    if (livello >= 0 && livello < DATI_SPADE.size()) {
        return DATI_SPADE[livello];
    }
    std::cerr << "Richiesto livello spada non valido: " << livello << std::endl;
    return DATI_SPADE[0];
}