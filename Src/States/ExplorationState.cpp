#include "States/ExplorationState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Game/Button.hpp"
#include "States/ArenaState.hpp"
#include "States/EncounterState.hpp"
#include "States/MenuState.hpp"

ExplorationState::ExplorationState(GameEngine& engine, Game& game): 
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font,"Looking for Pokemon", 38),
    instruction(font,"(Wait for 5 seconds to encounter a wild Pokemon)",15),
    backgroundTexture("../Res/bg/exploration.png"),
    backgroundSprite(backgroundTexture),
    CombatButton(nullptr),
    MenuButton(nullptr){
    const sf::Color skyTextColor(24, 48, 78);
    title.setFillColor(skyTextColor);
    title.setPosition({30.f,90.f});
    instruction.setFillColor(skyTextColor);
    instruction.setPosition({40.f,200.f});
    }

void ExplorationState::enter() {
    encounterClock.restart(); 
    engine.getWindow().setTitle("Pokemon - Exploration");
    CombatButton = std::make_unique<Button>(sf::Vector2f(550.f,50.f),sf::Vector2f(200.f,50.f),"Arena (death)",font,[this]() {
        engine.requestState(std::make_unique<ArenaState>(engine,game));
    });
    MenuButton = std::make_unique<Button>(sf::Vector2f(550.f,120.f),sf::Vector2f(200.f,50.f),"Menu",font,[this]() {
       engine.requestState(std::make_unique<MenuState>(engine,game));
    });
}

void ExplorationState::exit() {
}

void ExplorationState::update() {
    auto& window = engine.getWindow(); 
    while (const std::optional<sf::Event> event = window.pollEvent()) { 
        if (event->is<sf::Event::Closed>()) { 
            window.close();
        } 
        CombatButton->handleEvent(*event, window);
        MenuButton->handleEvent(*event, window);
        }

    if (encounterClock.getElapsedTime().asSeconds() >= 5.0f) { 
        encounterClock.restart(); 
        engine.requestState(std::make_unique<EncounterState>(engine, game)); 
    }
    window.draw(backgroundSprite);
    window.draw(title);
    window.draw(instruction);
    CombatButton->draw(window);
    MenuButton->draw(window);
}
