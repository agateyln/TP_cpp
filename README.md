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

Lors de la configuration, CMake cherche d'abord une installation locale. Si SFML 3 n'est pas trouvée, CMake la télécharge automatiquement depuis GitHub. Une connexion Internet est donc nécessaire lors de la première configuration.

Ensuite, reconfigurer et compiler :

```bash
cmake -S . -B build
cmake --build build --target Pokemon --parallel
```


## Compiler et lancer le projet

Les commandes doivent être exécutées depuis la racine du projet.

### macOS/Linux

```bash
cmake -S . -B build
cmake --build build --target Pokemon --parallel
cd build
./Pokemon
```

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Debug --target Pokemon --parallel
cd build
.\Debug\Pokemon.exe
```

Le dossier `Res` est automatiquement copié dans `build/Res` après la compilation. Il faut lancer l'exécutable depuis `build/` (ou depuis `build/Debug/` avec Visual Studio).