#include "Game.h"
#include "Grid.h"
#include "Pattern.h"
#include <stdexcept>
#include <string>
#include <iostream>

Game::Game()
    : window(
          sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH),
                         static_cast<unsigned int>(WINDOW_HEIGHT)}),
          "Life Simulation")
{
    //! Configure the grid tile appearance
    tile.setSize({TILE_WIDTH, TILE_HEIGHT});
    tile.setFillColor(sf::Color::White);

    //! Configure the sidebar
    sidebar.setSize({SIDEBAR_WIDTH, WINDOW_HEIGHT});
    sidebar.setPosition({WINDOW_WIDTH - SIDEBAR_WIDTH, 0.f});
    sidebar.setFillColor(sf::Color(30, 30, 30));

    //! Draw a separator between the grid and sidebar
    separator.setSize({2.f, WINDOW_HEIGHT});
    separator.setPosition({WINDOW_WIDTH - SIDEBAR_WIDTH, 0.f});
    separator.setFillColor(sf::Color(180, 180, 180));

    //! Load the font used by the UI
    if (!font.openFromFile("assets/PixelifySans-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    //! Configure the application title
    title.emplace(font);
    title->setString("Life Simulation");
    title->setCharacterSize(28);
    title->setFillColor(sf::Color::White);
    title->setPosition({720.f, 20.f});

    //! Create the information texts shown in the sidebar
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

    //! Set the position of each information text
    statusText->setPosition({720.f, 80.f});
    patternText->setPosition({720.f, 115.f});
    generationText->setPosition({720.f, 150.f});
    aliveText->setPosition({720.f, 185.f});

    //! Create all UI buttons
    createButtons();

    //! Start the simulation with the Blinker pattern
    grid.loadPattern(Pattern::Blinker);
}

//! Convert a Pattern enum into a readable name for the UI
std::string Game::getPatternName(Pattern pattern) const
{
    switch (pattern)
    {
    case Pattern::Blinker:
        return "Blinker";

    case Pattern::Glider:
        return "Glider";

    case Pattern::Beacon:
        return "Beacon";

    case Pattern::Toad:
        return "Toad";

    case Pattern::Random:
        return "Random";
    }

    return "Unknown";
}

//! Create and configure all sidebar buttons
void Game::createButtons()
{
    const float buttonWidth = 125.f;
    const float fullButtonWidth = 260.f;
    const float buttonHeight = 45.f;
    const float gap = 10.f;

    //! Position buttons inside the sidebar
    const float buttonX = WINDOW_WIDTH - SIDEBAR_WIDTH + 20.f;

    //! Start placing buttons near the bottom of the sidebar
    const float startY = 370.f;

    const std::vector<std::string> labels =
        {
            "Blinker",
            "Glider",
            "Beacon",
            "Toad",
            "Random Pattern",
            "Reset",
            "Pause / Resume",
        };

    //! Create each button and its corresponding text
    for (std::size_t i = 0; i < labels.size(); i++)
    {
        sf::RectangleShape button;

        float x;
        float y;
        float currentWidth;

        //! Arrange the first four pattern buttons in two columns
        if (i < 4)
        {
            int row = i / 2;
            int col = i % 2;

            currentWidth = buttonWidth;

            x = buttonX + col * (buttonWidth + gap);
            y = startY + row * (buttonHeight + gap);
        }
        //! Place the remaining buttons using the full sidebar width
        else
        {
            currentWidth = fullButtonWidth;

            x = buttonX;
            y = startY + 2 * (buttonHeight + gap) + (i - 4) * (buttonHeight + gap);
        }

        button.setSize({currentWidth,
                        buttonHeight});

        button.setPosition({x, y});

        //! Set the default button appearance
        button.setFillColor(sf::Color(30, 30, 30));
        button.setOutlineThickness(2.f);
        button.setOutlineColor(sf::Color(180, 180, 180));

        buttons.push_back(button);

        //! Create the text displayed inside the button
        buttonTexts.emplace_back(font);

        buttonTexts.back()->setString(labels[i]);
        buttonTexts.back()->setCharacterSize(20);
        buttonTexts.back()->setFillColor(sf::Color::White);

        //! Center the button text
        auto bounds = buttonTexts.back()->getLocalBounds();

        buttonTexts.back()->setOrigin({bounds.position.x + bounds.size.x / 2.f,
                                       bounds.position.y + bounds.size.y / 2.f});

        buttonTexts.back()->setPosition({x + currentWidth / 2.f,
                                         y + buttonHeight / 2.f});
    }
}

//! Main game loop
void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

//! Handle keyboard and mouse input
void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        //! Close the application when the window is closed
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        //! Handle keyboard input
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

        //! Handle mouse button clicks
        if (const auto *mouse =
                event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                mousePressed = true;

                sf::Vector2f mousePosition = {
                    static_cast<float>(mouse->position.x),
                    static_cast<float>(mouse->position.y)};

                //! Check whether a sidebar button was clicked
                for (std::size_t i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].getGlobalBounds().contains(mousePosition))
                    {
                        switch (i)
                        {
                        case 0:
                            grid.loadPattern(Pattern::Blinker);
                            currentPattern = Pattern::Blinker;
                            generation = 0;
                            paused = true;
                            break;

                        case 1:
                            grid.loadPattern(Pattern::Glider);
                            currentPattern = Pattern::Glider;
                            generation = 0;
                            paused = true;
                            break;

                        case 2:
                            grid.loadPattern(Pattern::Beacon);
                            currentPattern = Pattern::Beacon;
                            generation = 0;
                            paused = true;
                            break;

                        case 3:
                            grid.loadPattern(Pattern::Toad);
                            currentPattern = Pattern::Toad;
                            generation = 0;
                            paused = true;
                            break;

                        case 4:
                            grid.loadPattern(Pattern::Random);
                            currentPattern = Pattern::Random;
                            generation = 0;
                            paused = true;
                            break;

                        case 5:
                            grid.clear();
                            generation = 0;
                            paused = true;
                            break;

                        case 6:
                            paused = !paused;
                            break;
                        }

                        //! Prevent the same click from being treated as a grid click
                        return;
                    }
                }

                //! Convert the mouse position into a grid cell
                int col = mouse->position.x / TILE_WIDTH;
                int row = mouse->position.y / TILE_HEIGHT;

                //! Toggle the selected cell
                if (row >= 0 && row < grid.getSize() &&
                    col >= 0 && col < grid.getSize())
                {
                    grid.toggleCell(row, col);

                    //! Pause after manual editing
                    generation = 0;
                    paused = true;
                }
            }
        }

        //! Track when the left mouse button is released
        if (const auto *mouse =
                event->getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                mousePressed = false;
            }
        }

        //! Handle mouse movement
        if (const auto *mouse =
                event->getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(mouse->position.x),
                static_cast<float>(mouse->position.y)};

            //! Highlight buttons when the mouse is over them
            for (std::size_t i = 0; i < buttons.size(); i++)
            {
                if (buttons[i].getGlobalBounds().contains(mousePosition))
                {
                    buttons[i].setFillColor(sf::Color(50, 50, 50));
                    buttons[i].setOutlineColor(sf::Color::White);
                }
                else
                {
                    buttons[i].setFillColor(sf::Color(30, 30, 30));
                    buttons[i].setOutlineColor(sf::Color(180, 180, 180));
                }
            }

            //! Draw cells while holding the left mouse button
            if (mousePressed)
            {
                int col = mouse->position.x / TILE_WIDTH;
                int row = mouse->position.y / TILE_HEIGHT;

                if (row >= 0 && row < grid.getSize() &&
                    col >= 0 && col < grid.getSize())
                {
                    grid.setAlive(row, col);
                    paused = true;
                }
            }
        }
    }
}

//! Update the simulation
void Game::update()
{
    //! Do not update the grid while paused
    if (paused)
    {
        return;
    }

    //! Update the simulation every 300 milliseconds
    if (clock.getElapsedTime().asMilliseconds() >= 300)
    {
        grid.update();
        generation++;
        clock.restart();
    }
}

//! Draw the game and UI
void Game::render()
{
    window.clear();

    //! Draw the sidebar and separator
    window.draw(sidebar);
    window.draw(separator);

    //! Draw the title
    window.draw(*title);

    //! Update sidebar information
    statusText->setString(
        paused ? "Status: PAUSED" : "Status: RUNNING");

    generationText->setString(
        "Generation: " + std::to_string(generation));

    aliveText->setString(
        "Alive Cells: " + std::to_string(grid.countAliveCells()));

    patternText->setString(
        "Pattern: " + getPatternName(currentPattern));

    //! Draw sidebar information
    window.draw(*statusText);
    window.draw(*patternText);
    window.draw(*generationText);
    window.draw(*aliveText);

    //! Draw all alive cells
    for (int i = 0; i < grid.getSize(); i++)
    {
        for (int j = 0; j < grid.getSize(); j++)
        {
            if (grid.isAlive(i, j))
            {
                tile.setPosition({j * TILE_WIDTH,
                                  i * TILE_HEIGHT});

                window.draw(tile);
            }
        }
    }

    //! Draw buttons and their text
    for (std::size_t i = 0; i < buttons.size(); i++)
    {
        window.draw(buttons[i]);
        window.draw(*buttonTexts[i]);
    }

    window.display();
}