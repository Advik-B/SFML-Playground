#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Nunito.hpp"
#include "icecream.hpp"
#include <string>
#include <vector>

typedef std::vector<std::string> Text;

class TextBox {
    public:
        TextBox();
        ~TextBox();
        void update(sf::Event &event);
        void draw_to(sf::RenderWindow &window);
        void setPosition(sf::Vector2f position);
        void setScale(sf::Vector2f scale);
        void setFont(sf::Font font);
        void setTextColor(sf::Color textColor);
        void setOutlineColor(sf::Color outlineColor);
        void setBackgroundColor(sf::Color backgroundColor);
        void setText(Text text);
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
        sf::Text displayText;
        void _update();
};

void TextBox::_update() {}