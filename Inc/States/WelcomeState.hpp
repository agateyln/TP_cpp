#pragma once

#include "StateInterface.hpp"
#include "Game/Button.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

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
    sf::Texture patachiotTexture;
    sf::Sprite starter1;
    sf::Sprite starter2;
    sf::Sprite patachiot;
    std::unique_ptr<Button> button;

public:
    WelcomeState(GameEngine& engine, Game& game);
    void enter() override;
    void exit() override;
    void update() override;
};
