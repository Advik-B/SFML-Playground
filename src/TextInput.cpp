#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Nunito.hpp"
#include "icecream.hpp"
#include <string>
#include <vector>

typedef std::vector<std::string> displayText;

class TextBox {
    private:
        sf::Vector2f position;
        sf::Vector2f scale;
        void _update();
};

void TextBox::_update() {}