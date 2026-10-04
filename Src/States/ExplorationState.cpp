#include "States/ExplorationState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Game/Button.hpp"
#include "States/CombatState.hpp"
#include "States/EncounterState.hpp"
#include "States/MenuState.hpp"

ExplorationState::ExplorationState(GameEngine& engine, Game& game): 
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font,"Looking for Pokemon", 40),
    instruction(font, "Press E for wild encounter, T for trainer encounter", 20),
    backgroundTexture("../Res/bg/exploration.png"),
    backgroundSprite(backgroundTexture),
    CombatButton(nullptr),
    MenuButton(nullptr){
    title.setPosition({110.f,90.f});
    instruction.setPosition({130.f,500.f});
    }

void ExplorationState::enter() {
    encounterClock.restart(); 
    engine.getWindow().setTitle("Pokemon - Exploration");
    CombatButton = std::make_unique<Button>(sf::Vector2f(550.f,50.f),sf::Vector2f(200.f,50.f),"Combat in arena",font,[this]() {
        engine.requestState(std::make_unique<CombatState>(engine,game));
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
