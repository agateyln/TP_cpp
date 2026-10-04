#include "States/GameOverState.hpp"
#include "Game/GameEngine.hpp"

GameOverState::GameOverState(GameEngine& engine)
        : engine(engine),
            font("../Res/font.otf"),
            title(font, "Game Over", 48),
            message(font, "This path is too intimidating!", 24) {
        title.setPosition({230.f, 180.f});
        message.setPosition({180.f, 280.f});
}

void GameOverState::enter() {
    engine.getWindow().setTitle("Pokemon - Game Over | Fermez la fenetre");
}

void GameOverState::exit() {
}

void GameOverState::update() {
    auto& window = engine.getWindow();
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
    window.draw(title);
    window.draw(message);
}