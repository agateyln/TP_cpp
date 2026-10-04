#pragma once

#include "StateInterface.hpp"
#include "Pokemon/Pokemon.hpp"
#include "Game/Button.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

class GameEngine;
class Game;

class EncounterState : public StateInterface {
    private:
        GameEngine& engine;
        Game& game;
        sf::Font font;
        sf::Text title;
        sf::Text instruction;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Texture texture;
        sf::Sprite sprite;
        std::unique_ptr<Button> CombatButton;
        std::unique_ptr<Button> FleeButton;
        std::optional<Pokemon> wildPokemon;

    public:
        EncounterState(GameEngine& engine, Game& game);
        void enter() override;
        void exit() override;
        void update() override;
};