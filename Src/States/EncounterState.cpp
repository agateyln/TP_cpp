#include "States/EncounterState.hpp"
#include "States/CaptureState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/ExplorationState.hpp"
#include <random>

EncounterState::EncounterState(GameEngine& engine, Game& game): 
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font, "Wild Pokemon Encounter!",40),
    instruction(font,"Press C to try to capture, or F to flee",20),
    texture("../Res/pokemon/1.png"),
    sprite(texture) {
    title.setPosition({10.f,90.f});
    instruction.setPosition({10.f,500.f});
}

void EncounterState::enter() {
    engine.getWindow().setTitle("Pokemon - Rencontre avec un Pokemon sauvage");
    const Pokedex& pokedex = game.getPokedex();
    if (pokedex.empty()) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,static_cast<int>(pokedex.size())-1); 
    int randomIndex=dis(gen);
        wildPokemon = pokedex.getByIndex(randomIndex);
        title.setString("Wild Pokemon: " + wildPokemon->getName());
    if (!texture.loadFromFile(
            "../Res/pokemon/" + std::to_string(wildPokemon->getId()) + ".png")) {
        return;
    }
    sprite.setPosition({350.f,180.f});

}

void EncounterState::exit() {
}

void EncounterState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::C) {
                if (wildPokemon.has_value()) {
                    engine.requestState(std::make_unique<CaptureState>(
                        engine, game, *wildPokemon));
                }
            } else if (key->code == sf::Keyboard::Key::F) {
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
            }
        }
    }
    window.draw(title);
    window.draw(instruction);
    window.draw(sprite);
}