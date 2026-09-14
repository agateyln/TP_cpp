#include "SetOfPokemon.hpp"
#include <iostream>
#include <vector>

void SetOfPokemon::displayListPokemon(int number) {
    for (int i=0;i<number;i++) {
        std::cout<<arrayOfPokemon.at(i).getId()<<" / "<<arrayOfPokemon.at(i).getName()<<std::endl;
    }
    //for (const Pokemon& pokemon : arrayOfPokemon) {
    //    std::cout<<pokemon.getId()<<" / "<<pokemon.getName()<<std::endl;}
}

void SetOfPokemon::addPokemon(const Pokemon& pokemon) {
    arrayOfPokemon.push_back(pokemon);
}


