#include "PokemonParty.hpp"
#include "SetOfPokemon.hpp"
#include <iostream>
#include <vector>

PokemonParty::PokemonParty():SetOfPokemon() { 
	//std::cout<<"*** Constructeur du PokemonParty ***"<<std::endl;
	arrayOfPokemon = std::vector<Pokemon>();
}

PokemonParty::~PokemonParty() {
	arrayOfPokemon.clear();
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

void PokemonParty::addPokemonToParty(const Pokemon& pokemon) {
    arrayOfPokemon.push_back(pokemon);
}


void PokemonParty::removePokemonFromParty(const Pokemon& pokemon) {
    for (auto it=arrayOfPokemon.begin(); it!=arrayOfPokemon.end();) {
        if (it->getName()==pokemon.getName()) {
            it=arrayOfPokemon.erase(it);
        } else {
            ++it;
        }
    }
}