#pragma once
#include <SFML/Graphics.hpp>
#include <functional> 

class Button {
    private:
        sf::RectangleShape shape;
        sf::Text text;
        std::function<void()> callback;
    public:
        Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font, std::function<void()> callback);
        void draw(sf::RenderWindow& window); 
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
};
