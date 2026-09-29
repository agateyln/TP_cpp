#pragma once

#include "StateInterface.hpp"
#include "Pokemon/Pokemon.hpp"
#include <SFML/Graphics.hpp>
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
        sf::Texture texture;
        sf::Sprite sprite;
        std::optional<Pokemon> wildPokemon;

    public:
        EncounterState(GameEngine& engine, Game& game);
        void enter() override;
        void exit() override;
        void update() override;
};