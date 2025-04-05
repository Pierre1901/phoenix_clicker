/*
** EPITECH PROJECT, 2025
** phoenix_clicker
** File description:
** window
*/
#ifndef PHOENIX_CLICKER_WINDOW_HPP
#define PHOENIX_CLICKER_WINDOW_HPP

#include "phoenix_clicker.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Fenice : public Gioco {
private:
    std::string _uovo_sentiero;
    std::string _bambino_sentiero;
    std::string _adulta_sentiero;
    std::string _font_sentiero;
    sf::RenderWindow _fenice;
    sf::Texture _fenice_uovo;
    sf::Texture _fenice_bambino;
    sf::Texture _fenice_adulta;
    sf::RectangleShape _posto;
    long _bambino_fase;
    long _adulta_fase;
    sf::Font _font;
    sf::Text _attuale_punto;
    sf::Text _money_text;

    bool _menu_aperto;
    sf::RectangleShape _menu_sfondo;

    sf::RectangleShape _bottone_click_upgrade;
    sf::Text _testo_click_upgrade;
    sf::RectangleShape _bottone_pps_upgrade;
    sf::Text _testo_pps_upgrade;

    std::vector<sf::Texture> _tex_spade;
    std::vector<sf::Sprite> _sprite_spade;
    std::vector<sf::RectangleShape> _bottoni_spade;
    std::vector<sf::Text> _testi_spade;
    std::vector<std::string> _nomi_file_spade;
    sf::SoundBuffer _bufferClickPosto;
    sf::Sound _suonoClickPosto;
    sf::Texture _textureCoin;
    std::vector<sf::Sprite> _flyingCoins;
    sf::RectangleShape _moneda;

    static const long COSTO_CLICK_UPGRADE = 50;

    sf::Clock _orologio_pps;

    bool _sta_animando_click;
    sf::Clock _orologio_animazione_click;
    sf::Vector2f _scala_originale_posto;
    static const float DURATA_ANIMAZIONE_CLICK;

    void setupMenu();
    void gestisciClickMenu(int mouseX, int mouseY);
    void aggiornaTestoBottoni();

public:
    Fenice();
    ~Fenice();
    int bobalino_cattolino();
    void correre();
    void aggiornaFenice();
};

#endif //PHOENIX_CLICKER_WINDOW_HPP