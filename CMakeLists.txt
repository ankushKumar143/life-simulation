cmake_minimum_required(VERSION 3.20)

project(LifeSimulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(LifeSimulation
    src/main.cpp
    src/Game.cpp
)

target_include_directories(LifeSimulation PRIVATE include)

target_link_libraries(LifeSimulation
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_compile_options(LifeSimulation PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)