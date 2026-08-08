#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update();
    void render();
    sf::RenderWindow window;
    sf::RectangleShape tile;
    static constexpr float TILE_SIZE = 20.f;
    static constexpr int GRID_SIZE = 25;
    Grid grid;
    sf::Clock clock;
};