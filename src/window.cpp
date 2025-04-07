#include "../include/window.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <SFML/Audio.hpp>
#include <cmath> // Aggiunto per sicurezza

const long Fenice::COSTO_CLICK_UPGRADE;
const float Fenice::DURATA_ANIMAZIONE_CLICK = 0.15f;

Fenice::Fenice() : _fenice(sf::VideoMode(1920, 1080), "Phoenix Clicker") {
    _uovo_sentiero = "assets/egg.png";
    _bambino_sentiero = "assets/baby.png";
    _adulta_sentiero = "assets/adult.png";
    _font_sentiero = "assets/Fireflies.otf";
    _nomi_file_spade = {
            "assets/wood.png", "assets/stone.png", "assets/diamond.png",
            "assets/netherite.png", "assets/secret.png"
    };

    _menu_aperto = false;
    _sta_animando_click = false;
    _menu_parametros_abierto = false;
    _scala_originale_posto = {1.0f, 1.0f};

    _tex_spade.resize(5);
    _sprite_spade.resize(5);
    _bottoni_spade.resize(5);
    _testi_spade.resize(5);

    if (tralalero_tralala() == 84) {
        std::cerr << "ERRORE CRITICO durante il caricamento iniziale!" << std::endl;
        _punto = 10; _prossimo_punto = 10; _temp = 10;
        _money = 0; _click_potenza = 1; _punti_per_secondo = 0;
        setLivelloSpada(0);
        salvaProgresso();
    }

    if (_temp <= 0) _temp = 10;
    _bambino_fase = _temp / 3;
    _adulta_fase = _temp / 2;

    _orologio_pps.restart();
}

Fenice::~Fenice() {
    salvaProgresso();
}

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
    float menuWidth = 600;
    float menuHeight = 1080;
    float menuX = 0;
    float menuY = 0;

    _menu_sfondo.setSize(sf::Vector2f(menuWidth, menuHeight));
    _menu_sfondo.setPosition(menuX, menuY);
    sf::Color fondo_color(0, 0, 0, 77);
    _menu_sfondo.setFillColor(fondo_color);
    _menu_sfondo.setOutlineColor(sf::Color::Black);
    _menu_sfondo.setOutlineThickness(2);

    float buttonWidthOrig = menuWidth * 0.4f;
    float buttonHeightOrig = 60;
    float buttonSpacingOrig = 20;
    float buttonXOrig1 = menuX + (menuWidth / 2 - buttonWidthOrig - buttonSpacingOrig / 2);
    float buttonXOrig2 = menuX + menuWidth / 2 + buttonSpacingOrig / 2;
    float buttonYOrig = menuY + 250;

    _bottone_click_upgrade.setSize(sf::Vector2f(buttonWidthOrig, buttonHeightOrig));
    _bottone_click_upgrade.setPosition(buttonXOrig1, buttonYOrig);
    _bottone_click_upgrade.setFillColor(sf::Color::Cyan);
    _testo_click_upgrade.setFont(_font);
    _testo_click_upgrade.setCharacterSize(20);
    _testo_click_upgrade.setFillColor(sf::Color::Black);

    _shop_titulo_texto.setFont(_font);
    _shop_titulo_texto.setString("SHOP");
    _shop_titulo_texto.setCharacterSize(100);
    _shop_titulo_texto.setFillColor(sf::Color::White);

    sf::FloatRect textRect = _shop_titulo_texto.getLocalBounds();
    _shop_titulo_texto.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    _shop_titulo_texto.setPosition(_menu_sfondo.getPosition().x + _menu_sfondo.getSize().x / 2.0f, _menu_sfondo.getPosition().y + 100);

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
            aggiornaTestoBottoni();
        }
        return;
    }
    else if (_bottone_pps_upgrade.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
        long costo_pps = 100;
        if (_money >= costo_pps) {
            _money -= costo_pps;
            _punti_per_secondo += 1;
            aggiornaTestoBottoni();
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
                    aggiornaTestoBottoni();
                }
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
    if (!_bufferClickPosto.loadFromFile("assets/Toc.wav")) {
        std::cerr << "WARNING: Cannot load sound: assets/Toc.wav" << std::endl;
    } else {
        _suonoClickPosto.setBuffer(_bufferClickPosto);
    }
    if (!_textureCoin.loadFromFile("assets/coin.png")) {
        std::cerr << "WARNING: Cannot load texture: assets/coin.png" << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        if (!_tex_spade[i].loadFromFile(_nomi_file_spade[i])) {
            std::cerr << "ERROR: Could not load sword texture: " << _nomi_file_spade[i] << std::endl;
            return 84;
        }
    }

    if (!_textura_ajustes.loadFromFile("assets/setting.png")) {
        std::cerr << "WARNING: Impossible de charger la texture des ajustes : assets/setting.png" << std::endl;
        return 84;
    }
    _sprite_ajustes.setTexture(_textura_ajustes);

    float facteur_echelle = 0.15f;
    _sprite_ajustes.setScale(facteur_echelle, facteur_echelle);

    float posX = _fenice.getSize().x - _sprite_ajustes.getGlobalBounds().width - 10;
    float posY = 10;
    _sprite_ajustes.setPosition(posX, posY);

    _posto.setSize(sf::Vector2f(500, 500));
    _posto.setOrigin(_posto.getSize().x / 2, _posto.getSize().y / 2);
    _posto.setPosition(920, 500);
    _posto.setScale(_scala_originale_posto);
    aggiornaFenice();

    _attuale_punto.setFont(_font);
    _attuale_punto.setPosition(780, 10);
    _attuale_punto.setCharacterSize(100);
    _attuale_punto.setFillColor(sf::Color::White);

    _money_text.setFont(_font);
    _money_text.setPosition(1750, 50);
    _money_text.setCharacterSize(50);
    _money_text.setFillColor(sf::Color::White);

    _moneda.setPosition(1700, 65);
    if (_textureCoin.getSize().x > 0) {
        _moneda.setTexture(&_textureCoin);
    } else {
        _moneda.setFillColor(sf::Color::Yellow);
    }
    _moneda.setSize(sf::Vector2f(50, 50));

    setupMenu();

    return 0;
}

void Fenice::setupMenuParametros() {
    sf::Vector2f windowSize(static_cast<float>(_fenice.getSize().x), static_cast<float>(_fenice.getSize().y));

    // Fond du menu de paramètres
    float fondoWidth = 400.0f;
    float fondoHeight = 300.0f;
    _fondo_parametros.setSize(sf::Vector2f(fondoWidth, fondoHeight));
    _fondo_parametros.setPosition((windowSize.x - fondoWidth) / 2.0f, (windowSize.y - fondoHeight) / 2.0f);
    _fondo_parametros.setFillColor(sf::Color(50, 50, 50, 200)); // Fond semi-transparent

    // Premier bouton
    float botonWidth = 200.0f;
    float botonHeight = 50.0f;
    _boton_parametro_1.setSize(sf::Vector2f(botonWidth, botonHeight));
    _boton_parametro_1.setPosition(_fondo_parametros.getPosition().x + (fondoWidth - botonWidth) / 2.0f, _fondo_parametros.getPosition().y + 50.0f);
    _boton_parametro_1.setFillColor(sf::Color(100, 100, 100));

    _texto_parametro_1.setFont(_font);
    _texto_parametro_1.setString("SAVE");
    _texto_parametro_1.setCharacterSize(20);
    _texto_parametro_1.setFillColor(sf::Color::White);
    sf::FloatRect textoBounds1 = _texto_parametro_1.getLocalBounds();
    _texto_parametro_1.setOrigin(textoBounds1.left + textoBounds1.width / 2.0f, textoBounds1.top + textoBounds1.height / 2.0f);
    _texto_parametro_1.setPosition(_boton_parametro_1.getPosition().x + botonWidth / 2.0f, _boton_parametro_1.getPosition().y + botonHeight / 2.0f);

    // Deuxième bouton
    _boton_parametro_2.setSize(sf::Vector2f(botonWidth, botonHeight));
    _boton_parametro_2.setPosition(_fondo_parametros.getPosition().x + (fondoWidth - botonWidth) / 2.0f, _fondo_parametros.getPosition().y + 150.0f);
    _boton_parametro_2.setFillColor(sf::Color(100, 100, 100));

    _texto_parametro_2.setFont(_font);
    _texto_parametro_2.setString("RESET");
    _texto_parametro_2.setCharacterSize(20);
    _texto_parametro_2.setFillColor(sf::Color::White);
    sf::FloatRect textoBounds2 = _texto_parametro_2.getLocalBounds();
    _texto_parametro_2.setOrigin(textoBounds2.left + textoBounds2.width / 2.0f, textoBounds2.top + textoBounds2.height / 2.0f);
    _texto_parametro_2.setPosition(_boton_parametro_2.getPosition().x + botonWidth / 2.0f, _boton_parametro_2.getPosition().y + botonHeight / 2.0f);
}

void Fenice::correre(Gioco gioco) {
    while (_fenice.isOpen()) {
        sf::Event event;
        while (_fenice.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                salvaProgresso();
                _fenice.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    _menu_aperto = !_menu_aperto;
                    if (_menu_aperto) aggiornaTestoBottoni();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_fenice);
                    sf::Vector2f worldPos = _fenice.mapPixelToCoords(mousePos);
                    if (_sprite_ajustes.getGlobalBounds().contains(worldPos)) {
                        _menu_parametros_abierto = !_menu_parametros_abierto;
                    } else if (_menu_parametros_abierto) {
                        if (_boton_parametro_1.getGlobalBounds().contains(worldPos)) {
                            gioco.salvaProgresso();
                        } else if (_boton_parametro_2.getGlobalBounds().contains(worldPos)) {
                            gioco.resetGioco();
                            _punto = 0;
                            _temp = 0;
                            _prossimo_punto = 0;
                            _money = 0;
                            _click_potenza = 1;
                            _punti_per_secondo = 0;
                            _livello_spada = 0;
                            salvaProgresso();
                            bombardino_crocodilo();
                            setLivelloSpada(0);
                            aggiornaFenice();
                            aggiornaTestoBottoni();
                        } else if (!_fondo_parametros.getGlobalBounds().contains(worldPos)) {
                            _menu_parametros_abierto = false;
                        }
                    } else if (_menu_aperto) {
                        gestisciClickMenu(mousePos.x, mousePos.y);
                    } else {
                        if (_posto.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                              static_cast<float>(mousePos.y))) {
                            if (_suonoClickPosto.getBuffer()) _suonoClickPosto.play();

                            if (_textureCoin.getSize().x > 0) {
                                sf::Sprite coin(_textureCoin);
                                coin.setOrigin(static_cast<float>(_textureCoin.getSize().x) / 2.f,
                                               static_cast<float>(_textureCoin.getSize().y) / 2.f);
                                coin.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                                coin.setScale(2, 2);
                                _flyingCoins.push_back(coin);
                            }

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
        std::string moneyStr = std::to_string(_money);
        _money_text.setString(moneyStr);

        if (!_sta_animando_click) {
            aggiornaFenice();
        }

        _fenice.clear(sf::Color(50, 0, 0));
        _fenice.draw(_posto);
        _fenice.draw(_attuale_punto);
        _fenice.draw(_money_text);
        _fenice.draw(_moneda);
        _fenice.draw(_sprite_ajustes); // Le bouton de settings peut être dessiné ici

        if (_menu_aperto) {
            _fenice.draw(_menu_sfondo);
            _fenice.draw(_shop_titulo_texto);
            _fenice.draw(_bottone_click_upgrade);
            _fenice.draw(_testo_click_upgrade);
            _fenice.draw(_bottone_pps_upgrade);
            _fenice.draw(_testo_pps_upgrade);
            for (int i = 0; i < 5; ++i) {
                _fenice.draw(_bottoni_spade[i]);
                _fenice.draw(_sprite_spade[i]);
                _fenice.draw(_testi_spade[i]);
            }
        }

        // Dessiner le menu des paramètres APRÈS avoir dessiné les autres éléments
        if (_menu_parametros_abierto) {
            _fenice.draw(_fondo_parametros);
            _fenice.draw(_boton_parametro_1);
            _fenice.draw(_texto_parametro_1);
            _fenice.draw(_boton_parametro_2);
            _fenice.draw(_texto_parametro_2);
        }

        for (auto it = _flyingCoins.begin(); it != _flyingCoins.end();) {
            float verticalSpeed = -1.0f;
            it->move(0.f, verticalSpeed);

            if (it->getPosition().y + it->getGlobalBounds().height < 0) {
                it = _flyingCoins.erase(it);
            } else {
                _fenice.draw(*it);
                ++it;
            }
        }

        _fenice.display();
    }
}