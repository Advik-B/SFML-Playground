#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <SFML/Graphics.hpp>
#include "icecream.hpp"
inline void __(sf::RenderWindow &window) {
    auto size = sf::Vector2<sf::Uint32>(window.getSize().x, window.getSize().y);
    IC(size.x, size.y);
}

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
    __(window);
}

int main() {
    sf::RenderWindow window(
            sf::VideoMode(850, 600),
            ""
    );
    window.setVerticalSyncEnabled(true);
    sf::Sprite sprite;
    sf::Texture texture;
    unsigned char texels[] = {
            255, 0, 0, 255,
            0, 255, 0, 255,
            0, 0, 255, 255,
            255, 255, 0, 255,
    };
    texture.create(2, 2);
    texture.update(texels);
    sprite.setTexture(texture);
    sprite.setScale(200.f / 2, 200.f / 2);
    sprite.setPosition(100, 100);
    // Set the origin of the sprite to the center
    sprite.setOrigin(1, 1);

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        IC("Failed to load font");
        return 1;
    }
    __(window);
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
        window.draw(sprite);
        window.display();

        auto dt = clock.restart();
        // Update the sprite
        sprite.rotate(dt.asSeconds() * 150);
        sprite.move(100 * dt.asSeconds(), 1);

    }

    return 0;
}