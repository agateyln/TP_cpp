#include "Pokedex.hpp"
#include <iostream>
//#include "Pokemon.hpp"

/*
int main() {
    std::cout<<"Hello world"<<std::endl;
}
*/

/*
int main() {
    Pokemon pokemon1(1,"num1",100,60,55,1);
    Pokemon pokemon2(2,"num2",50,50,30,1);
    Pokemon pokemon3(3,"num3",80,50,30,1);

    pokemon1.displayInfo();
    pokemon2.displayInfo();
    pokemon3.displayInfo();

    std::cout<<"Number of Pokemon: "<<Pokemon::getCount()<<std::endl;

    // Test the copy constructor
    Pokemon pokemon4(pokemon2);
    pokemon2.displayInfo();
    pokemon4.displayInfo();

    // Test the attack method
    pokemon1.attackPokemon(pokemon2);
    pokemon2.displayInfo();
    pokemon1.attackPokemon(pokemon2);
    pokemon2.displayInfo();

    pokemon3.attackPokemon(pokemon1);
    pokemon1.displayInfo();

    // Test 
    
    return 0;
}
    */


/*
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hello SFML");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
return 0;
}
*/


// Test Pokedex

int main() {
    Pokedex* pokedex = Pokedex::getInstance("../Res/pokedex.csv");
    pokedex->displayListPokemon(5);
    return 0;
}