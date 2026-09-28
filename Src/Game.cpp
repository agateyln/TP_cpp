#include <iostream>
#include "Game.hpp"
#include "GameEngine.hpp"
#include "States/WelcomeState.hpp"
#include "States/ExplorationState.hpp"

Game::Game() 
    : pokedex(Pokedex::getInstance()),
      party(),
      attackList() {
}

void Game::run() {
    GameEngine engine;
    engine.setState(std::make_unique<WelcomeState>(engine, *this));
    engine.run();
}

PokemonParty& Game::getParty() {
    return party;
}

PokemonAttack& Game::getAttackList() {
    return attackList;
}

const PokemonAttack& Game::getAttackList() const {
    return attackList;
}

Pokedex& Game::getPokedex() {
    return pokedex;
}