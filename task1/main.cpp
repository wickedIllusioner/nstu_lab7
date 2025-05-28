#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>


void drawSquare(sf::RenderWindow& window, sf::Vector2f position, double size, sf::Color color) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(color);
    window.draw(square);
}

void drawPythagoreanTree(sf::RenderWindow& window, sf::Vector2f position, double size, double angle, int depth, int color) {
    if (depth == 0) {
        return;
    }

    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setOutlineColor(sf::Color::Green);
    square.setOutlineThickness(0.3);
    square.setFillColor(sf::Color(color, 240, 0));
    square.setOrigin(size / 2, size / 2);
    square.setPosition(position);
    square.setRotation(angle);
    window.draw(square);

    // Calculate the positions for the subsequent squares
    // We need to find the top-center of the current square to place the triangle
    sf::Vector2f topCenter;
    topCenter.x = position.x + (size / 2) * sin(angle * M_PI / 180);
    topCenter.y = position.y - (size / 2) * cos(angle * M_PI / 180);

    // The new squares will have side length (size / sqrt(2))
    double newSize = size / sqrt(2.);


    // Нахождение координат левого квадрата
    sf::Vector2f leftSquarePos;
    leftSquarePos.x = topCenter.x - (newSize / 2) * cos(angle * M_PI / 180);
    leftSquarePos.y = topCenter.y - (newSize / 2) * sin(angle * M_PI / 180);

    // Нахождение координат правого квадрата
    sf::Vector2f rightSquarePos;
    rightSquarePos.x = topCenter.x + (newSize / 2) * cos(angle * M_PI / 180);
    rightSquarePos.y = topCenter.y + (newSize / 2) * sin(angle * M_PI / 180);

    // Рекурсивный вызов функции для генерации двух квадратов
    drawPythagoreanTree(window, leftSquarePos, newSize, angle - 45, depth - 1, color - 25);
    drawPythagoreanTree(window, rightSquarePos, newSize, angle + 45, depth - 1, color - 25);
}

int main() {
    int maxDepth {10};
    // std::cout << "Введите число глубины рекурсии: ";
    // std::cin >> maxDepth;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Дерево Пифагора");
    window.setFramerateLimit(60);

    sf::Vector2f initialPosition(400, 500); // Bottom-center of the window
    double initialSize = 100.0f;             // Size of the base square
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
