#include "Game.hpp"
#include <iostream>
#include "fonts/Roboto-Regular.hpp"

#include "icecream.hpp"

#include "UI.cpp"

void Game::initVariables() {
    this->window = nullptr;
    this->currentGrab = new sf::Texture();
    sf::Font font;
    if (!font.loadFromMemory(Roboto, sizeof Roboto / sizeof Roboto[0])) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    this->button.setFont(font);
    this->button.setPosition({100.f, 100.f});
    this->button.setString("This is a button!");
    this->button.setSize({200.f, 100.f});
    this->button.setOutlineThickness(2.f);
    this->button.setFontSize(20.f);
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "SFML with C++");
    this->window->setVerticalSyncEnabled(true);
}
void Game::takeScreenshot() const {
    this->currentGrab->create(this->window->getSize().x, this->window->getSize().y);
    this->currentGrab->update(*this->window);
}

Game::Game() {
    initVariables();
    initWindow(); // why not initVariables() first?
}

Game::~Game() { delete this->window; }

bool Game::running() const { return this->window->isOpen(); }


void Game::render() {
    this->window->clear({37, 150, 190});

    this->button.render_to(*this->window);

    this->window->display();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
            case sf::Event::Resized:
                this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, ev.size.width, ev.size.height)));
                break;
            case sf::Event::MouseMoved:
                this->button.update(sf::Mouse::getPosition(*this->window), *this->window);
                break;
            case sf::Event::MouseButtonPressed:
                if (this->button.isPressed(ev)) {
                    IC();
                }
                break;
            default:
                break;
        }
    }
}

void Game::update() {
    this->clock.restart();
    this->pollEvents();
    this->takeScreenshot();
    this->button.setTexture(currentGrab);
}
