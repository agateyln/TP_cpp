#include "States/CaptureState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Game/Button.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>
#include <stdexcept>

CaptureState::CaptureState(GameEngine& engine, Game& game, const Pokemon& wildPokemon):
    engine(engine),
    game(game),
    wildPokemon(wildPokemon),
    font("../Res/font.otf"),
    title(font,"Battle to capture",40),
    attackerTexture("../Res/pokemon/1.png"),
    wildPokemonTexture("../Res/pokemon/1.png"),
    attackerSprite(attackerTexture),
    wildPokemonSprite(wildPokemonTexture),
    AttackButton(nullptr),
    FleeButton(nullptr),
    AttackListButton(nullptr),
    panelTitle(font,"",24),
    showPanel(false),
    refreshAttackPanel(false) {
    title.setPosition({10.f,90.f});
    panelTitle.setPosition({445.f,45.f});
}


void CaptureState::enter() {
    engine.getWindow().setTitle("Pokemon - Capture battle");
    AttackButton = std::make_unique<Button>(sf::Vector2f(100.f,500.f),sf::Vector2f(200.f,50.f),"Attack",font,[this](){
        handleAttack();
    });
    FleeButton = std::make_unique<Button>(sf::Vector2f(350.f,500.f),sf::Vector2f(200.f,50.f),"Flee",font,[this]() {
        engine.requestState(std::make_unique<ExplorationState>(engine,game));
        leavingState = true;
    });
    AttackListButton = std::make_unique<Button>(sf::Vector2f(600.f,500.f),sf::Vector2f(200.f,50.f),"Attack list",font,[this]() {
        displayAttackList();
    });

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

void CaptureState::clearPanel() {
    attackListTextures.clear();
    attackListSprites.clear();
    attackListLabels.clear();
    attackListButtons.clear();
}

void CaptureState::displayAttackList() {
    clearPanel();
    showPanel = true;
    refreshAttackPanel = false;
    panelTitle.setString("Attack list");
    attackListTextures.reserve(game.getAttackList().size());
    attackListSprites.reserve(game.getAttackList().size());
    attackListLabels.reserve(game.getAttackList().size());
    attackListButtons.reserve(game.getAttackList().size());

    if (attackerPokemon.has_value()) {
        game.getAttackList().updatePokemon(*attackerPokemon);
    }

    for (std::size_t index = 0; index < game.getAttackList().size(); ++index) {
        Pokemon pokemon = game.getAttackList().getByIndex(index);
        const std::string texturePath = "../Res/pokemon/" + std::to_string(pokemon.getId())+".png";
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            std::cerr << "Failed to load image: "<<texturePath<<std::endl;
            continue;
        }
        auto sprite = std::make_unique<sf::Sprite>(*texture);
        auto label = std::make_unique<sf::Text>(font,pokemon.getName()+"\n - HP: "+std::to_string(static_cast<int>(pokemon.getHitPoint()))+"\n - Atk: "+std::to_string(static_cast<int>(pokemon.getAttack()))+"\n - Def: "+std::to_string(static_cast<int>(pokemon.getDefense())),14);

        sprite->setPosition({445.f,85.f + static_cast<float>(index)*75.f});
        label->setPosition({535.f,110.f + static_cast<float>(index)*75.f});
        attackListTextures.push_back(std::move(texture));
        attackListSprites.push_back(std::move(sprite));
        attackListLabels.push_back(std::move(label));

        // button to choose the Pokemon as the attacker
        auto button=std::make_unique<Button>(sf::Vector2f(700.f,120.f + static_cast<float>(index)*75.f),sf::Vector2f(60.f,30.f),"Choose",font,[this,pokemon]() {
            attackerPokemon = pokemon;
            if (!attackerTexture.loadFromFile( 
                    "../Res/pokemon/" + std::to_string(attackerPokemon->getId()) + ".png")) {
                std::cerr << "Error: Unable to load the attacker's image." << std::endl;
            }
            attackerSprite.setTexture(attackerTexture);
            std::cout<<"You chose "<<attackerPokemon->getName()<<" as your attacker."<<std::endl;
            refreshAttackPanel = true;
            showPanel = false;
        });
        attackListButtons.push_back(std::move(button));
    }
    
}

void CaptureState::drawPanel(sf::RenderWindow& window) {
    if (!showPanel) {
        return;
    }
    window.draw(panelTitle);
    for (const auto& sprite : attackListSprites) {
        window.draw(*sprite);
    }
    for (const auto& label : attackListLabels) {
        window.draw(*label);
    }
    for (const auto& button : attackListButtons) {
        button->draw(window);
    }
}

void CaptureState::exit() {}

void CaptureState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        AttackButton->handleEvent(*event,window);
        FleeButton->handleEvent(*event,window);
        AttackListButton->handleEvent(*event,window);
        for (const auto& button : attackListButtons) {
            button->handleEvent(*event,window);
        }
    }
    if (refreshAttackPanel && showPanel) {
        refreshAttackPanel = false;
        displayAttackList();
    }

    if (!leavingState) {
        window.draw(title);
        window.draw(attackerSprite);
        window.draw(wildPokemonSprite);
    }
    
    window.draw(title);
    AttackButton->draw(window);
    FleeButton->draw(window);
    AttackListButton->draw(window);
    drawPanel(window);
}

void CaptureState::handleAttack() {
    if (attackerPokemon.has_value()) {
        std::cout<<"Attacker: "<<attackerPokemon->getName()<<" | Attack: "<<attackerPokemon->getAttack()<<" | Defense: "<<attackerPokemon->getDefense()<<" | HP: "<<attackerPokemon->getHitPoint()<<std::endl;
        std::cout<<"Wild Pokemon: "<<wildPokemon.getName()<<" | Attack: "<<wildPokemon.getAttack()<<" | Defense: "<<wildPokemon.getDefense()<<" | HP: "<<wildPokemon.getHitPoint()<<"\n"<<std::endl;

        std::cout << attackerPokemon->getName()<< " attacks " << wildPokemon.getName() << std::endl;
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
