#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Nunito.hpp"

class TextInput {
public:
    TextInput(sf::RenderWindow &window) : window(window) {
        /*
         unsigned char Nunito_SemiBold[] = { 0x00, 0x01, ...}
         */
        auto Nunito_SemiBold_size = sizeof(Nunito_SemiBold) / sizeof(Nunito_SemiBold[0]);
        font.loadFromMemory(Nunito_SemiBold, Nunito_SemiBold_size);
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        rectangle.setFillColor(sf::Color(35, 39, 46));
    }


    inline void draw() {
        // Draw a rectangle behind the text
        _drawRectangle();
        // Draw the text
        _drawText();
        // Draw the cursor
        _drawCursor();
    }

    inline void setPosition(float x, float y) {
        position = {x, y};
        text.setPosition(x, y);
        rectangle.setPosition(x + 5, y + 5);
    }

    inline void setPadding(float new_padding) {
        padding = new_padding;
    }

    void update(sf::Event event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == 8) {
                    if (!input.empty()) {
                        input.pop_back();
                    }
                } else {
                    input += static_cast<char>(event.text.unicode);
                }
                _updateText();
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                input.clear();
                _updateText();
            }
        }

    }

private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::Text text;
    std::string input;
    sf::RectangleShape rectangle;
    sf::Vector2f position;
    float padding;

    void _drawRectangle() {
        window.draw(rectangle);
    }

    void _updateText() {
        rectangle.setSize(sf::Vector2f(text.getLocalBounds().width + 10, text.getLocalBounds().height + 10));
        // Set the position of the rectangle to be 5 pixels away from the text
        rectangle.setPosition(position.x - padding, position.y + padding);
        text.setString(input);
    }

    void _drawCursor() {
        // Draw a cursor at the end of the text
        auto bounds = text.getLocalBounds();
        sf::RectangleShape cursor;
        cursor.setSize(sf::Vector2f(1, bounds.height + padding));
        cursor.setFillColor(sf::Color::White);
        cursor.setPosition(bounds.width, position.y);
        window.draw(cursor);
    }

    void _drawText() {
        window.draw(text);
    }
};