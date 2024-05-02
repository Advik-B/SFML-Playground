#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Nunito.hpp"
#include "icecream.hpp"
#include <string>
#include <vector>

typedef std::vector<std::string> Text;

class TextBox {
    public:
        TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font font, sf::Text &displayText);

    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font font);

//        ~TextBox();
        void update(sf::Event &event);
        void draw_to(sf::RenderWindow &window);
        void setPosition(sf::Vector2f position);
        void setScale(sf::Vector2f scale);
        void setFont(sf::Font font);
        void setTextColor(sf::Color textColor);
        void setOutlineColor(sf::Color outlineColor);
        void setBackgroundColor(sf::Color backgroundColor);
        void setText(Text text);
        void setString(std::string text);
        sf::Vector2f getPosition();
        sf::Vector2f getScale();
        sf::Font getFont();
        sf::Color getTextColor();
        sf::Color getOutlineColor();
        sf::Color getBackgroundColor();
    private:
        sf::Vector2f position;
        sf::Vector2f scale;
        sf::Font font;
        sf::Color textColor;
        sf::Color outlineColor;
        sf::Color backgroundColor;
        Text text;
        sf::RectangleShape box;
        sf::Text displayText = sf::Text();
        bool isFocused;
        void _update();
};

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font font) : displayText() {
    this->position = position;
    this->scale = size;
    this->font = font;
    this->box = sf::RectangleShape(size);
    this->box.setPosition(position);
    this->box.setFillColor(sf::Color::White);
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setOutlineThickness(1);
    this->displayText.setFont(font);
    this->displayText.setPosition(position);
    this->displayText.setFillColor(sf::Color::Black);
    this->displayText.setCharacterSize(20);
    this->isFocused = false;
}

void TextBox::setString(std::string newString) {
    // Split the text at every '\n' character
    std::string line;
    for (char c : newString) {
        if (c == '\n') {
            this->text.push_back(line);
            line = "";
        } else {
            line += c;
        }
    }
    this->text.push_back(line);
    this->_update();
}

void TextBox::setText(Text text) {
    this->text = text;
    this->_update();
}

void TextBox::_update() {
    std::string displayText_;
    for (std::string line : this->text) {
        displayText_ += line + '\n';
    }
    this->displayText.setString(displayText_);
}

void TextBox::update(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        if (this->box.getGlobalBounds().contains(mousePosition)) {
            this->isFocused = true;
        } else {
            this->isFocused = false;
        }
    }
    if (this->isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {
            // Backspace
            if (this->text.size() > 0) {
                this->text.back().pop_back();
                if (this->text.back().size() == 0) {
                    this->text.pop_back();
                }
            }
        } else {
            this->text.back() += event.text.unicode;
        }
        this->_update();
    }
}

void TextBox::draw_to(sf::RenderWindow &window) {
    IC();
    window.draw(box);
    IC();
    window.draw(displayText);
    IC();
}

void TextBox::setPosition(sf::Vector2f position) {
    this->position = position;
    this->box.setPosition(position);
    this->displayText.setPosition(position);
}

void TextBox::setScale(sf::Vector2f scale) {
    this->scale = scale;
    this->box.setSize(scale);
    this->_update();
}

void TextBox::setFont(sf::Font font) {
    this->font = font;
    this->displayText.setFont(font);
    this->_update();
}

void TextBox::setTextColor(sf::Color textColor) {
    this->textColor = textColor;
    this->displayText.setFillColor(textColor);
}

void TextBox::setOutlineColor(sf::Color outlineColor) {
    this->outlineColor = outlineColor;
    this->box.setOutlineColor(outlineColor);
}

void TextBox::setBackgroundColor(sf::Color backgroundColor) {
    this->backgroundColor = backgroundColor;
    this->box.setFillColor(backgroundColor);
}

sf::Vector2f TextBox::getPosition() {
    return this->position;
}

sf::Vector2f TextBox::getScale() {
    return this->scale;
}

sf::Font TextBox::getFont() {
    return this->font;
}

sf::Color TextBox::getTextColor() {
    return this->textColor;
}

sf::Color TextBox::getOutlineColor() {
    return this->outlineColor;
}

sf::Color TextBox::getBackgroundColor() {
    return this->backgroundColor;
}

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font font, sf::Text &displayText) {
    this->position = position;
    this->scale = size;
    this->font = font;
    this->box = sf::RectangleShape(size);
    this->box.setPosition(position);
    this->box.setFillColor(sf::Color::White);
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setOutlineThickness(1);
    this->displayText = displayText;
    this->displayText.setFont(font);
    this->displayText.setPosition(position);
    this->displayText.setFillColor(sf::Color::Black);
    this->displayText.setCharacterSize(20);
    this->isFocused = false;

}

//TextBox::~TextBox() {}