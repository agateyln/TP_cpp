cmake_minimum_required(VERSION 3.21)
project(Pokemon
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 COMPONENTS Graphics Audio Window System REQUIRED)

# --- Fichiers sources ---
set(SOURCES
    Src/main.cpp
    Src/Game/Game.cpp
    Src/Game/GameEngine.cpp
    Src/Game/Button.cpp
    Src/Pokemon/Pokemon.cpp
    Src/Pokemon/SetOfPokemon.cpp
    Src/Pokemon/Pokedex.cpp
    Src/Pokemon/PokemonParty.cpp
    Src/Pokemon/PokemonAttack.cpp
    Src/States/WelcomeState.cpp
    Src/States/ExplorationState.cpp
    Src/States/EncounterState.cpp
    Src/States/CombatState.cpp
    Src/States/GameOverState.cpp
    Src/States/CaptureState.cpp
    Src/States/MenuState.cpp
)

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Audio
    SFML::Window
    SFML::System
)

# --- Dossier des headers ---
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Inc
)