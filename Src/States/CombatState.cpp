#include "States/CombatState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/ExplorationState.hpp"
#include "States/GameOverState.hpp"

CombatState::CombatState(GameEngine& engine, Game& game)
    : engine(engine), game(game) {
}

void CombatState::enter() {
    engine.getWindow().setTitle("Pokemon - Combat | W: victoire, L: defaite");
}

void CombatState::exit() { 
}

void CombatState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::W) {
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
            } else if (key->code == sf::Keyboard::Key::L) {
                engine.requestState(std::make_unique<GameOverState>(engine));
            }
        }
    }
}