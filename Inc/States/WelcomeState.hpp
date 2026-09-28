#pragma once

#include "StateInterface.hpp"
#include <SFML/Graphics.hpp>

class GameEngine;
class Game;

class WelcomeState : public StateInterface {
private:
    GameEngine& engine;
    Game& game;
    sf::Font font;
    sf::Text title;
    sf::Text instruction;
    sf::Text message;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Sprite starter1;
    sf::Sprite starter2;

public:
    WelcomeState(GameEngine& engine, Game& game);
    void enter() override;
    void exit() override;
    void update() override;
};
