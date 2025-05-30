#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>


void drawPythagoreanTree(sf::RenderWindow& window, sf::Vector2f position, double size, double angle, int depth, int color) {
    if (depth == 0) {
        return;
    }

    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setOutlineColor(sf::Color::Green);
    square.setOutlineThickness(0.5);
    square.setFillColor(sf::Color(color, 240, 0));
    square.setOrigin(size / 2, size / 2);
    square.setPosition(position);
    square.setRotation(angle);
    window.draw(square);
    
    double radAngle = angle * M_PI / 180.0;

    // Координаты верхней левой вершины текущего квадрата
    sf::Vector2f topLeft;
    topLeft.x = -size / 2.0;
    topLeft.y = -size;

    // Координаты верхней правой вершины текущего квадрата
    sf::Vector2f topRight;
    topRight.x = size / 2.0;
    topRight.y = -size;

    // Поворачиваем эти точки на текущий угол и смещаем их к position
    sf::Vector2f topLeftRotated;
    topLeftRotated.x = position.x + (topLeft.x * cos(radAngle) - topLeft.y * sin(radAngle));
    topLeftRotated.y = position.y + (topLeft.x * sin(radAngle) + topLeft.y * cos(radAngle));

    sf::Vector2f topRightRotated;
    topRightRotated.x = position.x + (topRight.x * cos(radAngle) - topRight.y * sin(radAngle));
    topRightRotated.y = position.y + (topRight.x * sin(radAngle) + topRight.y * cos(radAngle));
    
    // Длина стороны следующих квадратов
    double newSize = size / std::sqrt(2.0);

    // Рекурсивные вызовы для двух новых ветвей
    drawPythagoreanTree(window, topLeftRotated, newSize, angle - 45, depth - 1, color - 20);
    drawPythagoreanTree(window, topRightRotated, newSize, angle + 45, depth - 1, color - 20);
}


int main() {
    int maxDepth {12};

    sf::RenderWindow window(sf::VideoMode(800, 600), "Дерево Пифагора");
    window.setFramerateLimit(60);

    sf::Vector2f initialPosition(400, 500);
    double initialSize = 100;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        drawPythagoreanTree(window, initialPosition, initialSize, 0, maxDepth, 255);
        window.display();
    }

    return 0;
}
