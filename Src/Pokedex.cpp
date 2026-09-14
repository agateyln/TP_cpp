#include "Pokedex.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

Pokedex* Pokedex::instance = nullptr;

Pokedex* Pokedex::getInstance(string fileName) {
    if (instance == nullptr) {
        instance = new Pokedex(fileName);
    }
    return instance;
}

Pokedex::Pokedex(string fileName):SetOfPokemon() { 

    //std::cout << "*** Constructeur du Pokedex ***" << std::endl;

    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cerr<<"File "<<fileName<<" not found "<<std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
    //    std::cout << line << std::endl;
        std::stringstream inputstringstream(line);
        std::string cell;
        std::vector<std::string> lineData;

        while(std::getline(inputstringstream,cell,',')){
            lineData.push_back(cell);
        }
        int id = std::stoi(lineData.at(0));
        double attackValue = std::stod(lineData.at(6));
        double hitPoint = std::stod(lineData.at(5));
        double defenseValue = std::stod(lineData.at(7));
        int generation = std::stoi(lineData.at(11));

        
        arrayOfPokemon.push_back(Pokemon(id, lineData.at(1), hitPoint, attackValue,
                         defenseValue, generation));
        
       //addPokemon(Pokemon(id, lineData.at(1), hitPoint, attackValue, defenseValue, generation));
    }
}

Pokemon Pokedex::getByIndex(int index) { // Returns a copy of the Pokemon with the given index
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getId() == index) {
            return Pokemon(pokemon);
        }
    }
    throw std::invalid_argument("Pokemon not found");
}

Pokemon Pokedex::getByName(string name) { // Returns a copy of the Pokemon with the given name
    for (Pokemon& pokemon : arrayOfPokemon) {
        if (pokemon.getName() == name) {
            return Pokemon(pokemon);  
        }
    }
    throw std::invalid_argument("Pokemon not found");
}
