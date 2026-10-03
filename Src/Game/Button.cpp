#include "Game/Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font, std::function<void()> callback) :
    text(font, text, 20),
    callback(callback) {
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(sf::Color(74, 74, 158));
        this->text.setString(text);
        this->text.setCharacterSize(20);
        this->text.setFillColor(sf::Color::White);
        // center the text in the button
        sf::FloatRect textBounds=this->text.getLocalBounds();
        this->text.setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                              textBounds.position.y + textBounds.size.y / 2.0f});
        this->text.setPosition({position.x + size.x / 2.0f,
                                 position.y + size.y / 2.0f});
    }

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}


void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            
            if (shape.getGlobalBounds().contains(mousePos)) {
                callback();
            }
        }
    }
    auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    if (shape.getGlobalBounds().contains(mousePos)) {
        shape.setFillColor(sf::Color(113, 113, 192));
    } else {
        shape.setFillColor(sf::Color(74, 74, 158));
    }
    
}