#pragma once

#include "StateInterface.hpp"
#include "Pokemon.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class GameEngine;
class Game;

class CaptureState : public StateInterface { 
    private:
        GameEngine& engine;
        Game& game;
        Pokemon wildPokemon;
        std::optional<Pokemon> attackerPokemon;
        sf::Font font;
        sf::Text title;
        sf::Texture attackerTexture;
        sf::Texture wildPokemonTexture;
        sf::Sprite attackerSprite;
        sf::Sprite wildPokemonSprite;
    
    public:
        CaptureState(GameEngine& engine, Game& game, const Pokemon& wildPokemon);
        void enter() override;
        void exit() override;
        void update() override;
};