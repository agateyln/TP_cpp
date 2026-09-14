#include "Pokemon_Attack.hpp"
#include <iostream>

Pokemon_Attack::Pokemon_Attack() {}

Pokemon Pokemon_Attack::getByIndex(int index) {
    auto iterator = arrayOfPokemon.begin() + index - 1;
    Pokemon pokemon = *iterator;
    arrayOfPokemon.erase(iterator);
    return pokemon;
}

Pokemon Pokemon_Attack::getByName(string name) {
    for (auto iterator = arrayOfPokemon.begin(); iterator != arrayOfPokemon.end(); ++iterator) {
        if (iterator->getName() == name) {
            Pokemon pokemon = *iterator;
            arrayOfPokemon.erase(iterator);
            return pokemon;
        }
    }
}