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
    Src/Pokemon.cpp
    Src/SetOfPokemon.cpp
    Src/Pokedex.cpp
    Src/PokemonParty.cpp
    Src/Pokemon_Attack.cpp
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