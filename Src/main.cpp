#include "Pokedex.hpp"
#include "PokemonParty.hpp"
#include "Pokemon_Attack.hpp"
#include <iostream>


int main() {

    // POKEDEC
    std::cout<<"5 premiers Pokemons du Pokedex"<<std::endl;
    Pokedex* pokedex = Pokedex::getInstance("../Res/pokedex.csv");
    pokedex->displayListPokemon(5);
    
    // POKEMON PARTY
    std::cout<<"\nPokemon Party"<<std::endl;
    PokemonParty party;
    party.addPokemonToParty(pokedex->getByName("Bulbasaur"));
    party.addPokemonToParty(pokedex->getByName("Charizard"));
    party.addPokemonToParty(pokedex->getByName("Squirtle"));
    party.displayListPokemon(3);

    // POKEMON ATTACK
    std::cout<<"\nPokemon Attack"<<std::endl;
    Pokemon_Attack attackList;
    attackList.addPokemonToAttackFromParty(party, party.getByName("Bulbasaur"));
    attackList.addPokemonToAttackFromParty(party, party.getByName("Charizard"));
    attackList.displayListPokemon(2);

    std::cout << "\nParty after selecting the attack team:\n";
    party.displayListPokemon(1);

    // COMBAT
    std::cout<<"\nCombat!"<<std::endl;
    Pokemon attacker = attackList.getByName("Charizard");
    Pokemon defender = attackList.getByName("Bulbasaur");

    std::cout << attacker.getName() << " attacks " << defender.getName() << ".\n";
    while (attacker.attackPokemon(defender)) {
        std::cout<<attacker.getName()<<" deals "<<attacker.getAttack()-defender.getDefense()<<" damage to "<<defender.getName()<<std::endl;
        defender.damagePokemon(defender, attacker.getAttack() - defender.getDefense());
        std::cout<<defender.getName()<<" has "<<defender.getHitPoint()<<" HP left."<<std::endl;
    }
    if (defender.getHitPoint()<=0) {
        std::cout<<defender.getName()<<" is sleeping."<<std::endl;
    }

    // RETURN POKEMONS TO PARTY
    std::cout<<"\nCombat ended. Pokemons return to their party."<<std::endl;
    attackList.removePokemonFromAttackToParty(party,attacker);
    attackList.removePokemonFromAttackToParty(party,defender);
    std::cout<<"\nParty after combat"<<std::endl;
    party.displayListPokemon(3);
    
    return 0;
}







// Test code for SFML
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