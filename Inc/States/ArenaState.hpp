#pragma once

#include "StateInterface.hpp"
#include "Game/Button.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class GameEngine;
class Game;

class ArenaState : public StateInterface {
private:
    GameEngine& engine;
    Game& game;
    sf::Font font;
    sf::Text title;
    std::unique_ptr<Button> explorationButton;
    std::unique_ptr<Button> gameOverButton;

public:
    ArenaState(GameEngine& engine, Game& game);
    void enter() override;
    void exit() override;
    void update() override;
};