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
    message(font,"On vous donne deux Pokemon pour commencer",24),
    texture1("../Res/pokemon/2.png"),
    texture2("../Res/pokemon/40.png"),
    starter1(texture1),
    starter2(texture2) {
    title.setPosition({110.f, 90.f});
    instruction.setPosition({130.f, 500.f});
    starter1.setPosition({100.f, 180.f});
    starter2.setPosition({350.f, 180.f});
}

void WelcomeState::enter() {
    engine.getWindow().setTitle("Pokemon - Accueil | Appuyez sur Entree");
    // Add the two starter Pokemon to the player's party
    Pokemon starter = game.getPokedex().getById(2);
    Pokemon starter2 = game.getPokedex().getById(40);
    game.getParty().addPokemonToParty(starter);
    game.getParty().addPokemonToParty(starter2);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(), starter);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(), starter2);
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
    window.draw(starter1);
    window.draw(starter2);
}
