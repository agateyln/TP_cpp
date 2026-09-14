#include "Pokedex.hpp"
#include "PokemonParty.hpp"
#include "Pokemon_Attack.hpp"
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


/*/*
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

int main() {
    // Test Pokedex
    Pokedex* pokedex = Pokedex::getInstance("../Res/pokedex.csv");
    pokedex->displayListPokemon(5);
  
    
    PokemonParty party;
    party.addPokemonToParty(pokedex->getByIndex(1));
    party.addPokemonToParty(pokedex->getByName("Ivysaur"));
    std::cout<<"Party List"<<std::endl;
    party.displayListPokemon(2);
    party.removePokemonFromParty(pokedex->getByIndex(2));
    std::cout<<"Party list after removing a pokemon"<<std::endl;
    party.displayListPokemon(1);
    party.addPokemonToParty(pokedex->getByIndex(2));
    party.addPokemonToParty(pokedex->getByIndex(3));
    party.addPokemonToParty(pokedex->getByIndex(4));
    party.addPokemonToParty(pokedex->getByIndex(5));
    std::cout<<"Party list after adding more pokemons"<<std::endl;
    party.displayListPokemon(5);
    std::cout<<"Pokedex list after adding pokemons to party"<<std::endl;
    pokedex->displayListPokemon(5);

    Pokemon_Attack attackList;
    attackList.addPokemonToAttackFromParty(party, party.getByIndex(1));
    attackList.addPokemonToAttackFromParty(party, party.getByIndex(2));
    attackList.addPokemonToAttackFromParty(party, party.getByIndex(3));
    std::cout<<"Attack List"<<std::endl;
    attackList.displayListPokemon(3);
    std::cout<<"Party list after adding pokemons to attack list"<<std::endl;
    party.displayListPokemon(2);
    attackList.removePokemonFromAttackToParty(party, attackList.getByIndex(1));
    std::cout<<"Attack list after returning a pokemon to party list"<<std::endl;
    attackList.displayListPokemon(2);
    std::cout<<"Party list after returning a pokemon from attack list"<<std::endl;
    party.displayListPokemon(3);


    return 0;
}