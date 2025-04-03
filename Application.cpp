#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snake Game");
    window.setFramerateLimit(60);

    sf::RectangleShape snake(sf::Vector2f(20, 20));
    snake.setPosition(100, 100);
    snake.setFillColor(sf::Color::Green);

    int currentDirection = 0;
    float moveSpeed = 5.0f;

    sf::Clock clock;
    float moveInterval = 0.01f;
    float timeSinceLastMove = 0.0f;

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
                    if (newPosition.y > 0)
                        newPosition.y -= moveSpeed;
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
                    if (newPosition.x > 0)
                        newPosition.x -= moveSpeed;
                    break;
            }
            snake.setPosition(newPosition);
        }

        window.clear();
        window.draw(snake);
        window.display();
    }

    return 0;
}