#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp> 
#include "StateInterface.hpp"

class GameEngine;
class Game;

class ExplorationState : public StateInterface {
private:
        GameEngine& engine; // Adding engine reference
        Game& game;
        sf::Clock encounterClock; // Adding encounter clock
        sf::Font font;
        sf::Text title;
        sf::Text instruction;

public:
    void enter() override;
    void exit() override;
    void update() override;
    ExplorationState(GameEngine& engine, Game& game);
};
