#ifndef GAME_HPP
#define GAME_HPP
#endif

#include <SFML/Graphics.hpp>
#include "UI.hpp"

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    UI::Button button;
    sf::Clock clock;
    sf::Texture* currentGrab;

    void initVariables();
    void initWindow();
    void takeScreenshot() const;
public:
    sf::Event ev;

    Game();
    virtual ~Game();

    [[nodiscard]] bool running() const;
    void pollEvents();
    void update();
    void render();
};

