#include "Pokemon/SetOfPokemon.hpp"
#include <iostream>

void SetOfPokemon::displayListPokemon(int number) {
    if (number > static_cast<int>(arrayOfPokemon.size())) {  
        number=arrayOfPokemon.size();
    }
    for (int i=0;i<number;i++) {
        std::cout<<arrayOfPokemon.at(i).getId()<<" / "<<arrayOfPokemon.at(i).getName()<<std::endl;
    }
}

Pokemon SetOfPokemon::getByIndex(std::size_t index) const {
    return arrayOfPokemon.at(index);
}

std::size_t SetOfPokemon::size() const {
    return arrayOfPokemon.size();
}

bool SetOfPokemon::empty() const {
    return arrayOfPokemon.empty();
}
