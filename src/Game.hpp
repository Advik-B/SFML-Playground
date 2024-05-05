#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    void initVariables();
    void initWindow();
    UI::Button button;
public:
    sf::Event ev;

    Game();
    virtual ~Game();

    [[nodiscard]] bool running() const;
    void pollEvents();
    void update();
    void render();
};

