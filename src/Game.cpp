#include <iostream>
#include "Game.hpp"
#include "fonts/Roboto-Regular.hpp"

void Game::initVariables() {
    this->window = nullptr;
    sf::Font font;
    if (!font.loadFromMemory(Roboto, sizeof Roboto)) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    this->button.setFont(font);
    this->button.setPosition({100.f, 100.f});

}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "SFML with C++");
}

Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    delete this->window;
}

bool Game::running() const {
    return this->window->isOpen();
}


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
            default:
                break;
        }
    }
}

void Game::update() {
    this->pollEvents();
}
