#include "SetOfPokemon.hpp"
#include <iostream>

void SetOfPokemon::displayListPokemon(int number) {
    for (int i=0;i<number;i++) {
        std::cout<<arrayOfPokemon.at(i).getId()<<" / "<<arrayOfPokemon.at(i).getName()<<std::endl;
    }
}
