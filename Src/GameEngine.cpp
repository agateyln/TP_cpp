#include "GameEngine.hpp"
#include <iostream>

GameEngine::GameEngine()
        : currentState(nullptr), requestedState(nullptr), running(true),
            window(sf::VideoMode({800, 600}), "Pokemon") {
        window.setFramerateLimit(60); 
}

GameEngine::~GameEngine() {
    if (currentState != nullptr) {
        currentState->exit();
    }
}

void GameEngine::setState(std::unique_ptr<StateInterface> newState) {
    if (currentState != nullptr) {
        currentState->exit();
    }
    currentState = std::move(newState); 
    if (currentState != nullptr) { 
        currentState->enter();
    }
}

void GameEngine::requestState(std::unique_ptr<StateInterface> newState) {
    requestedState = std::move(newState);
}

void GameEngine::run() {
    while (running && currentState != nullptr && window.isOpen()) {
        window.clear(sf::Color(24, 35, 55));
        currentState->update();
        if (requestedState != nullptr) {
            std::unique_ptr<StateInterface> nextState = std::move(requestedState); 
            setState(std::move(nextState)); 
        }
        window.display();
    }
}

sf::RenderWindow& GameEngine::getWindow() {
    return window;
}
