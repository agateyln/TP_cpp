#include "States/ExplorationState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/CombatState.hpp"
#include "States/EncounterState.hpp"
#include <random>

ExplorationState::ExplorationState(GameEngine& engine, Game& game): 
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font,"Looking for Pokemon", 40),
    instruction(font, "Press E for wild encounter, T for trainer encounter", 20) {
    title.setPosition({110.f,90.f});
    instruction.setPosition({130.f,500.f});
    }

void ExplorationState::enter() {
    encounterClock.restart(); 
    engine.getWindow().setTitle("Pokemon - Exploration | E: sauvage, T: dresseur");
}

void ExplorationState::exit() {
}

void ExplorationState::update() {
    auto& window = engine.getWindow(); 
    while (const std::optional<sf::Event> event = window.pollEvent()) { 
        if (event->is<sf::Event::Closed>()) { 
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) { 
            if (key->code == sf::Keyboard::Key::E) {
                engine.requestState(std::make_unique<EncounterState>(engine, game)); 
            } else if (key->code == sf::Keyboard::Key::T) {
                engine.requestState(std::make_unique<CombatState>(engine, game));
            }
        }
    }

    if (encounterClock.getElapsedTime().asSeconds() >= 10.0f) { 
        static std::mt19937 generator(std::random_device{}());
        std::bernoulli_distribution trainerEncounter(0.25); 
        encounterClock.restart(); 
        if (trainerEncounter(generator)) {
            engine.requestState(std::make_unique<CombatState>(engine, game)); 
        } else {
            engine.requestState(std::make_unique<EncounterState>(engine, game)); 
        }
    }
    window.draw(title);
    window.draw(instruction);
}
