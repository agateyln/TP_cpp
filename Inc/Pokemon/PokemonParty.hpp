#pragma once

#include "SetOfPokemon.hpp"

class PokemonParty : public SetOfPokemon {
    public:
        PokemonParty(); 
        ~PokemonParty();
        Pokemon getById(int index) override;
        Pokemon getByName(string name) override;
        void addPokemonToParty(const Pokemon& pokemon);
        void removePokemonFromParty(const Pokemon& pokemon);
};