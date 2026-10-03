#include "Pokemon/PokemonParty.hpp"
#include "Pokemon/SetOfPokemon.hpp"
#include "Pokemon/Pokedex.hpp"
#include <iostream>
#include <vector>

PokemonParty::PokemonParty():SetOfPokemon() { 
	//std::cout<<"*** Constructeur du PokemonParty ***"<<std::endl;
	arrayOfPokemon = std::vector<Pokemon>();
}

PokemonParty::~PokemonParty() {
	arrayOfPokemon.clear();
}

Pokemon PokemonParty::getById(int index) {
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

// for each Pokemon in the party, set its hitPoint to its original value (the one it had when it was created from the Pokedex)
void PokemonParty::healAllPokemon() {
    for (Pokemon& pokemon : arrayOfPokemon) {
        // get the original hitPoint of the Pokemon from the Pokedex and set it to the current hitPoint of the Pokemon in the party
        double originalHitPoint = Pokedex::getInstance().getByName(pokemon.getName()).getHitPoint();
        pokemon.damagePokemon(-originalHitPoint + pokemon.getHitPoint());
    }
}