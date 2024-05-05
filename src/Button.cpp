#include "Button.hpp"

namespace UI {
    Button::Button() {
        this->shape.setSize({100.f, 50.f});
        this->shape.setFillColor(sf::Color::White);
        this->shape.setOutlineThickness(1.f);
        this->shape.setOutlineColor(sf::Color::Black);

        this->text.setFont(this->font);
        this->text.setFillColor(sf::Color::Black);
        this->text.setCharacterSize(12);

        this->texture = nullptr;
    }

    Button::~Button() {
        delete this->texture;
    }

    void Button::setFont(sf::Font& font) {
        this->font = font;
        this->text.setFont(this->font);
    }

    void Button::setBackColor(sf::Color color) {
        this->shape.setFillColor(color);
    }

    void Button::setTextColor(sf::Color color) {
        this->text.setFillColor(color);
    }

    void Button::setCharacterSize(unsigned int size) {
        this->text.setCharacterSize(size);
    }

    void Button::setPosition(const sf::Vector2f& pos) {
        this->shape.setPosition(pos);

        float x = pos.x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f;
        float y = pos.y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f;

        this->text.setPosition({x, y});
    }

    void Button::setString(const std::string& str) {
        this->text.setString(str);
    }

    void Button::setTexture(sf::Texture* texture) {
        this->texture = texture;
        this->shape.setTexture(this->texture);
    }

    void Button::render_to(sf::RenderTarget& target) {
        target.draw(this->shape);
        target.draw(this->text);
    }

    bool Button::isMouseOver(const sf::Vector2f& mousePos) {
        return this->shape.getGlobalBounds().contains(mousePos);
    }

    bool Button::isPressed(const sf::Event& ev) {
        if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
            if (this->isMouseOver({static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y)})) {
                return true;
            }
        }
        return false;
    }

}