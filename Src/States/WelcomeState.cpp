#include "States/WelcomeState.hpp"
#include "GameEngine.hpp"
#include "Game.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>

WelcomeState::WelcomeState(GameEngine& engine, Game& game):
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font, "Pokemon pour les nuls", 40),
    instruction(font, "Appuyez sur Entree pour continuer", 24),
    message(font,"On vous donne un Pokemon pour commencer",24),
    texture("../Res/pokemon/2.png"),
    sprite(texture) {
    title.setPosition({110.f, 90.f});
    instruction.setPosition({130.f, 500.f});
    sprite.setPosition({350.f, 180.f});
}

void WelcomeState::enter() {
    engine.getWindow().setTitle("Pokemon - Accueil | Appuyez sur Entree");
    const Pokemon starter = game.getPokedex().getById(2);
    game.getParty().addPokemonToParty(starter);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(), starter);
}

void WelcomeState::exit() {
    std::cout << "Sortie de l'ecran d'accueil." << std::endl;
}

void WelcomeState::update() {
    auto& window = engine.getWindow(); 
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Enter) {
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
            }
        }
    }

    window.draw(title);
    window.draw(instruction);
    window.draw(message);
    window.draw(sprite);
}
