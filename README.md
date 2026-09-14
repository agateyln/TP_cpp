# TP Introduction C++ 

## Objectif

Ce projet d'introduction au C++ a pour but de se familiariser avec les différentes notions de base de ce langage. Il contient les premiers éléments pour créer une version simplifiée d'un jeu de Pokemon. 


## Classes
Pour l'instant, ce projet est constitué de 5 classes.  

- **`Pokemon`**
    - Représente un Pokemon
    - Contient son id, son nom, ses points de vie, son attaque, sa défense et sa génération
    - Peut attaquer un autre Pokemon et lui infliger des dégâts

- **`SetOfPokemon`** 
    - Classe mère abstraite
    - Contient une liste de `Pokemon`
    - Définit les méthodes de recherche par id et par nom
    - Définit une méthode pour afficher la liste

- **`Pokedex`** 
    - Hérite de `SetOfPokemon`
    - Charge les Pokemons depuis un fichier CSV
    - Utilise le design pattern Singleton
    
- **`PokemonParty`** 
    - Hérite de `SetOfPokemon`
    - Représente l'ensemble des Pokemons du joueur
    - Permet d'ajouter ou de retirer des Pokemons

- **`Pokemon_Attack`** 
    - Hérite de `SetOfPokemon`
    - Représente la liste des Pokemons utilisés pour une attaque
    - Peut contenir au maximum 6 Pokemons
    - Permet de transférer des Pokémons depuis ou vers l'équipe du joueur



## Installations requises

- CMake 
- SFML 3


### Si SFML 3 n'est pas installée

SFML n'est pas encore utilisée par le code actuel. Pour compiler le projet sans l'installer, commenter temporairement les deux blocs SFML dans `CMakeLists.txt`.

```cmake
# find_package(SFML 3 COMPONENTS Graphics Audio Window System REQUIRED)
```

Et : 

```cmake
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     SFML::Graphics
#     SFML::Audio
#     SFML::Window
#     SFML::System
# )
```

Ensuite, reconfigurer et compiler :

```bash
cmake -S . -B build
cmake --build build --target Pokemon
```


## Compiler et lancer le projet

Les commandes doivent être exécutées depuis la racine du projet.

### macOS/Linux

```bash
cmake -S . -B build
cmake --build build --target Pokemon
cd build
./Pokemon
```

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Debug --target Pokemon
cd build
.\Debug\Pokemon.exe
```