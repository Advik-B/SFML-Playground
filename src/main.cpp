#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "icecream.hpp"

struct Movement {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

class Shape : public sf::Shape {
// This class is a simple wrapper around sf::Shape to allow relative positioning of shapes
public:
    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setPosition(const sf::Vector2f &position) {
        setPosition(position.x, position.y);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void setFillColor_r(const sf::Color &color)  {
        fillColor = color;
    }

    void setOutlineColor(const sf::Color &color) {
        outlineColor = color;
    }

    void setOutlineThickness(float thickness) {
        outlineThickness = thickness;
    }

    void setPointCount(std::size_t count) {
        points.resize(count);
    }

    std::size_t getPointCount() const override {
        return points.size();
    }

    sf::Vector2f getPoint(std::size_t index) const override {
        return points[index];
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Transform transform;
        transform.translate(position);
        states.transform *= transform;
        states.texture = nullptr;

        if (fillColor.a != 0) {
            target.draw(reinterpret_cast<const sf::Vertex *>(&points[0]), points.size(), sf::PrimitiveType::TriangleFan, states);
        }

        if (outlineThickness != 0) {
            target.draw(reinterpret_cast<const sf::Vertex *>(&points[0]), points.size(), sf::PrimitiveType::LineStrip, states);
        }
    }

private:
    sf::Vector2f position;
    sf::Color fillColor;
    sf::Color outlineColor;
    float outlineThickness;
    std::vector<sf::Vector2f> points;
};

class Camera {
private:
    sf::RenderWindow &window;
    sf::View cameraView;
    Movement movement;

    // List of shapes to draw
    std::vector<Shape *> shapes;
    float movementSpeed = 5.0f;


public:
    Camera(sf::RenderWindow &window) : window(window) {
        cameraView = window.getDefaultView();
    }

    void addShape(Shape *shape) {
        shapes.push_back(shape);
    }

    void setMovementSpeed(float speed) {
        movementSpeed = speed;
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle keyboard input for movement
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W)
                    movement.up = true;
                if (event.key.code == sf::Keyboard::S)
                    movement.down = true;
                if (event.key.code == sf::Keyboard::A)
                    movement.left = true;
                if (event.key.code == sf::Keyboard::D)
                    movement.right = true;
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W)
                    movement.up = false;
                if (event.key.code == sf::Keyboard::S)
                    movement.down = false;
                if (event.key.code == sf::Keyboard::A)
                    movement.left = false;
                if (event.key.code == sf::Keyboard::D)
                    movement.right = false;
            }

            // Handle mouse wheel movement
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    cameraView.zoom(0.9f); // Zoom in
                else
                    cameraView.zoom(1.1f); // Zoom out
            }
        }
    }

    void update(sf::Time deltaTime = sf::Time::Zero) {
        if (movement.up) {
            IC("Moved");
            cameraView.move(0, -movementSpeed * deltaTime.asSeconds());
        }

        if (movement.down)
            cameraView.move(0, movementSpeed * deltaTime.asSeconds());
        if (movement.left)
            cameraView.move(-movementSpeed * deltaTime.asSeconds(), 0);
        if (movement.right)
            cameraView.move(movementSpeed * deltaTime.asSeconds(), 0);
    }

    void draw() {
        window.clear();
        window.setView(cameraView);

        // Draw all shapes with their positions updated relative to the camera
        for (auto shape: shapes) {
            sf::Vector2f cameraPosition = cameraView.getCenter() - cameraView.getSize() / 2.f;
            sf::Vector2f relativePosition = shape->getPosition();
            shape->setPosition(cameraPosition + relativePosition);
            window.draw(*shape);
        }

        window.display();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Camera Movement");
    // Create an instance of the Camera class
    Camera camera(window);
    camera.setMovementSpeed(0.6f);


    class Rectangle : public Shape, public sf::RectangleShape {};

    Rectangle rect;
    rect.setSize({100, 100});
    rect.setFillColor_r(sf::Color::Red);
    camera.addShape(&rect);

    sf::Clock clock;
    while (window.isOpen()) {
        camera.handleEvents();
        camera.update(clock.restart());
        camera.draw();
    }

    return 0;
}
