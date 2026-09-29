#include "Pokemon/Pokedex.hpp"
#include "Pokemon/PokemonParty.hpp"
#include "Pokemon/PokemonAttack.hpp"

class Game { 
    private:
        Pokedex& pokedex;
        PokemonParty party;
        PokemonAttack attackList;
    public:
        Game();
        ~Game() = default;
        void run();
        PokemonParty& getParty();
        PokemonAttack& getAttackList();
        const PokemonAttack& getAttackList() const;
        Pokedex& getPokedex();
};