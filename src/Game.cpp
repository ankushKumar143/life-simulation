#include "Game.h"
#include "Grid.h"

Game::Game()
    : window(
          sf::VideoMode({800, 600}),
          "Life Simulation")
{
    tile.setSize({TILE_SIZE - 1, TILE_SIZE - 1});
    tile.setFillColor(sf::Color::White);

    grid.setAlive(10, 10);
    grid.setAlive(10, 11);
    grid.setAlive(10, 12);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Game::update()
{
    if (clock.getElapsedTime().asMilliseconds() >= 300)
    {
        grid.update();
        clock.restart();
    }
}

void Game::render()
{
    window.clear();
    for (int i = 0; i < grid.getSize(); i++)
    {
        for (int j = 0; j < grid.getSize(); j++)
        {
            if (grid.isAlive(i, j))
            {
                tile.setPosition({j * TILE_SIZE, i * TILE_SIZE});
                window.draw(tile);
            }
        }
    }
    window.display();
}