#include <iostream>
#include <SFML/Graphics.hpp>

struct PlayerMovement
{
    bool up, down, left, right;
};

class Game
{
public:
    Game();
    int run();
private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    PlayerMovement mPlayerMovement;
    float mPlayerSpeed;
    sf::Clock mClock;
};

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application")
    , mPlayer(10.f)
    , mPlayerMovement({false, false, false, false})
    , mPlayerSpeed(100.f)
    , mClock()
{
    mPlayer.setFillColor(sf::Color::Cyan);
    mPlayer.setPosition(100.f, 100.f);
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update()
{
    sf::Vector2f movement(0.f, 0.f);
    if (mPlayerMovement.left)
        movement.x -= mPlayerSpeed;
    if (mPlayerMovement.right)
        movement.x += mPlayerSpeed;
    if (mPlayerMovement.up)
        movement.y -= mPlayerSpeed;
    if (mPlayerMovement.down)
        movement.y += mPlayerSpeed;

    mPlayer.move(movement * mClock.restart().asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        mPlayerMovement.up = isPressed;
    else if (key == sf::Keyboard::S)
        mPlayerMovement.down = isPressed;
    else if (key == sf::Keyboard::A)
        mPlayerMovement.left = isPressed;
    else if (key == sf::Keyboard::D)
        mPlayerMovement.right = isPressed;
}

int Game::run()
{
    mClock.restart();
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }

    return 0;
}

int main()
{
    Game game;
    return game.run();
}