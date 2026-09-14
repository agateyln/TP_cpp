#pragma once

#include "SetOfPokemon.hpp"
#include "PokemonParty.hpp"
#include <cstddef>

class Pokemon_Attack : public SetOfPokemon {
    public:
        const std::size_t MAX_ATTACK_POKEMON = 6;
        Pokemon_Attack();
        ~Pokemon_Attack();
        Pokemon getByIndex(int index) override;
        Pokemon getByName(string name) override;
        void addPokemonToAttackFromParty(PokemonParty& party, const Pokemon& pokemon);
        void removePokemonFromAttackToParty(PokemonParty& party, const Pokemon& pokemon);
};