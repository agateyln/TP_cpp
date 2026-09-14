#pragma once

#include "SetOfPokemon.hpp"


class PokemonParty : public SetOfPokemon {
    public:
        PokemonParty(); 
        Pokemon getByIndex(int index) override;
        Pokemon getByName(string name) override;
};