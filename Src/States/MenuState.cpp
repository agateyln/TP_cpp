#include "States/MenuState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Game/Button.hpp"
#include "States/ExplorationState.hpp"
#include <iostream>
#include <string>

MenuState::MenuState(GameEngine& engine, Game& game):
    engine(engine),
    game(game),
    font("../Res/font.otf"),
    title(font,"Menu",40),
    backgroundTexture("../Res/bg/welcome.png"),
    backgroundSprite(backgroundTexture),
    HealButton(nullptr),
    PartyButton(nullptr),
    AttackListButton(nullptr),
    ExplorationButton(nullptr),
    panelTitle(font, "", 24),
    showPanel(false),
    refreshPartyPanel(false),
    refreshAttackPanel(false) {
        const sf::Color skyTextColor(24, 48, 78);
        title.setFillColor(skyTextColor);
        title.setPosition({600.f,30.f});
        panel.setPosition({420.f,20.f});
        panel.setSize({350.f,560.f});
        panel.setFillColor(sf::Color(36,48,72));
        panel.setOutlineColor(sf::Color(120,140,180)); 
        panel.setOutlineThickness(2.f);
        panelTitle.setPosition({445.f,45.f});
    }

void MenuState::enter() {
    engine.getWindow().setTitle("Pokemon - Menu");
    HealButton = std::make_unique<Button>(sf::Vector2f(100.f,200.f),sf::Vector2f(200.f,50.f),"Heal Party",font, [this]() {
        game.getParty().healAllPokemon();
    });
    PartyButton = std::make_unique<Button>(sf::Vector2f(100.f,300.f),sf::Vector2f(200.f,50.f),"View Party",font, [this]() {
        partyPage = 0;
        displayPartyPanel();
    });
    AttackListButton = std::make_unique<Button>(sf::Vector2f(100.f,400.f),sf::Vector2f(200.f,50.f),"View Attack list",font,[this]() {
        displayAttackPanel();
    }); 
    ExplorationButton = std::make_unique<Button>(sf::Vector2f(20.f,20.f),sf::Vector2f(100.f,50.f),"Back",font,[this](){
        engine.requestState(std::make_unique<ExplorationState>(engine, game));
    });
}

void MenuState::clearPanel() {
    panelTextures.clear();
    panelSprites.clear();
    panelLabels.clear();
    panelButtons.clear();
    previousPartyButton.reset();
    nextPartyButton.reset();
}

void MenuState::displayPartyPanel() {
    clearPanel();
    showPanel = true;
    panelTitle.setString("Your party");

    // calculate the number of pages based on the party size and page size
    const std::size_t partySize = game.getParty().size();
    const std::size_t pageCount = (partySize + partyPageSize - 1) / partyPageSize;
    if (pageCount == 0) {
        partyPage = 0;
    } else if (partyPage >= pageCount) {
        partyPage = pageCount - 1;
    }

    // calculate the range of Pokemon to display on the current page
    const std::size_t firstPokemon = partyPage * partyPageSize;
    const std::size_t lastPokemon = std::min(firstPokemon + partyPageSize, partySize);
    panelTextures.reserve(lastPokemon - firstPokemon);
    panelSprites.reserve(lastPokemon - firstPokemon);
    panelLabels.reserve(lastPokemon - firstPokemon);
    panelButtons.reserve(lastPokemon - firstPokemon);

    // display the pokemon for the current page
    for (std::size_t index = firstPokemon; index < lastPokemon; ++index) {
        Pokemon pokemon = game.getParty().getByIndex(index);
        const std::size_t row = index - firstPokemon;
        const std::string texturePath = "../Res/pokemon/" + std::to_string(pokemon.getId()) + ".png";
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            std::cerr << "Failed to load image: " << texturePath << std::endl;
            continue;
        }
        auto sprite = std::make_unique<sf::Sprite>(*texture);
        auto label = std::make_unique<sf::Text>(font, pokemon.getName() + "\n - HP: " + std::to_string(static_cast<int>(pokemon.getHitPoint())) + "\n - Atk: " + std::to_string(static_cast<int>(pokemon.getAttack())) + "\n - Def: " + std::to_string(static_cast<int>(pokemon.getDefense())), 14);

        sprite->setPosition({445.f, 85.f + static_cast<float>(row) * 75.f});
        label->setPosition({535.f, 110.f + static_cast<float>(row) * 75.f});
        panelTextures.push_back(std::move(texture));
        panelSprites.push_back(std::move(sprite));
        panelLabels.push_back(std::move(label));

        // button to add the Pokemon to the attack list, only if its hitPoint is greater than 0
        auto button= std::make_unique<Button>(sf::Vector2f(700.f,135.f + static_cast<float>(row)*75.f),sf::Vector2f(60.f,30.f),"Add",font,[this,pokemon]() {
            if (pokemon.getHitPoint() > 0) {
                game.getAttackList().addPokemonToAttackFromParty(game.getParty(),pokemon);
                refreshPartyPanel = true;
            }
        });
        panelButtons.push_back(std::move(button));

    }

    if (partyPage > 0) {
        previousPartyButton = std::make_unique<Button>(
            sf::Vector2f(445.f, 535.f),
            sf::Vector2f(90.f, 30.f),
            "<<",
            font,
            [this]() {
                --partyPage;
                refreshPartyPanel = true;
            });
    }
    if (partyPage + 1 < pageCount) {
        nextPartyButton = std::make_unique<Button>(
            sf::Vector2f(650.f, 535.f),
            sf::Vector2f(90.f, 30.f),
            ">>",
            font,
            [this]() {
                ++partyPage;
                refreshPartyPanel = true;
            });
    }

}

void MenuState::displayAttackPanel() {
    clearPanel();
    showPanel = true;
    panelTitle.setString("Attack list");
    panelTextures.reserve(game.getAttackList().size());
    panelSprites.reserve(game.getAttackList().size());
    panelLabels.reserve(game.getAttackList().size());

    // display the pokemon in the attack list
    for (std::size_t index = 0; index < game.getAttackList().size(); ++index) {
        Pokemon pokemon = game.getAttackList().getByIndex(index);
        const std::string texturePath = "../Res/pokemon/" + std::to_string(pokemon.getId()) + ".png";
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            std::cerr << "Failed to load image: " << texturePath << std::endl;
            continue;
        }
        auto sprite = std::make_unique<sf::Sprite>(*texture);
        auto label = std::make_unique<sf::Text>(font, pokemon.getName()+"\n - HP: " + std::to_string(static_cast<int>(pokemon.getHitPoint())) + "\n - Atk: " + std::to_string(static_cast<int>(pokemon.getAttack())) + "\n - Def: " + std::to_string(static_cast<int>(pokemon.getDefense())), 14);

        sprite->setPosition({445.f, 85.f + static_cast<float>(index) * 75.f});
        label->setPosition({535.f, 110.f + static_cast<float>(index) * 75.f});
        panelTextures.push_back(std::move(texture));
        panelSprites.push_back(std::move(sprite));
        panelLabels.push_back(std::move(label));

        // button to remove the Pokemon from the attack list to the party
        auto button=std::make_unique<Button>(sf::Vector2f(660.f,135.f + static_cast<float>(index)*75.f),sf::Vector2f(100.f,30.f),"Remove",font,[this,pokemon]() {
            game.getAttackList().removePokemonFromAttackToParty(game.getParty(),pokemon);
            refreshAttackPanel=true;
        });
        panelButtons.push_back(std::move(button)); 
    }
}

void MenuState::drawPanel(sf::RenderWindow& window) {
    if (!showPanel) {
        return;
    }
    window.draw(panel);
    window.draw(panelTitle);
    for (const auto& sprite : panelSprites) {
        window.draw(*sprite);
    }
    for (const auto& label : panelLabels) {
        window.draw(*label);
    }
    for (const auto& button : panelButtons) {
        button->draw(window);
    }
    if (previousPartyButton) {
        previousPartyButton->draw(window);
    }
    if (nextPartyButton) {
        nextPartyButton->draw(window);
    }
}

void MenuState::exit() {
}

void MenuState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        HealButton->handleEvent(*event, window);
        PartyButton->handleEvent(*event, window);
        AttackListButton->handleEvent(*event, window);
        ExplorationButton->handleEvent(*event, window);
        for (const auto& button : panelButtons) {
            button->handleEvent(*event, window);
        }
        if (previousPartyButton) {
            previousPartyButton->handleEvent(*event, window);
        }
        if (nextPartyButton) {
            nextPartyButton->handleEvent(*event, window);
        }
    }
    if (refreshPartyPanel) {
        refreshPartyPanel = false;
        displayPartyPanel();
    }
    if (refreshAttackPanel) {
        refreshAttackPanel = false;
        displayAttackPanel();
    }
    window.draw(backgroundSprite);
    window.draw(title);
    HealButton->draw(window);
    PartyButton->draw(window);
    AttackListButton->draw(window);
    ExplorationButton->draw(window);
    drawPanel(window);
}