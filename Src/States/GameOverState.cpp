#include "States/GameOverState.hpp"
#include "GameEngine.hpp"

GameOverState::GameOverState(GameEngine& engine)
    : engine(engine) {
}

void GameOverState::enter() {
    engine.getWindow().setTitle("Pokemon - Game Over | Fermez la fenetre");
}

void GameOverState::exit() {
}

void GameOverState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}