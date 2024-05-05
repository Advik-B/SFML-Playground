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
        static float getFontSizes(const sf::Font& font, const std::string& str, unsigned int size);

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
        void setSize(const sf::Vector2f& size);
        void setOutlineColor(const sf::Color& color);
        void setFontStyle(sf::Text::Style style);
        void setOutlineThickness(float thickness);
        void setFontSize(unsigned int size);

        bool isPressed(const sf::Event& ev);
    };

} // UI

#endif //SFML_PLAYGROUND_BUTTON_HPP
