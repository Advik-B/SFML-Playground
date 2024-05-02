#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Nunito.hpp"
#include "icecream.hpp"
#include <string>
#include <vector>

typedef std::vector<std::string> Text;

class TextBox {
    private:
        sf::Vector2f position;
        sf::Vector2f scale;
        sf::Font font;
        sf::Color textColor;
        sf::Color outlineColor;
        sf::Color backgroundColor;
        Text text;
        sf::RectangleShape box;
        sf::Text displayText;
        void _update();
};

void TextBox::_update() {}