#pragma once

#include <SFML/Graphics.hpp>
#include "StateInterface.hpp"
#include "Game/Button.hpp"
#include <string>
#include <vector>

class GameEngine;
class Game;

// the menu button will be used to open a menu where the player can choose to heal their Pokemon, view and manage their Pokemon party and attack list


class MenuState : public StateInterface {
    private:
        GameEngine& engine;
        Game& game;
        sf::Font font;
        sf::Text title;
        std::unique_ptr<Button> HealButton;
        std::unique_ptr<Button> PartyButton;
        std::unique_ptr<Button> AttackListButton;
        std::unique_ptr<Button> ExplorationButton;
        sf::RectangleShape panel;
        sf::Text panelTitle;
        std::vector<std::unique_ptr<sf::Texture>> panelTextures;
        std::vector<std::unique_ptr<sf::Sprite>> panelSprites;
        std::vector<std::unique_ptr<sf::Text>> panelLabels;
        std::vector<std::unique_ptr<Button>> panelButtons;
        std::unique_ptr<Button> previousPartyButton;
        std::unique_ptr<Button> nextPartyButton;
        std::size_t partyPage = 0;
        static constexpr std::size_t partyPageSize = 6;
        bool showPanel;
        bool refreshPartyPanel;
        bool refreshAttackPanel;

        void displayPartyPanel();
        void displayAttackPanel();
        void clearPanel();
        void drawPanel(sf::RenderWindow& window);
    public:
        MenuState(GameEngine& engine, Game& game);
        void enter() override;
        void exit() override;
        void update() override;
};