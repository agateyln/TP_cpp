#pragma once

#include "StateInterface.hpp"

class GameEngine;
class Game;

class CombatState : public StateInterface {
private:
    GameEngine& engine;
    Game& game;

public:
    CombatState(GameEngine& engine, Game& game);
    void enter() override;
    void exit() override;
    void update() override;
};