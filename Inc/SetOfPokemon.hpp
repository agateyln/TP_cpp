#pragma once
#include <string>
#include "Pokemon.hpp"
#include <vector>

using std::string;

class SetOfPokemon {
    protected:
        std::vector<Pokemon> arrayOfPokemon;
    public:
        virtual ~SetOfPokemon() {};
        virtual Pokemon getById(int index) = 0;
        virtual Pokemon getByName(string name) = 0;
        void displayListPokemon(int number);
};