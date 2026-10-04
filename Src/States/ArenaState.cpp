#include "States/ArenaState.hpp"
#include "Game/GameEngine.hpp"
#include "Game/Game.hpp"
#include "States/ExplorationState.hpp"
#include "States/GameOverState.hpp"

ArenaState::ArenaState(GameEngine& engine, Game& game)
    : engine(engine),
      game(game),
      font("../Res/font.otf"),
      title(font, "Choose your path", 42),
      explorationButton(nullptr),
      gameOverButton(nullptr) {
        title.setPosition({170.f, 180.f});
}

void ArenaState::enter() {
    engine.getWindow().setTitle("Pokemon - Arena");
    explorationButton = std::make_unique<Button>(sf::Vector2f(100.f, 300.f),sf::Vector2f(250.f, 50.f),"Left",font,[this]() {
            engine.requestState(std::make_unique<ExplorationState>(engine, game));
        });
    gameOverButton = std::make_unique<Button>(sf::Vector2f(450.f, 300.f),sf::Vector2f(250.f, 50.f),"Right",font,[this]() {
            engine.requestState(std::make_unique<GameOverState>(engine));
        });
}

void ArenaState::exit() { 
}

void ArenaState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        explorationButton->handleEvent(*event, window);
        gameOverButton->handleEvent(*event, window);
    }
    window.draw(title);
    explorationButton->draw(window);
    gameOverButton->draw(window);
}