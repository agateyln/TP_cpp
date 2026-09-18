#include "Pokemon.hpp"
#include <iostream>

int Pokemon::countPokemon=0;

Pokemon::Pokemon(int id, string name, double hitPoint, double attack, double defense, int generation) {
    this->id=id;
    this->name=name;
    this->hitPoint=hitPoint;
    this->attack=attack;
    this->defense=defense;
    this->generation=generation;   
    countPokemon++; 
}

Pokemon::Pokemon(const Pokemon &anotherPokemon) {
    id=anotherPokemon.id;
    name=anotherPokemon.name;
    hitPoint=anotherPokemon.hitPoint;
    attack=anotherPokemon.attack;
    defense=anotherPokemon.defense;
    generation=anotherPokemon.generation;
    countPokemon++;
}

Pokemon::~Pokemon() {
    //std::cout<<"Destructeur du pokemon "<<name<<std::endl;
    countPokemon--;
}

void Pokemon::displayInfo() const {
    std::cout<<"Id: "<<id<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Hit Point: "<<hitPoint<<std::endl;
    std::cout<<"Attack: "<<attack<<std::endl;
    std::cout<<"Defense: "<<defense<<std::endl;
    std::cout<<"Generation: "<<generation<<std::endl;
}

int Pokemon::getId() const {
    return id;
}

string Pokemon::getName() const {
    return name;
}

double Pokemon::getHitPoint() {
    return hitPoint;
}

double Pokemon::getAttack() {
    return attack;
}

double Pokemon::getDefense() {
    return defense;
}
int Pokemon::getGeneration() {
    return generation;
}

bool Pokemon::attackPokemon(Pokemon &target) {
    if (target.hitPoint <=0) {
        return false;
    }
    else if (attack > target.defense) {
        return true;
    } 
    else {
        return false;
    }
}

void Pokemon::damagePokemon(double damage) {
    hitPoint -= damage;
    if (hitPoint < 0) {
        hitPoint = 0;
    }
}

int Pokemon::getCount() {
    return countPokemon;
}

bool Pokemon::isSleeping(){
    return hitPoint <= 0;
}