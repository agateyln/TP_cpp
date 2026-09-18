## I - Code Review

### Structure du code

- La classe Pokemon_Attack peut être renommé en PokemonAttack pour suivre la nomenclature des autres classes
- Tu peux faire une description de chaque classe en debut des fichiers .hpp
- Redondance da la fonction getByName et getByIndex, il y a moyen d'alléger le code
- une fois tu mets getByIndex () et une autre getId (harmonisation possible)

### Main.cpp

- Je connaissais pas le Pokedec ;) (l9)
- Un petit peu de français, c'est glissé ("Combat") (Mais je comprends, je fais pareil). (En vrai, Je laisse le bénéfice du doute, car Combat peut se traduire par combat en langage formel) ;)

### Pokedex.hpp

- Pour le Pokedex, il faudrait faire un getInstance sans paramètre pour alléger le code 

### Pokemon_Attack.cpp 

- Tu crées une copie du pokémon dans les méthodes getByIndex et getByName alors qu'il faudrait plus donner la référence

### Pokemon.cpp

- Pokemon::damagePokemon demande un Pokemon en paramètre mais ne l'utilise pas

### SetOfPokemon.cpp

- SetOfPokemon::displayListPokemon il y a problème si number > à la taille de liste

## II - Proposition de méthode 

Je propose de rajouter une méthode pour savoir si le pokémon dort. Elle permettra une lecture plus claire dans le code.

    bool Pokemon::isSleeping(){
        return hitPoint <= 0;
    }
