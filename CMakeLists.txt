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

find_package(SFML 3 CONFIG QUIET COMPONENTS Graphics Audio Window System)

if(NOT SFML_FOUND)
    include(FetchContent)

    message(STATUS "SFML 3 not found locally; fetching SFML 3.0.2 from GitHub")
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW TRUE
    )

    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Disable SFML examples" FORCE)
    set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "Disable SFML tests" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "Disable SFML documentation" FORCE)
    FetchContent_MakeAvailable(SFML)
endif()

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

# Keep runtime resources beside the build tree so the executable can be
# launched from build/ without depending on the source tree layout.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Res
        ${CMAKE_BINARY_DIR}/Res
)