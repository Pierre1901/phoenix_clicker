/*
** EPITECH PROJECT, 2025
** phoenix_clicker
** File description:
** window
*/
#include "../include/window.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

const long Fenice::COSTO_CLICK_UPGRADE;
const float Fenice::DURATA_ANIMAZIONE_CLICK = 0.15f;

Fenice::Fenice() : _fenice(sf::VideoMode(1920, 1080), "Phoenix Clicker") {
    _uovo_sentiero = "assets/egg.png";
    _bambino_sentiero = "assets/baby.png";
    _adulta_sentiero = "assets/adult.png";
    _font_sentiero = "assets/Fireflies.otf";
    _menu_aperto = false;
    _sta_animando_click = false;

    _nomi_file_spade = {
            "assets/wood.png", "assets/stone.png", "assets/diamond.png",
            "assets/netherite.png", "assets/secret.png"
    };
    _tex_spade.resize(5);
    _sprite_spade.resize(5);
    _bottoni_spade.resize(5);
    _testi_spade.resize(5);


    if (tralalero_tralala() == 84) {
        std::cerr << "Error initializing game data from files!" << std::endl;
        _punto = 10; _prossimo_punto = 10; _temp = 10;
        _money = 0; _click_potenza = 1; _punti_per_secondo = 0;
        setLivelloSpada(0);
    }

    if (_temp <= 0) _temp = 10;
    _bambino_fase = _temp / 3;
    _adulta_fase = _temp / 2;

    _orologio_pps.restart();
    _scala_originale_posto = {1.0f, 1.0f};
}

Fenice::~Fenice() {}

void Fenice::aggiornaFenice() {
    if (_temp <= 0) _temp = 1;
    _bambino_fase = _temp / 3;
    _adulta_fase = _temp / 2;

    if (!_fenice_uovo.getNativeHandle()) { return; }
    if (!_fenice_bambino.getNativeHandle()) { return; }
    if (!_fenice_adulta.getNativeHandle()) { return; }

    _posto.setScale(_scala_originale_posto);
    _sta_animando_click = false;

    if (_punto >= (_temp - _bambino_fase)) {
        _posto.setTexture(&_fenice_uovo);
    } else if (_punto >= (_temp - _adulta_fase)) {
        _posto.setTexture(&_fenice_bambino);
    } else {
        _posto.setTexture(&_fenice_adulta);
    }
}

void Fenice::setupMenu() {
    float winWidth = 1920;
    float winHeight = 1080;
    float menuWidth = 800;
    float menuHeight = 650;
    float menuX = (winWidth - menuWidth) / 2;
    float menuY = (winHeight - menuHeight) / 2;

    _menu_sfondo.setSize(sf::Vector2f(menuWidth, menuHeight));
    _menu_sfondo.setPosition(menuX, menuY);
    _menu_sfondo.setFillColor(sf::Color(100, 100, 100, 220));
    _menu_sfondo.setOutlineColor(sf::Color::Black);
    _menu_sfondo.setOutlineThickness(2);

    float buttonWidthOrig = menuWidth * 0.4f;
    float buttonHeightOrig = 60;
    float buttonSpacingOrig = 20;
    float buttonXOrig1 = menuX + (menuWidth / 2 - buttonWidthOrig - buttonSpacingOrig / 2);
    float buttonXOrig2 = menuX + menuWidth / 2 + buttonSpacingOrig / 2;
    float buttonYOrig = menuY + 30;

    _bottone_click_upgrade.setSize(sf::Vector2f(buttonWidthOrig, buttonHeightOrig));
    _bottone_click_upgrade.setPosition(buttonXOrig1, buttonYOrig);
    _bottone_click_upgrade.setFillColor(sf::Color::Cyan);
    _testo_click_upgrade.setFont(_font);
    _testo_click_upgrade.setCharacterSize(20);
    _testo_click_upgrade.setFillColor(sf::Color::Black);

    _bottone_pps_upgrade.setSize(sf::Vector2f(buttonWidthOrig, buttonHeightOrig));
    _bottone_pps_upgrade.setPosition(buttonXOrig2, buttonYOrig);
    _bottone_pps_upgrade.setFillColor(sf::Color::Magenta);
    _testo_pps_upgrade.setFont(_font);
    _testo_pps_upgrade.setCharacterSize(20);
    _testo_pps_upgrade.setFillColor(sf::Color::Black);

    float buttonWidthSpada = menuWidth * 0.85f;
    float buttonHeightSpada = 75;
    float buttonSpacingSpada = 20;
    float buttonXSpada = menuX + (menuWidth - buttonWidthSpada) / 2;
    float startYSpada = buttonYOrig + buttonHeightOrig + 40;
    float spriteSize = buttonHeightSpada * 0.8f;
    float spriteOffsetX = 15;
    float textOffsetX = spriteOffsetX + spriteSize + 15;


    for (int i = 0; i < 5; ++i) {
        float currentY = startYSpada + i * (buttonHeightSpada + buttonSpacingSpada);

        _bottoni_spade[i].setSize(sf::Vector2f(buttonWidthSpada, buttonHeightSpada));
        _bottoni_spade[i].setPosition(buttonXSpada, currentY);
        _bottoni_spade[i].setFillColor(sf::Color(200, 200, 200));
        _bottoni_spade[i].setOutlineColor(sf::Color::Black);
        _bottoni_spade[i].setOutlineThickness(1);

        if (_tex_spade[i].getSize().x > 0) {
            _sprite_spade[i].setTexture(_tex_spade[i]);
            float scaleFactor = spriteSize / _tex_spade[i].getSize().y;
            _sprite_spade[i].setScale(scaleFactor, scaleFactor);
            _sprite_spade[i].setPosition(buttonXSpada + spriteOffsetX,
                                         currentY + (buttonHeightSpada - _sprite_spade[i].getGlobalBounds().height) / 2);
        }

        _testi_spade[i].setFont(_font);
        _testi_spade[i].setCharacterSize(22);
        _testi_spade[i].setFillColor(sf::Color::Black);
        _testi_spade[i].setPosition(buttonXSpada + textOffsetX, currentY + 5);
    }

    aggiornaTestoBottoni();
}

void Fenice::aggiornaTestoBottoni() {
    std::string clickText = "Potenza Click\nCosto: " + std::to_string(COSTO_CLICK_UPGRADE) + " (Attuale: " + std::to_string(_click_potenza) + ")";
    _testo_click_upgrade.setString(clickText);
    sf::FloatRect textRect = _testo_click_upgrade.getLocalBounds();
    _testo_click_upgrade.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    _testo_click_upgrade.setPosition(_bottone_click_upgrade.getPosition().x + _bottone_click_upgrade.getSize().x/2.0f,
                                     _bottone_click_upgrade.getPosition().y + _bottone_click_upgrade.getSize().y/2.0f);

    std::string ppsText = "Punti Passivi (+1/sec)\nCosto: " + std::to_string(100) + " Money (Attuale: " + std::to_string(_punti_per_secondo) + ")";
    _testo_pps_upgrade.setString(ppsText);
    textRect = _testo_pps_upgrade.getLocalBounds();
    _testo_pps_upgrade.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    _testo_pps_upgrade.setPosition(_bottone_pps_upgrade.getPosition().x + _bottone_pps_upgrade.getSize().x/2.0f,
                                   _bottone_pps_upgrade.getPosition().y + _bottone_pps_upgrade.getSize().y/2.0f);


    int livello_attuale_spada = getLivelloSpada();

    for (int i = 0; i < 5; ++i) {
        int livello_bottone = i + 1;
        const DatiSpada& dati = Gioco::getDatiSpada(livello_bottone);
        std::string testo_spada;
        sf::Color colore_bottone = sf::Color(200, 200, 200);
        sf::Color colore_testo = sf::Color::Black;

        if (livello_attuale_spada >= livello_bottone) {
            testo_spada = dati.nome + "\nAcquistata (Bonus: +" + std::to_string(dati.bonus_click) + ")";
            colore_bottone = sf::Color(100, 255, 100);
        } else if (livello_attuale_spada == livello_bottone - 1) {
            testo_spada = "Acquista " + dati.nome + "\nCosto: " + std::to_string(dati.costo) + " Money (Bonus: +" + std::to_string(dati.bonus_click) + ")";
            if (_money >= dati.costo) {
                colore_bottone = sf::Color(255, 255, 150);
            } else {
                colore_bottone = sf::Color(255, 150, 150);
                colore_testo = sf::Color(80, 80, 80);
            }
        } else {
            testo_spada = dati.nome + "\nBloccata (Acquista prima la spada precedente)";
            colore_bottone = sf::Color(150, 150, 150);
            colore_testo = sf::Color(80, 80, 80);
        }

        _testi_spade[i].setString(testo_spada);
        _testi_spade[i].setFillColor(colore_testo);
        _bottoni_spade[i].setFillColor(colore_bottone);
    }
}


void Fenice::gestisciClickMenu(int mouseX, int mouseY) {
    if (_bottone_click_upgrade.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
        if (_money >= COSTO_CLICK_UPGRADE) {
            _money -= COSTO_CLICK_UPGRADE;
            _click_potenza += 1;
            std::cout << "Upgrade Click Potenza acquistato! Nuova potenza base: " << _click_potenza << std::endl;
            aggiornaTestoBottoni();
        } else {
            std::cout << "Non abbastanza money per Potenza Click!" << std::endl;
        }
        return;
    }
    else if (_bottone_pps_upgrade.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
        long costo_pps = 100;
        if (_money >= costo_pps) {
            _money -= costo_pps;
            _punti_per_secondo += 1;
            std::cout << "Upgrade Punti Passivi acquistato! Punti/sec: " << _punti_per_secondo << std::endl;
            aggiornaTestoBottoni();
        } else {
            std::cout << "Non abbastanza money per Punti Passivi!" << std::endl;
        }
        return;
    }

    int livello_attuale_spada = getLivelloSpada();
    for (int i = 0; i < 5; ++i) {
        if (_bottoni_spade[i].getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
            int livello_da_acquistare = i + 1;
            if (livello_attuale_spada == livello_da_acquistare - 1) {
                const DatiSpada& dati = Gioco::getDatiSpada(livello_da_acquistare);
                if (_money >= dati.costo) {
                    _money -= dati.costo;
                    setLivelloSpada(livello_da_acquistare);
                    std::cout << "Acquistata Spada: " << dati.nome << std::endl;
                    aggiornaTestoBottoni();
                } else {
                    std::cout << "Non abbastanza money per: " << dati.nome << std::endl;
                }
            } else if (livello_attuale_spada >= livello_da_acquistare) {
                std::cout << "Spada " << Gioco::getDatiSpada(livello_da_acquistare).nome << " gia' acquistata." << std::endl;
            } else {
                std::cout << "Devi prima acquistare la spada precedente." << std::endl;
            }
            return;
        }
    }
}


int Fenice::bobalino_cattolino() {
    if (!_font.loadFromFile(_font_sentiero)) return 84;
    if (!_fenice_uovo.loadFromFile(_uovo_sentiero)) return 84;
    if (!_fenice_bambino.loadFromFile(_bambino_sentiero)) return 84;
    if (!_fenice_adulta.loadFromFile(_adulta_sentiero)) return 84;

    for (int i = 0; i < 5; ++i) {
        if (!_tex_spade[i].loadFromFile(_nomi_file_spade[i])) {
            std::cerr << "ERROR: Could not load sword texture: " << _nomi_file_spade[i] << std::endl;
            return 84;
        }
    }


    _posto.setSize(sf::Vector2f(500, 500));
    _posto.setOrigin(_posto.getSize().x / 2, _posto.getSize().y / 2);
    _posto.setPosition(920, 500);
    _posto.setScale(_scala_originale_posto);
    aggiornaFenice();

    _attuale_punto.setFont(_font);
    _attuale_punto.setPosition(780, 10);
    _attuale_punto.setCharacterSize(100);
    _attuale_punto.setFillColor(sf::Color::Black);
    _attuale_punto.setString("Score: " + std::to_string(_punto));

    _money_text.setFont(_font);
    _money_text.setPosition(10, 10);
    _money_text.setCharacterSize(50);
    _money_text.setFillColor(sf::Color::Black);
    _money_text.setString("Money: " + std::to_string(_money));

    setupMenu();

    std::cout << "bobalino_cattolino completed successfully." << std::endl;
    return 0;
}

void Fenice::correre() {
    while (_fenice.isOpen()) {
        sf::Event event;
        while (_fenice.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _fenice.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    _menu_aperto = !_menu_aperto;
                    if (_menu_aperto) aggiornaTestoBottoni();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_fenice);
                    if (_menu_aperto) {
                        gestisciClickMenu(mousePos.x, mousePos.y);
                    } else {
                        if (_posto.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            bombardino_crocodilo();
                            _money = _money + 1;
                            if (!_sta_animando_click) {
                                _sta_animando_click = true;
                                _scala_originale_posto = _posto.getScale();
                                _posto.setScale(_scala_originale_posto.x * 0.9f, _scala_originale_posto.y * 0.9f);
                                _orologio_animazione_click.restart();
                            }
                        }
                    }
                }
            }
        }

        if (_punti_per_secondo > 0) {
            if (_orologio_pps.getElapsedTime().asSeconds() >= 1.0f) {
                applicaPuntiPerSecondo();
                _orologio_pps.restart();
            }
        }

        if (_sta_animando_click) {
            if (_orologio_animazione_click.getElapsedTime().asSeconds() >= DURATA_ANIMAZIONE_CLICK) {
                _posto.setScale(_scala_originale_posto);
                _sta_animando_click = false;
            }
        }

        std::string scoreStr = "Score: " + std::to_string(_punto);
        _attuale_punto.setString(scoreStr);
        std::string moneyStr = "Money: " + std::to_string(_money);
        _money_text.setString(moneyStr);

        if (!_sta_animando_click) {
            aggiornaFenice();
        }

        _fenice.clear(sf::Color::White);
        _fenice.draw(_posto);
        _fenice.draw(_attuale_punto);
        _fenice.draw(_money_text);

        if (_menu_aperto) {
            _fenice.draw(_menu_sfondo);
            _fenice.draw(_bottone_click_upgrade);
            _fenice.draw(_testo_click_upgrade);
            _fenice.draw(_bottone_pps_upgrade);
            _fenice.draw(_testo_pps_upgrade);
            for(int i=0; i<5; ++i) {
                _fenice.draw(_bottoni_spade[i]);
                _fenice.draw(_sprite_spade[i]);
                _fenice.draw(_testi_spade[i]);
            }
        }

        _fenice.display();
    }
}