#include "PokemonAttack.hpp"
#include <iostream>
#include <stdexcept>

PokemonAttack::PokemonAttack() {
}

PokemonAttack::~PokemonAttack() {
}

Pokemon PokemonAttack::getById(int index) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getId() == index) {
            return Pokemon(pokemon);
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

Pokemon PokemonAttack::getByName(string name) {
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getName() == name) {
            return Pokemon(pokemon);  
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

// Add a Pokemon from the party to the attack list and remove it from the party
void PokemonAttack::addPokemonToAttackFromParty(PokemonParty& party, const Pokemon& pokemon) { 
    if (arrayOfPokemon.size() >= MAX_ATTACK_POKEMON) {
        throw std::runtime_error("Attack list is full.");
    }
    arrayOfPokemon.push_back(pokemon);
    party.removePokemonFromParty(pokemon); 
}

// Remove a Pokemon from the attack list and add it back to the party
void PokemonAttack::removePokemonFromAttackToParty(PokemonParty& party, const Pokemon& pokemon) {
    for (auto it=arrayOfPokemon.begin(); it!=arrayOfPokemon.end();) {
        if (it->getName()==pokemon.getName()) {
            it=arrayOfPokemon.erase(it);
            party.addPokemonToParty(pokemon);
        } else {
            ++it;
        }
    }
}