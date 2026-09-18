#pragma once

#include "SetOfPokemon.hpp"

class Pokedex : public SetOfPokemon {
    private:
        Pokedex(string fileName);
        static Pokedex *instance;
    public:
        static Pokedex *getInstance();
        Pokemon getById(int index) override;
        Pokemon getByName(string name) override;
        
};