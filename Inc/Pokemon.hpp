#pragma once

#include <string>

using std::string;

class Pokemon {
    private:
        int id;
        string name;
        double hitPoint;
        double attack;
        double defense;
        int generation;
        static int countPokemon;

    public:
        Pokemon(int id, string name, double hitPoint, double attack, double defense, int generation);
        Pokemon(const Pokemon &anotherPokemon);
        ~Pokemon();
        void displayInfo() const;

        int getId() const;
        string getName() const;
        double getHitPoint();
        double getAttack();
        double getDefense();
        int getGeneration();
        static int getCount();

        bool attackPokemon(Pokemon &target);
        void damagePokemon(Pokemon, double damage);

};