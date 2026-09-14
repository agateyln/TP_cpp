#include "Pokemon_Attack.hpp"
#include <iostream>
#include <stdexcept>

Pokemon_Attack::Pokemon_Attack() {
}

Pokemon_Attack::~Pokemon_Attack() {
}

Pokemon Pokemon_Attack::getByIndex(int index) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getId() == index) {
            return Pokemon(pokemon);
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

Pokemon Pokemon_Attack::getByName(string name) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getName() == name) {
            return Pokemon(pokemon);  
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

void Pokemon_Attack::addPokemonToAttackFromParty(PokemonParty& party, const Pokemon& pokemon) {
    if (arrayOfPokemon.size() >= MAX_ATTACK_POKEMON) {
        throw std::runtime_error("Attack list is full.");
    }
    arrayOfPokemon.push_back(pokemon);
    party.removePokemonFromParty(pokemon); 
}

void Pokemon_Attack::removePokemonFromAttackToParty(PokemonParty& party, const Pokemon& pokemon) {
    for (auto it=arrayOfPokemon.begin(); it!=arrayOfPokemon.end();) {
        if (it->getName()==pokemon.getName()) {
            it=arrayOfPokemon.erase(it);
            party.addPokemonToParty(pokemon);
        } else {
            ++it;
        }
    }
}