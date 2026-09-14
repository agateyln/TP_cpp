#pragma once

#include "SetOfPokemon.hpp"

class Pokemon_Attack : public SetOfPokemon {
    public:
        Pokemon_Attack();
        Pokemon getByIndex(int index) override;
        Pokemon getByName(string name) override;     
};