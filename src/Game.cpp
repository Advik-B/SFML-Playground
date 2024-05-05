#include <iostream>
#include "Game.hpp"
#include "fonts/Roboto-Regular.hpp"
#include "pratibha.hpp"
#include "icecream.hpp"

void Game::initVariables() {
    this->window = nullptr;
    sf::Font font;
    if (!font.loadFromMemory(Roboto, sizeof Roboto /  sizeof Roboto[0])) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
//    auto* texture = new sf::Texture;
//    if (!texture->loadFromMemory(pratibha, sizeof pratibha / sizeof pratibha[0])) {
//        std::cerr << "Error loading texture" << std::endl;
//        exit(-1);
//    }
    this->button.setFont(font);
    this->button.setPosition({100.f, 100.f});
    this->button.setString("Hello World");
    this->button.setTextColor(sf::Color::Black);
//    this->button.setTexture(texture);
    this->button.setSize({200.f, 100.f});
    this->button.setOutlineThickness(2.f);
    this->button.setFontSize(30);
//    this->button.setOutlineColor(sf::Color::White);


}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "SFML with C++");
    this->window->setVerticalSyncEnabled(true);
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
            case sf::Event::Resized:
                this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, ev.size.width, ev.size.height)));
                break;
            default:
                if (this->button.isPressed(ev)) {
                    IC();
                }
                break;
        }
    }
}

void Game::update() {
    this->clock.restart();
    this->pollEvents();
    this->button.update(sf::Mouse::getPosition(*this->window), *this->window);
}
