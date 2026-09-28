#pragma once

#include "StateInterface.hpp"

class GameEngine;

class GameOverState : public StateInterface {
private:
    GameEngine& engine;

public:
    explicit GameOverState(GameEngine& engine);
    void enter() override;
    void exit() override;
    void update() override;
};