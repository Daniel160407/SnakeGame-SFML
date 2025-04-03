#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Food.hpp"

using namespace std;

const long SCREEN_WIDTH = 1920;
const long SCREEN_HEIGHT = 1080;

void drawFood(sf::RenderWindow &window, Food &food)
{
    sf::CircleShape foodShape(10.f);
    foodShape.setPosition(food.getPosX(), food.getPosY());
    foodShape.setFillColor(sf::Color::Red);
    window.draw(foodShape);
}

bool checkFoodCollision(const sf::RectangleShape &snake, const Food &food)
{
    sf::FloatRect snakeBounds = snake.getGlobalBounds();
    sf::FloatRect foodBounds(food.getPosX(), food.getPosY(), 20.f, 20.f);
    return snakeBounds.intersects(foodBounds);
}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");
    window.setFramerateLimit(60);

    sf::RectangleShape snake(sf::Vector2f(20, 20));
    snake.setPosition(100, 100);
    snake.setFillColor(sf::Color::Green);

    int currentDirection = 0;
    float moveSpeed = 5.0f;

    sf::Clock clock;
    float moveInterval = 0.01f;
    float timeSinceLastMove = 0.0f;

    Food currentFood(rand() % (SCREEN_WIDTH-20), rand() % (SCREEN_HEIGHT-20));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentDirection != 2)
        {
            currentDirection = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentDirection != 1)
        {
            currentDirection = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentDirection != 4)
        {
            currentDirection = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentDirection != 3)
        {
            currentDirection = 4;
        }

        float deltaTime = clock.restart().asSeconds();
        timeSinceLastMove += deltaTime;

        if (timeSinceLastMove >= moveInterval)
        {
            timeSinceLastMove = 0.0f;

            sf::Vector2f newPosition = snake.getPosition();
            switch (currentDirection)
            {
                case 1:
                    if (newPosition.y > 0) newPosition.y -= moveSpeed;
                    break;
                case 2:
                    if (newPosition.y < window.getSize().y - snake.getSize().y)
                        newPosition.y += moveSpeed;
                    break;
                case 3:
                    if (newPosition.x < window.getSize().x - snake.getSize().x)
                        newPosition.x += moveSpeed;
                    break;
                case 4:
                    if (newPosition.x > 0) newPosition.x -= moveSpeed;
                    break;
            }
            snake.setPosition(newPosition);
        }

        if (checkFoodCollision(snake, currentFood))
        {
            currentFood.setPosX(rand() % (SCREEN_WIDTH-20));
            currentFood.setPosY(rand() % (SCREEN_HEIGHT-20));
        }

        window.clear();
        window.draw(snake);
        drawFood(window, currentFood);
        window.display();
    }

    return 0;
}