#include "States/WelcomeState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Game/Button.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>

WelcomeState::WelcomeState(GameEngine& engine, Game& game):
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font, "Pokemon pour les nuls", 40),
    instruction(font, "Appuyez sur le bouton", 24),
    message(font,"On vous donne deux Pokemon pour commencer",24),
    texture1("../Res/pokemon/2.png"),
    texture2("../Res/pokemon/40.png"),
    patachiotTexture("../Res/pokemon/926.png"),
    starter1(texture1),
    starter2(texture2),
    patachiot(patachiotTexture),
    button(nullptr) {
    title.setPosition({110.f, 90.f});
    instruction.setPosition({130.f, 500.f});
    starter1.setPosition({100.f, 180.f});
    starter2.setPosition({350.f, 180.f});
    patachiot.setPosition({225.f, 300.f});
    }

void WelcomeState::enter() {
    engine.getWindow().setTitle("Pokemon - Accueil | Appuyez sur Entree");
    // Add the two starter Pokemon to the player's party
    Pokemon starter = game.getPokedex().getById(2);
    Pokemon starter2 = game.getPokedex().getById(40);
    Pokemon patachiot = game.getPokedex().getById(926);
    game.getParty().addPokemonToParty(starter);
    game.getParty().addPokemonToParty(starter2);
    game.getParty().addPokemonToParty(patachiot);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(), starter);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(), starter2);
    game.getAttackList().addPokemonToAttackFromParty(game.getParty(),patachiot);

    // create the button to start the game
    
    button = std::make_unique<Button>(sf::Vector2f(300.f,400.f), sf::Vector2f(200.f,50.f),"Start Game", font, [this]() {
        engine.requestState(std::make_unique<ExplorationState>(engine, game));
    });
}

void WelcomeState::exit() {
    std::cout << "Sortie de l'ecran d'accueil." << std::endl;
}


void WelcomeState::update() {
    auto& window = engine.getWindow(); 
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        button->handleEvent(*event, window);
    }
    

    window.draw(title);
    window.draw(instruction);
    window.draw(message);
    window.draw(starter1);
    window.draw(starter2);
    window.draw(patachiot);
    button->draw(window);

}
