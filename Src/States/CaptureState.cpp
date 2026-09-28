#include "States/CaptureState.hpp"
#include "GameEngine.hpp"
#include "Game.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>

CaptureState::CaptureState(GameEngine& engine, Game& game,
                           const Pokemon& wildPokemon):
    engine(engine),
    game(game),
    wildPokemon(wildPokemon),
    font("../Res/font.otf"),
    title(font,"Battle to capture",40),
    attackerTexture("../Res/pokemon/1.png"),
    wildPokemonTexture("../Res/pokemon/1.png"),
    attackerSprite(attackerTexture),
    wildPokemonSprite(wildPokemonTexture) {
    title.setPosition({10.f,90.f});
}


void CaptureState::enter() {
    // the attacker is the player's pokemon, we take the first pokemon in the attack list
    if (game.getAttackList().empty()) {
        std::cerr << "Error: No pokemon in the attack list to use as attacker." << std::endl;
        std::abort();
    }

        attackerPokemon = game.getAttackList().getByIndex(0);

    engine.getWindow().setTitle("Pokemon - Capture battle");
    if (!attackerTexture.loadFromFile(
            "../Res/pokemon/" + std::to_string(attackerPokemon->getId()) + ".png")) {
        std::cerr << "Error: Unable to load the attacker's image." << std::endl;
    }
    attackerSprite.setTexture(attackerTexture);
    if (!wildPokemonTexture.loadFromFile(
            "../Res/pokemon/" + std::to_string(wildPokemon.getId()) + ".png")) {
        std::cerr << "Error: Unable to load the wild Pokemon's image." << std::endl;
    }
    wildPokemonSprite.setTexture(wildPokemonTexture);
    attackerSprite.setPosition({100.f,180.f});
    wildPokemonSprite.setPosition({350.f,180.f});

}

void CaptureState::exit() {

}

void CaptureState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::F) {
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
            } else if (key->code == sf::Keyboard::Key::C && attackerPokemon.has_value()) {
                std::cout << attackerPokemon->getName()
                          << " attacks " << wildPokemon.getName() << std::endl;
                if (attackerPokemon->attackPokemon(wildPokemon)) {
                    if (attackerPokemon->getAttack()-wildPokemon.getDefense()>0) {
                        wildPokemon.damagePokemon(attackerPokemon->getAttack() - wildPokemon.getDefense());
                        std::cout<<attackerPokemon->getName()<<" deals "<<attackerPokemon->getAttack()-wildPokemon.getDefense()<<" damage to "<<wildPokemon.getName()<<std::endl;
                        std::cout<<wildPokemon.getName()<<" has "<<wildPokemon.getHitPoint()<<" HP left."<<std::endl;
                    } else if (attackerPokemon->getAttack()-wildPokemon.getDefense()<=0) {
                        std::cout<<attackerPokemon->getName()<<" deals no damage to "<<wildPokemon.getName()<<std::endl;
                    }
                }

                if (!wildPokemon.isSleeping() && wildPokemon.attackPokemon(*attackerPokemon)) {
                    std::cout<<wildPokemon.getName()<<" attacks "<<attackerPokemon->getName()<<std::endl;
                    if (wildPokemon.getAttack()-attackerPokemon->getDefense()>0) {
                        attackerPokemon->damagePokemon(wildPokemon.getAttack() - attackerPokemon->getDefense());
                        std::cout<<wildPokemon.getName()<<" deals "<<wildPokemon.getAttack()-attackerPokemon->getDefense()<<" damage to "<<attackerPokemon->getName()<<std::endl;
                        std::cout<<attackerPokemon->getName()<<" has "<<attackerPokemon->getHitPoint()<<" HP left."<<std::endl;
                    } else if (wildPokemon.getAttack()-attackerPokemon->getDefense()<=0) {
                        std::cout<<wildPokemon.getName()<<" deals no damage to "<<attackerPokemon->getName()<<std::endl;
                    }
                }

                if (wildPokemon.isSleeping() || attackerPokemon->isSleeping()) {
                    if (wildPokemon.isSleeping()) {
                        game.getParty().addPokemonToParty(wildPokemon);
                    }
                    std::cout<<"Battle ended"<<std::endl;
                    engine.requestState(std::make_unique<ExplorationState>(engine, game));
                }
            }
        }
    }

    window.draw(title);
    window.draw(attackerSprite);
    window.draw(wildPokemonSprite);
}
