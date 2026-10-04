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
        wildPokemonInfo(font,"",18),
    backgroundTexture("../Res/bg/exploration.png"),
    backgroundSprite(backgroundTexture),
    combatMessagePanel(),
    combatMessageText(font,"",16),
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
    const sf::Color skyTextColor(24, 48, 78);
    title.setFillColor(skyTextColor);
    wildPokemonInfo.setFillColor(skyTextColor);
    title.setPosition({10.f,10.f});
        wildPokemonInfo.setPosition({500.f,370.f});
    combatMessagePanel.setPosition({20.f,55.f});
    combatMessagePanel.setSize({760.f,180.f});
    combatMessagePanel.setFillColor(sf::Color(36,48,72));
    combatMessagePanel.setOutlineColor(sf::Color(120,140,180));
    combatMessagePanel.setOutlineThickness(2.f);
    combatMessageText.setPosition({35.f,70.f});
    panelTitle.setPosition({35.f,60.f});
}


void CaptureState::enter() {
    engine.getWindow().setTitle("Pokemon - Capture battle");
    AttackButton = std::make_unique<Button>(sf::Vector2f(50.f,500.f),sf::Vector2f(200.f,50.f),"Attack",font,[this](){
        handleAttack();
    });
    FleeButton = std::make_unique<Button>(sf::Vector2f(300.f,500.f),sf::Vector2f(200.f,50.f),"Flee",font,[this]() {
        engine.requestState(std::make_unique<ExplorationState>(engine,game));
        leavingState = true;
    });
    AttackListButton = std::make_unique<Button>(sf::Vector2f(550.f,500.f),sf::Vector2f(200.f,50.f),"Attack list",font,[this]() {
        displayAttackList();
    });

    if (game.getAttackList().empty()) {
        addCombatMessage("You have no Pokemon in your attack list.");
        engine.requestState(std::make_unique<ExplorationState>(engine, game));
        leavingState = true;
        return;
    }

    if (!attackerPokemon.has_value()) {
        attackerPokemon = game.getAttackList().getByIndex(0);
    }

    updateWildPokemonInfo();

    engine.getWindow().setTitle("Pokemon - Capture battle");

    if (!attackerTexture.loadFromFile(
            "../Res/pokemon/" + std::to_string(attackerPokemon->getId()) + ".png")) {
        std::cerr << "Error: Unable to load the attacker's image." << std::endl;
    }
    attackerSprite.setTexture(attackerTexture);
    attackerSprite.setOrigin({static_cast<float>(attackerTexture.getSize().x), 0.f});
    attackerSprite.setScale({-1.f, 1.f});
    
    if (!wildPokemonTexture.loadFromFile(
            "../Res/pokemon/" + std::to_string(wildPokemon.getId()) + ".png")) {
        std::cerr << "Error: Unable to load the wild Pokemon's image." << std::endl;
    }
    wildPokemonSprite.setTexture(wildPokemonTexture);
    attackerSprite.setPosition({160.f,330.f});
    wildPokemonSprite.setPosition({350.f,330.f});

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
    panelTitle.setCharacterSize(18);
    panelTitle.setPosition({35.f,60.f});
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
        auto label = std::make_unique<sf::Text>(
            font,
            pokemon.getName() + "\nHP: " + std::to_string(static_cast<int>(pokemon.getHitPoint()))
                + "\nAtk: " + std::to_string(static_cast<int>(pokemon.getAttack()))
                + "\nDef: " + std::to_string(static_cast<int>(pokemon.getDefense())),
            10);

        const float columnX = 25.f + static_cast<float>(index) * 125.f;
        sprite->setScale({0.5f,0.5f});
        sprite->setPosition({columnX,85.f});
        label->setPosition({columnX,135.f});
        attackListTextures.push_back(std::move(texture));
        attackListSprites.push_back(std::move(sprite));
        attackListLabels.push_back(std::move(label));

        // button to choose the Pokemon as the attacker
        auto button=std::make_unique<Button>(sf::Vector2f(columnX,200.f),sf::Vector2f(90.f,25.f),"Choose",font,[this,pokemon]() {
            attackerPokemon = pokemon;
            if (!attackerTexture.loadFromFile( 
                    "../Res/pokemon/" + std::to_string(attackerPokemon->getId()) + ".png")) {
                std::cerr << "Error: Unable to load the attacker's image." << std::endl;
            }
            attackerSprite.setTexture(attackerTexture);
            addCombatMessage("You chose " + attackerPokemon->getName() + " as your attacker.");
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
    window.draw(combatMessagePanel);
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

    window.draw(backgroundSprite);
    if (!leavingState) {
        window.draw(title);
        window.draw(attackerSprite);
        window.draw(wildPokemonSprite);
        window.draw(wildPokemonInfo);
    }

    if (!showPanel) {
        window.draw(combatMessagePanel);
        window.draw(combatMessageText);
    }
    window.draw(title);
    AttackButton->draw(window);
    FleeButton->draw(window);
    AttackListButton->draw(window);
    drawPanel(window);
}

void CaptureState::handleAttack() {
    if (attackerPokemon.has_value()) {
        addCombatMessage(attackerPokemon->getName() + " attacks " + wildPokemon.getName() + ".");
        if (attackerPokemon->attackPokemon(wildPokemon)) {
            if (attackerPokemon->getAttack()-wildPokemon.getDefense()>0) {
                wildPokemon.damagePokemon(attackerPokemon->getAttack() - wildPokemon.getDefense());
                addCombatMessage(attackerPokemon->getName() + " deals " + std::to_string(static_cast<int>(attackerPokemon->getAttack()-wildPokemon.getDefense())) + " damage.");
                addCombatMessage(wildPokemon.getName() + ": " + std::to_string(static_cast<int>(wildPokemon.getHitPoint())) + " HP left. " + attackerPokemon->getName() + ": " + std::to_string(static_cast<int>(attackerPokemon->getHitPoint())) + " HP left.");
            } else if (attackerPokemon->getAttack()-wildPokemon.getDefense()<=0) {
                addCombatMessage(attackerPokemon->getName() + " deals no damage.");
            }
        }

        if (!wildPokemon.isSleeping() && wildPokemon.attackPokemon(*attackerPokemon)) {
            addCombatMessage(wildPokemon.getName() + " attacks " + attackerPokemon->getName() + ".");
            if (wildPokemon.getAttack()-attackerPokemon->getDefense()>0) {
                attackerPokemon->damagePokemon(wildPokemon.getAttack() - attackerPokemon->getDefense());
                addCombatMessage(wildPokemon.getName() + " deals " + std::to_string(static_cast<int>(wildPokemon.getAttack()-attackerPokemon->getDefense())) + " damage.");
                addCombatMessage(attackerPokemon->getName() + ": " + std::to_string(static_cast<int>(attackerPokemon->getHitPoint())) + " HP left. " + wildPokemon.getName() + ": " + std::to_string(static_cast<int>(wildPokemon.getHitPoint())) + " HP left.");
            } else if (wildPokemon.getAttack()-attackerPokemon->getDefense()<=0) {
                addCombatMessage(wildPokemon.getName() + " deals no damage.");
            }
        }

        game.getAttackList().updatePokemon(*attackerPokemon);

        if (wildPokemon.isSleeping() || attackerPokemon->isSleeping()) {
            if (wildPokemon.isSleeping()) { 
                addCombatMessage(wildPokemon.getName() + " has been captured!");
                game.getParty().addPokemonToParty(wildPokemon);
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
                leavingState = true;
            } else if (attackerPokemon->isSleeping()) {
                addCombatMessage(attackerPokemon->getName() + " has fallen asleep and returns to the party.");
                game.getAttackList().removePokemonFromAttackToParty(game.getParty(),*attackerPokemon); 
                attackerPokemon.reset();
            }

            if (game.getAttackList().empty()) {
                addCombatMessage("All your Pokemon are sleeping. Heal them at the hospital.");
                engine.requestState(std::make_unique<ExplorationState>(engine, game));
                leavingState = true;
            } else if (!game.getAttackList().empty() && !attackerPokemon.has_value()) { 
                addCombatMessage("Choose another attacker or flee.");
            }
        }
        updateWildPokemonInfo();
    }
}

void CaptureState::updateWildPokemonInfo() {
    wildPokemonInfo.setString(
        wildPokemon.getName() + "\n"
        "- HP: " + std::to_string(static_cast<int>(wildPokemon.getHitPoint())) + "\n"
        "- Attack: " + std::to_string(static_cast<int>(wildPokemon.getAttack())) + "\n"
        "- Defense: " + std::to_string(static_cast<int>(wildPokemon.getDefense())));
}

void CaptureState::addCombatMessage(const std::string& message) {
    constexpr std::size_t maxMessages = 7;
    combatMessages.push_back(message);
    if (combatMessages.size() > maxMessages) {
        combatMessages.erase(combatMessages.begin());
    }

    std::string text;
    for (const std::string& combatMessage : combatMessages) {
        text += combatMessage + "\n";
    }
    combatMessageText.setString(text);
}
