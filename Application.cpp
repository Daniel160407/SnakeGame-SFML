#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Food.hpp"

using namespace std;

const long SCREEN_WIDTH = 1920;
const long SCREEN_HEIGHT = 1080;
const float SNAKE_SIZE = 20.f;
const float FOOD_SIZE = 10.f;

void drawFood(sf::RenderWindow& window, Food& food) {
    sf::CircleShape foodShape(FOOD_SIZE);
    foodShape.setPosition(food.getPosX(), food.getPosY());
    foodShape.setFillColor(sf::Color::Red);
    window.draw(foodShape);
}

bool checkFoodCollision(const sf::RectangleShape& snakeHead, const Food& food) {
    sf::FloatRect snakeBounds = snakeHead.getGlobalBounds();
    sf::FloatRect foodBounds(food.getPosX(), food.getPosY(), FOOD_SIZE*2, FOOD_SIZE*2);
    return snakeBounds.intersects(foodBounds);
}

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");
    window.setFramerateLimit(60);

    vector<sf::RectangleShape> snakeParts;
    sf::RectangleShape head(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    head.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    head.setFillColor(sf::Color::Green);
    snakeParts.push_back(head);

    int currentDirection = 3;
    float moveSpeed = SNAKE_SIZE;
    vector<sf::Vector2f> previousPositions;

    sf::Clock clock;
    float moveInterval = 0.1f;
    float timeSinceLastMove = 0.0f;

    Food currentFood(rand() % (SCREEN_WIDTH - 40), rand() % (SCREEN_HEIGHT - 40));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentDirection != 2) {
            currentDirection = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentDirection != 1) {
            currentDirection = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentDirection != 4) {
            currentDirection = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentDirection != 3) {
            currentDirection = 4;
        }

        float deltaTime = clock.restart().asSeconds();
        timeSinceLastMove += deltaTime;

        if (timeSinceLastMove >= moveInterval) {
            timeSinceLastMove = 0.0f;

            previousPositions.clear();
            for (const auto& part : snakeParts) {
                previousPositions.push_back(part.getPosition());
            }

            sf::Vector2f newPosition = snakeParts[0].getPosition();
            switch (currentDirection) {
                case 1:
                    newPosition.y -= moveSpeed;
                    if (newPosition.y < 0) newPosition.y = SCREEN_HEIGHT - SNAKE_SIZE;
                    break;
                case 2:
                    newPosition.y += moveSpeed;
                    if (newPosition.y >= SCREEN_HEIGHT) newPosition.y = 0;
                    break;
                case 3:
                    newPosition.x += moveSpeed;
                    if (newPosition.x >= SCREEN_WIDTH) newPosition.x = 0;
                    break;
                case 4:
                    newPosition.x -= moveSpeed;
                    if (newPosition.x < 0) newPosition.x = SCREEN_WIDTH - SNAKE_SIZE;
                    break;
            }
            snakeParts[0].setPosition(newPosition);

            for (size_t i = 1; i < snakeParts.size(); i++) {
                snakeParts[i].setPosition(previousPositions[i-1]);
            }

            if (checkFoodCollision(snakeParts[0], currentFood)) {
                currentFood.setPosX(rand() % (SCREEN_WIDTH - 40));
                currentFood.setPosY(rand() % (SCREEN_HEIGHT - 40));

                sf::RectangleShape newPart(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
                newPart.setPosition(previousPositions.back());
                newPart.setFillColor(sf::Color(0, 200, 0));
                snakeParts.push_back(newPart);
            }

            for (size_t i = 1; i < snakeParts.size(); i++) {
                if (snakeParts[0].getGlobalBounds().intersects(snakeParts[i].getGlobalBounds())) {
                    window.close();
                }
            }
        }

        window.clear();
        for (const auto& part : snakeParts) {
            window.draw(part);
        }
        drawFood(window, currentFood);
        window.display();
    }

    return 0;
}