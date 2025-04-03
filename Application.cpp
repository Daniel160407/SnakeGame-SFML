#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Food.hpp"

using namespace std;

const long SCREEN_WIDTH = 800;
const long SCREEN_HEIGHT = 600;
const float SNAKE_SIZE = 20.f;
const float SNAKE_MOVE_SPEED = 20.f;
const float FOOD_SIZE = 10.f;
const int SCORE_INCREMENT = 1;

void drawFood(sf::RenderWindow &window, Food &food)
{
    if (food.isBigFood())
    {
        sf::CircleShape foodShape(FOOD_SIZE + 10);
        foodShape.setPosition(food.getPosX(), food.getPosY());
        foodShape.setFillColor(sf::Color::Blue);
        window.draw(foodShape);
    }
    else
    {
        sf::CircleShape foodShape(FOOD_SIZE);
        foodShape.setPosition(food.getPosX(), food.getPosY());
        foodShape.setFillColor(sf::Color::Red);
        window.draw(foodShape);
    }
}

bool checkFoodCollision(const sf::RectangleShape &snakeHead, const Food &food)
{
    sf::FloatRect snakeBounds = snakeHead.getGlobalBounds();
    sf::FloatRect foodBounds(food.getPosX(), food.getPosY(), FOOD_SIZE * 2, FOOD_SIZE * 2);
    return snakeBounds.intersects(foodBounds);
}

int showGameOverScreen(sf::RenderWindow &window, sf::Font &font, int score, float gameTime)
{
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER!");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(SCREEN_WIDTH / 2 - gameOverText.getLocalBounds().width / 2,
                             SCREEN_HEIGHT / 2 - 150);

    stringstream scoreStream;
    scoreStream << "Final Score: " << score;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(scoreStream.str());
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(SCREEN_WIDTH / 2 - scoreText.getLocalBounds().width / 2,
                          SCREEN_HEIGHT / 2);

    stringstream timeStream;
    timeStream << "Time: " << fixed << setprecision(1) << gameTime << " seconds";
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setString(timeStream.str());
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(SCREEN_WIDTH / 2 - timeText.getLocalBounds().width / 2,
                         SCREEN_HEIGHT / 2 + 80);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setString("Press R to Restart or ESC to Exit");
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setPosition(SCREEN_WIDTH / 2 - restartText.getLocalBounds().width / 2,
                            SCREEN_HEIGHT / 2 + 180);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return -1;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    return 0;
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return -1;
                }
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(timeText);
        window.draw(restartText);
        window.display();
    }
    return -1;
}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("src/fonts/Pixel_Game.otf"))
    {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    while (true)
    {
        int score = 0;
        sf::Clock gameClock;
        sf::Clock frameClock;

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(20, 20);

        sf::Text timeText;
        timeText.setFont(font);
        timeText.setCharacterSize(30);
        timeText.setFillColor(sf::Color::White);
        timeText.setStyle(sf::Text::Bold);
        timeText.setPosition(20, 60);

        vector<sf::RectangleShape> snakeParts;
        sf::RectangleShape head(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
        head.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        head.setFillColor(sf::Color::Green);
        snakeParts.push_back(head);

        int currentDirection = 3;
        vector<sf::Vector2f> previousPositions;

        Food currentFood(rand() % (SCREEN_WIDTH - 40), rand() % (SCREEN_HEIGHT - 40));

        bool gameOver = false;
        float timeSinceLastMove = 0.0f;

        while (window.isOpen() && !gameOver)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return -1;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return -1;
                }
            }

            if (!gameOver)
            {
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

                float deltaTime = frameClock.restart().asSeconds();
                timeSinceLastMove += deltaTime;

                if (timeSinceLastMove >= 0.1f)
                {
                    timeSinceLastMove = 0.0f;

                    previousPositions.clear();
                    for (const auto &part : snakeParts)
                    {
                        previousPositions.push_back(part.getPosition());
                    }

                    sf::Vector2f newPosition = snakeParts[0].getPosition();
                    switch (currentDirection)
                    {
                    case 1:
                        newPosition.y -= SNAKE_MOVE_SPEED;
                        if (newPosition.y < 0)
                            newPosition.y = SCREEN_HEIGHT - SNAKE_SIZE;
                        break;
                    case 2:
                        newPosition.y += SNAKE_MOVE_SPEED;
                        if (newPosition.y >= SCREEN_HEIGHT)
                            newPosition.y = 0;
                        break;
                    case 3:
                        newPosition.x += SNAKE_MOVE_SPEED;
                        if (newPosition.x >= SCREEN_WIDTH)
                            newPosition.x = 0;
                        break;
                    case 4:
                        newPosition.x -= SNAKE_MOVE_SPEED;
                        if (newPosition.x < 0)
                            newPosition.x = SCREEN_WIDTH - SNAKE_SIZE;
                        break;
                    }
                    snakeParts[0].setPosition(newPosition);

                    for (size_t i = 1; i < snakeParts.size(); i++)
                    {
                        snakeParts[i].setPosition(previousPositions[i - 1]);
                    }

                    if (checkFoodCollision(snakeParts[0], currentFood))
                    {
                        if (currentFood.isBigFood())
                        {
                            score += SCORE_INCREMENT + 10;
                        }
                        else
                        {
                            score += SCORE_INCREMENT;
                        }
                        currentFood.setPosX(rand() % (SCREEN_WIDTH - 40));
                        currentFood.setPosY(rand() % (SCREEN_HEIGHT - 40));

                        int random = (rand() % 100);
                        if (random % 10 == 0)
                        {
                            currentFood.setBigFood(true);
                        }
                        else
                        {
                            currentFood.setBigFood(false);
                        }

                        sf::RectangleShape newPart(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
                        newPart.setPosition(previousPositions.back());
                        newPart.setFillColor(sf::Color(0, 200, 0));
                        snakeParts.push_back(newPart);
                    }

                    for (size_t i = 1; i < snakeParts.size(); i++)
                    {
                        if (snakeParts[0].getGlobalBounds().intersects(snakeParts[i].getGlobalBounds()))
                        {
                            gameOver = true;
                        }
                    }
                }

                stringstream scoreStream;
                scoreStream << "Score: " << score;
                scoreText.setString(scoreStream.str());

                stringstream timeStream;
                timeStream << "Time: " << fixed << setprecision(1) << gameClock.getElapsedTime().asSeconds() << "s";
                timeText.setString(timeStream.str());

                window.clear();
                for (const auto &part : snakeParts)
                {
                    window.draw(part);
                }
                drawFood(window, currentFood);
                window.draw(scoreText);
                window.draw(timeText);
                window.display();
            }
        }

        if (gameOver && window.isOpen())
        {
            float finalTime = gameClock.getElapsedTime().asSeconds();
            int result = showGameOverScreen(window, font, score, finalTime);
            if (result == -1)
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }

    return 0;
}