#pragma once

#include "SetOfPokemon.hpp"

class Pokedex : public SetOfPokemon {
    private:
        Pokedex(string fileName);
        static Pokedex *instance;
    public:
        static Pokedex *getInstance(string fileName);
        Pokemon getByIndex(int index) override;
        Pokemon getByName(string name) override;
        
};