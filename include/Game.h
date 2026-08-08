#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <optional>
#include <string>

class Game
{
public:
    Game();

    void run();

private:
    static constexpr float WINDOW_WIDTH = 1000.f;
    static constexpr float WINDOW_HEIGHT = 650.f;
    static constexpr float SIDEBAR_WIDTH = 300.f;
    static constexpr float TILE_WIDTH = 28.f;
    static constexpr float TILE_HEIGHT = 26.f;

    void processEvents();
    void update();
    void render();
    void createButtons();

    sf::RenderWindow window;
    sf::RectangleShape tile;
    sf::RectangleShape sidebar;
    sf::RectangleShape separator;
    sf::Clock clock;
    sf::Font font;
    std::optional<sf::Text> title;

    int generation = 0;
    Pattern currentPattern = Pattern::Blinker;

    std::optional<sf::Text> statusText;
    std::optional<sf::Text> patternText;
    std::optional<sf::Text> generationText;
    std::optional<sf::Text> aliveText;
    std::vector<sf::RectangleShape> buttons;
    std::vector<std::optional<sf::Text>> buttonTexts;
    std::string getPatternName(Pattern pattern) const;

    Grid grid;

    bool paused = false;
    bool mousePressed = false;
};