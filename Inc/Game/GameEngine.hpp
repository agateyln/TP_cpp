#pragma once

#include "States/StateInterface.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void setState(std::unique_ptr<StateInterface> newState);
    void requestState(std::unique_ptr<StateInterface> newState); 
    void run();
    sf::RenderWindow& getWindow();

private:
    std::unique_ptr<StateInterface> currentState;
    std::unique_ptr<StateInterface> requestedState;
    bool running;
    sf::RenderWindow window;
};
