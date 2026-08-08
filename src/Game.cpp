#include "Game.h"
#include "Grid.h"
#include "Pattern.h"
#include <stdexcept>
#include <string>

Game::Game()
    : window(
          sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT)}),
          "Life Simulation")
{
    tile.setSize({TILE_SIZE - 1, TILE_SIZE - 1});
    tile.setFillColor(sf::Color::White);

    sidebar.setSize({SIDEBAR_WIDTH, WINDOW_HEIGHT});
    sidebar.setPosition({WINDOW_WIDTH - SIDEBAR_WIDTH, 0.f});
    sidebar.setFillColor(sf::Color(30, 30, 30));

    separator.setSize({2.f, WINDOW_HEIGHT});
    separator.setPosition({WINDOW_WIDTH - SIDEBAR_WIDTH, 0.f});
    separator.setFillColor(sf::Color(180, 180, 180));

    if (!font.openFromFile("assets/PixelifySans-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    title.emplace(font);
    title->setString("Life Simulation");
    title->setCharacterSize(28);
    title->setFillColor(sf::Color::White);
    title->setPosition({720.f, 20.f});

    statusText.emplace(font);
    patternText.emplace(font);
    generationText.emplace(font);
    aliveText.emplace(font);

    statusText->setCharacterSize(22);
    patternText->setCharacterSize(22);
    generationText->setCharacterSize(22);
    aliveText->setCharacterSize(22);

    statusText->setFillColor(sf::Color::White);
    patternText->setFillColor(sf::Color::White);
    generationText->setFillColor(sf::Color::White);
    aliveText->setFillColor(sf::Color::White);

    statusText->setPosition({720.f, 80.f});
    patternText->setPosition({720.f, 115.f});
    generationText->setPosition({720.f, 150.f});
    aliveText->setPosition({720.f, 185.f});

    patternText->setString("Pattern: Blinker");

    grid.loadPattern(Pattern::Blinker);
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

        if (const auto *key = event->getIf<sf::Event::KeyPressed>())
        {
            switch (key->scancode)
            {
            case sf::Keyboard::Scancode::Space:
                paused = !paused;
                break;

            case sf::Keyboard::Scancode::Num1:
                grid.loadPattern(Pattern::Blinker);
                paused = true;
                break;

            case sf::Keyboard::Scancode::Num2:
                grid.loadPattern(Pattern::Glider);
                paused = true;
                break;

            case sf::Keyboard::Scancode::Num3:
                grid.loadPattern(Pattern::Beacon);
                paused = true;
                break;

            case sf::Keyboard::Scancode::Num4:
                grid.loadPattern(Pattern::Toad);
                paused = true;
                break;

            case sf::Keyboard::Scancode::Num5:
                grid.loadPattern(Pattern::Random);
                paused = true;
                break;

            case sf::Keyboard::Scancode::R:
                grid.clear();
                paused = true;
                break;

            default:
                break;
            }
        }

        if (const auto *mouse =
                event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                int col = mouse->position.x / TILE_SIZE;
                int row = mouse->position.y / TILE_SIZE;

                if (row >= 0 && row < grid.getSize() &&
                    col >= 0 && col < grid.getSize())
                {
                    grid.toggleCell(row, col);
                }
            }
        }
    }
}

void Game::update()
{
    if (paused)
    {
        return;
    }
    if (clock.getElapsedTime().asMilliseconds() >= 300)
    {
        grid.update();
        generation++;
        clock.restart();
    }
}

void Game::render()
{
    window.clear();
    window.draw(sidebar);
    window.draw(separator);
    window.draw(*title);
    statusText->setString(
        paused ? "Status: PAUSED" : "Status: RUNNING");

    generationText->setString(
        "Generation: " + std::to_string(generation));

    aliveText->setString(
        "Alive Cells: " + std::to_string(grid.countAliveCells()));

    window.draw(*statusText);
    window.draw(*patternText);
    window.draw(*generationText);
    window.draw(*aliveText);
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