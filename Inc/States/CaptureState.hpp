#pragma once

#include "StateInterface.hpp"
#include "Pokemon/Pokemon.hpp"
#include <SFML/Graphics.hpp>
#include "Game/Button.hpp"
#include <optional>

class GameEngine;
class Game;

class CaptureState : public StateInterface { 
    private:
        GameEngine& engine;
        Game& game;
        Pokemon wildPokemon;
        std::optional<Pokemon> attackerPokemon;
        bool leavingState = false;
        sf::Font font;
        sf::Text title;
        sf::Texture attackerTexture;
        sf::Texture wildPokemonTexture;
        sf::Sprite attackerSprite;
        sf::Sprite wildPokemonSprite;
        std::unique_ptr<Button> AttackButton;
        std::unique_ptr<Button> FleeButton;
        std::unique_ptr<Button> AttackListButton;
        sf::Text panelTitle;
        std::vector<std::unique_ptr<sf::Texture>> attackListTextures; 
        std::vector<std::unique_ptr<sf::Sprite>> attackListSprites;
        std::vector<std::unique_ptr<sf::Text>> attackListLabels;
        std::vector<std::unique_ptr<Button>> attackListButtons;
        void handleAttack();
        void displayAttackList();
        void clearPanel();
        void drawPanel(sf::RenderWindow& window);
        bool showPanel;
        bool refreshAttackPanel;
    
    public:
        CaptureState(GameEngine& engine, Game& game, const Pokemon& wildPokemon);
        void enter() override;
        void exit() override;
        void update() override;
};