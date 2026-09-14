#include "PokemonParty.hpp"
#include "SetOfPokemon.hpp"
#include <iostream>
#include <vector>

PokemonParty::PokemonParty():SetOfPokemon() { 
	std::cout<<"*** Constructeur du PokemonParty ***"<<std::endl;
	arrayOfPokemon = std::vector<Pokemon>();
}

