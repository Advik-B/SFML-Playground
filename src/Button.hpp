#ifndef SFML_PLAYGROUND_BUTTON_HPP
#define SFML_PLAYGROUND_BUTTON_HPP

#include <SFML/Graphics.hpp>

namespace UI {

    class Button {
    private:
        sf::RectangleShape shape;
        sf::Font font;
        sf::Text text;
        sf::Texture* texture;

        bool isMouseOver(const sf::Vector2f& mousePos);

    public:
        Button();
        virtual ~Button();

        void setFont(sf::Font& font);
        void setBackColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setCharacterSize(unsigned int size);
        void setPosition(const sf::Vector2f& pos);
        void setString(const std::string& str);
        void setTexture(sf::Texture* texture);
        void render_to(sf::RenderTarget& target);

        bool isPressed(const sf::Event& ev);
    };

} // UI

#endif //SFML_PLAYGROUND_BUTTON_HPP
