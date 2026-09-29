#include "States/CaptureState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>
#include <stdexcept>

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
        std::cout<<"You have no Pokemon in your attack list."<<std::endl;
        engine.requestState(std::make_unique<ExplorationState>(engine, game));
        leavingState = true;
        return;
    }

    if (!attackerPokemon.has_value()) {
        attackerPokemon = game.getAttackList().getByIndex(0);
    }

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

// to replace the pressing of keys with clickable buttons, we will need to create a button class and handle mouse events in the update method.
// to do so, we first need to create a button class that can be drawn on the window and can detect mouse clicks. Then, we will create buttons for "Attack", "Flee", and "Choose Attacker" and handle their click events in the update method.
// the button class will have a rectangle shape, a text label, and a callback function that will be called when the button is clicked. 

void CaptureState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::F) {
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
                leavingState = true;
            } else if (key->code == sf::Keyboard::Key::A) { // press A to display the player's attackList and choose an attacker
                if (attackerPokemon.has_value()) {
                    game.getAttackList().updatePokemon(*attackerPokemon);
                }
                std::cout<<"Choose your attacker Pokemon by index:"<<std::endl;
                game.getAttackList().displayListPokemon(static_cast<int>(game.getAttackList().size()));
                int pokemonId;
                std::cin >> pokemonId;
                try {
                    attackerPokemon = game.getAttackList().getById(pokemonId);
                    if (!attackerTexture.loadFromFile(
                            "../Res/pokemon/" + std::to_string(attackerPokemon->getId()) + ".png")) {
                        std::cerr << "Error: Unable to load the attacker's image." << std::endl;
                    }
                    attackerSprite.setTexture(attackerTexture);
                    std::cout<<"You chose "<<attackerPokemon->getName()<<" as your attacker."<<std::endl;
                } catch (const std::invalid_argument&) {
                    std::cout << "No Pokemon with id " << pokemonId
                              << " in the attack list." << std::endl;
                }

            } else if (key->code == sf::Keyboard::Key::C && attackerPokemon.has_value()) {
                // display the attack, defense and hit points of both Pokemon
                std::cout<<"Attacker: "<<attackerPokemon->getName()<<" | Attack: "<<attackerPokemon->getAttack()<<" | Defense: "<<attackerPokemon->getDefense()<<" | HP: "<<attackerPokemon->getHitPoint()<<std::endl;
                std::cout<<"Wild Pokemon: "<<wildPokemon.getName()<<" | Attack: "<<wildPokemon.getAttack()<<" | Defense: "<<wildPokemon.getDefense()<<" | HP: "<<wildPokemon.getHitPoint()<<"\n"<<std::endl;

                std::cout << attackerPokemon->getName()
                          << " attacks " << wildPokemon.getName() << std::endl;
                if (attackerPokemon->attackPokemon(wildPokemon)) {
                    if (attackerPokemon->getAttack()-wildPokemon.getDefense()>0) {
                        wildPokemon.damagePokemon(attackerPokemon->getAttack() - wildPokemon.getDefense());
                        std::cout<<attackerPokemon->getName()<<" deals "<<attackerPokemon->getAttack()-wildPokemon.getDefense()<<" damage to "<<wildPokemon.getName()<<std::endl;
                        std::cout<<wildPokemon.getName()<<" has "<<wildPokemon.getHitPoint()<<" HP left."<<std::endl;
                    } else if (attackerPokemon->getAttack()-wildPokemon.getDefense()<=0) {
                        std::cout<<attackerPokemon->getName()<<" deals no damage to "<<wildPokemon.getName()<<"\n"<<std::endl;
                    }
                }

                if (!wildPokemon.isSleeping() && wildPokemon.attackPokemon(*attackerPokemon)) {
                    std::cout<<"Attacker: "<<attackerPokemon->getName()<<" | Attack: "<<attackerPokemon->getAttack()<<" | Defense: "<<attackerPokemon->getDefense()<<" | HP: "<<attackerPokemon->getHitPoint()<<std::endl;
                    std::cout<<"Wild Pokemon: "<<wildPokemon.getName()<<" | Attack: "<<wildPokemon.getAttack()<<" | Defense: "<<wildPokemon.getDefense()<<" | HP: "<<wildPokemon.getHitPoint()<<"\n"<<std::endl;
                
                    std::cout<<wildPokemon.getName()<<" attacks "<<attackerPokemon->getName()<<std::endl;
                    if (wildPokemon.getAttack()-attackerPokemon->getDefense()>0) {
                        attackerPokemon->damagePokemon(wildPokemon.getAttack() - attackerPokemon->getDefense());
                        std::cout<<wildPokemon.getName()<<" deals "<<wildPokemon.getAttack()-attackerPokemon->getDefense()<<" damage to "<<attackerPokemon->getName()<<std::endl;
                        std::cout<<attackerPokemon->getName()<<" has "<<attackerPokemon->getHitPoint()<<" HP left."<<std::endl;
                    } else if (wildPokemon.getAttack()-attackerPokemon->getDefense()<=0) {
                        std::cout<<wildPokemon.getName()<<" deals no damage to "<<attackerPokemon->getName()<<"\n"<<std::endl;
                    }
                }

                game.getAttackList().updatePokemon(*attackerPokemon);

                if (wildPokemon.isSleeping() || attackerPokemon->isSleeping()) {
                    if (wildPokemon.isSleeping()) { 
                        std::cout<<wildPokemon.getName()<<" has been captured!"<<std::endl;
                        game.getParty().addPokemonToParty(wildPokemon);
                        std::cout<<"Your party: "<<std::endl;
                        game.getParty().displayListPokemon(static_cast<int>(game.getParty().size()));
                        std::cout<<"Your attack list: "<<std::endl;
                        game.getAttackList().displayListPokemon(static_cast<int>(game.getAttackList().size()));
                        engine.requestState(std::make_unique<ExplorationState>(engine, game));
                        leavingState = true;
                    } else if (attackerPokemon->isSleeping()) {
                        std::cout<<attackerPokemon->getName()<<" has fallen asleep and goes back to the party with their friends (or not)."<<std::endl;
                        game.getAttackList().removePokemonFromAttackToParty(game.getParty(),*attackerPokemon); 
                        std::cout<<"Your party: "<<std::endl;
                        game.getParty().displayListPokemon(static_cast<int>(game.getParty().size()));
                        std::cout<<"Your attack list: "<<std::endl;
                        game.getAttackList().displayListPokemon(static_cast<int>(game.getAttackList().size()));
                        attackerPokemon.reset();
                    }

                    if (game.getAttackList().empty()) {
                        std::cout<<"All your Pokemon are sleeping. You have no more Pokemon to fight with. Heal them at the hospital."<<std::endl;
                        engine.requestState(std::make_unique<ExplorationState>(engine, game));
                        leavingState = true;
                    } else if (!game.getAttackList().empty() && !attackerPokemon.has_value()) { 
                        std::cout<<"You still have Pokemon to fight with. Choose another attacker by pressing A or flee by pressing F."<<std::endl;
                    }
                }
            }
        }
    }

    if (!leavingState) {
        window.draw(title);
        window.draw(attackerSprite);
        window.draw(wildPokemonSprite);
    }
}
