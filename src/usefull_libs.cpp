//
// Created by Advik on 01-05-2024.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

int getPointCount(const sf::RenderWindow &window, const sf::CircleShape &circle) {
    // Get the size of the window
    unsigned windowSize = window.getSize().x * window.getSize().y / 100000;

    // Get the radius of the circle
    float radius = circle.getRadius();

    // Calculate the number of points needed to approximate the circle
    int pcout = static_cast<int>(radius * windowSize / 10);
    std::cout << "Point Count: " << pcout << '\n';
    return pcout;
}