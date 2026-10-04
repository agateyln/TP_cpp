#include "States/EncounterState.hpp"
#include "States/CaptureState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/ExplorationState.hpp"
#include "Game/Button.hpp"
#include <random>

EncounterState::EncounterState(GameEngine& engine, Game& game): 
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font, "Wild Pokemon Encounter!",40),
    instruction(font,"Choose an action",20),
    backgroundTexture("../Res/bg/exploration.png"),
    backgroundSprite(backgroundTexture),
    texture("../Res/pokemon/1.png"),
    sprite(texture),
    CombatButton(nullptr),
    FleeButton(nullptr) {
    const sf::Color skyTextColor(24, 48, 78);
    title.setFillColor(skyTextColor);
    instruction.setFillColor(skyTextColor);
    title.setPosition({10.f,90.f});
    instruction.setPosition({10.f,430.f});
}

void EncounterState::enter() {
    engine.getWindow().setTitle("Pokemon - Encounter");
    CombatButton = std::make_unique<Button>(sf::Vector2f(100.f, 500.f),sf::Vector2f(200.f, 50.f),"Combat",font,[this]() {
        if (wildPokemon.has_value()) {
            engine.requestState(std::make_unique<CaptureState>(engine, game, *wildPokemon));
        }
    });
    FleeButton = std::make_unique<Button>(sf::Vector2f(350.f, 500.f),sf::Vector2f(200.f, 50.f),"Flee",font,[this]() {
        engine.requestState(std::make_unique<ExplorationState>(engine, game));
    });

    const Pokedex& pokedex = game.getPokedex();
    if (pokedex.empty()) {
        return;
    }

    // generate a rando index to select a wild Pokemon from Pokedex
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,static_cast<int>(pokedex.size())-1); 
    int randomIndex=dis(gen);
        wildPokemon = pokedex.getByIndex(randomIndex);
        title.setString("Wild Pokemon: \n" + wildPokemon->getName());
    if (!texture.loadFromFile(
            "../Res/pokemon/" + std::to_string(wildPokemon->getId()) + ".png")) {
        return;
    }
    sprite.setPosition({350.f,290.f});

}

void EncounterState::exit() {
}

void EncounterState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        CombatButton->handleEvent(*event, window);
        FleeButton->handleEvent(*event, window);
    }

    window.draw(backgroundSprite);
    window.draw(title);
    window.draw(instruction);
    window.draw(sprite);
    CombatButton->draw(window);
    FleeButton->draw(window);
}