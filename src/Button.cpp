#include "Button.hpp"
#include "StandardCursor.cpp"

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


    void Button::setPosition(const sf::Vector2f& pos) {
        this->shape.setPosition(pos);

        float x = pos.x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f;
        float y = pos.y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f;

        this->text.setPosition({x - 20, y});
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

    void Button::setSize(const sf::Vector2f &size) {
        this->shape.setSize(size);
        // Calculate the new position of the text
        float x = this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f;
        float y = this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f;
        this->text.setPosition({x, y});

        // Calculate the new font size of the text
        unsigned int newSize = this->text.getCharacterSize();
        while (getFontSizes(this->font, this->text.getString(), newSize) > this->shape.getGlobalBounds().width) {
            newSize--;
        }
        this->text.setCharacterSize(newSize);
    }

    float Button::getFontSizes(const sf::Font &font, const std::string &str, unsigned int size) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(size);
        text.setString(str);
        return text.getGlobalBounds().width;
    }

    void Button::setOutlineColor(const sf::Color &color) {
        this->shape.setOutlineColor(color);
    }

    void Button::setFontStyle(sf::Text::Style style) {
        this->text.setStyle(style);
    }

    void Button::setOutlineThickness(float thickness) {
        this->shape.setOutlineThickness(thickness);
    }

    void Button::setFontSize(unsigned int size) {
        // Calculate the new position of the text and set the new font size
        this->text.setCharacterSize(size);
        float x = this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f;
        float y = this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f;
        this->text.setPosition({x, y});
    }

    void Button::update(const sf::Vector2i &mousePos, sf::Window &window) {
        if (this->isMouseOver(mousePos)) {
            this->shape.setFillColor(sf::Color::Red);
             sf::StandardCursor(sf::StandardCursor::HAND).set(window.getSystemHandle());
        } else {
            this->shape.setFillColor(sf::Color::White);
            sf::StandardCursor(sf::StandardCursor::NORMAL).set(window.getSystemHandle());
        }
    }

}