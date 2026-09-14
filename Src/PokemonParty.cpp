#include "PokemonParty.hpp"
#include "SetOfPokemon.hpp"
#include <iostream>
#include <vector>

PokemonParty::PokemonParty():SetOfPokemon() { 
	std::cout<<"*** Constructeur du PokemonParty ***"<<std::endl;
	arrayOfPokemon = std::vector<Pokemon>();
}

Pokemon PokemonParty::getByIndex(int index) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getId() == index) {
            return Pokemon(pokemon);
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

Pokemon PokemonParty::getByName(string name) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getName() == name) {
            return Pokemon(pokemon);  
        }
    }
    throw std::invalid_argument("Pokemon not found");
}