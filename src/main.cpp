#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <SFML/Graphics.hpp>
#include "icecream.hpp"
#include "fonts/Roboto-Regular.hpp"
#include "pratibha.hpp"

class Button {
private:
    sf::Text text;
    sf::Font font;
};

void onResize(const sf::Event::SizeEvent &sizeEvent, sf::RenderWindow &window) {
    window.setView(
            sf::View(
                    sf::FloatRect(
                            0,
                            0,
                            sizeEvent.width,
                            sizeEvent.height
                    )
            )
    );
    IC(window.getSize().x, window.getSize().y);
}

sf::Texture *screenGrab(sf::RenderWindow &window) {
    auto texture = new sf::Texture();
    texture->create(window.getSize().x, window.getSize().y);
    texture->update(window);
    return texture;
}

int main() {
    sf::RenderWindow window(
            sf::VideoMode(850, 600),
            ""
    );
    window.setVerticalSyncEnabled(true);
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromMemory(pratibha, sizeof(pratibha));
//    unsigned char texels[] = {
//            255, 0, 0, 255,
//            0, 255, 0, 255,
//            0, 0, 255, 255,
//            255, 255, 0, 255,
//    };
//    texture.create(2, 2);
//    texture.update(texels);
    sprite.setTexture(texture);
//    sprite.setScale(200.f / 2, 200.f / 2);
    sprite.setPosition(100, 100);
    // Set the origin of the sprite to the center
    sprite.setOrigin(1, 1);

    sf::Font font;
    if (!font.loadFromMemory(Roboto, sizeof(Roboto))) {
        IC("Failed to load font", Roboto);
        return 1;
    }
    // Make a text and rasterize it into a texture
    sf::Text text;
    text.setFont(font);
    text.setString("Hello, World!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(100, 100);
    // Set the origin of the text to the center
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    sf::Texture *textTexture = screenGrab(window);
    sf::Sprite textSprite(*textTexture);
    textSprite.setPosition(100, 100);
    textSprite.setScale(0.9, 0.9);
    textSprite.setOrigin(textSprite.getLocalBounds().width / 2, textSprite.getLocalBounds().height / 2);

    sf::Vector2f velocity(100, 100);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                onResize(event.size, window);

        }

        window.clear();
        window.draw(textSprite);
        window.draw(sprite);
        window.display();
        textSprite.setTexture(*screenGrab(window));

        auto dt = clock.restart();
        // Update the sprite
        sprite.rotate(dt.asSeconds() * 150);
        textSprite.setRotation(sprite.getRotation());
        sprite.move(velocity * dt.asSeconds());
        textSprite.setPosition(sprite.getPosition());

        if (sprite.getPosition().x < 0 || sprite.getPosition().x > window.getSize().x)
            velocity.x = -velocity.x;
        if (sprite.getPosition().y < 0 || sprite.getPosition().y > window.getSize().y)
            velocity.y = -velocity.y;
    }

    return 0;
}