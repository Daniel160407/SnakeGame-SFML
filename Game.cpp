#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

#define FOOD_SIZE 10.f
#define SCORE_INCREMENT 1

Game::Game(int width, int height)
    : window(sf::VideoMode(width, height), "Snake Game"),
      width(width), height(height),
      snake(20.f, 20.f, width, height),
      food(rand() % (width - 40), rand() % (height - 40)),
      wallsGenerator(width, height),
      score(0), isRunning(true)
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("src/fonts/Pixel_Game.otf"))
        std::cerr << "Failed to load font!" << std::endl;

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(20, 20);

    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setStyle(sf::Text::Bold);
    timeText.setPosition(20, 60);

    eatSoundBuffer.loadFromFile("src/sounds/food-eaten.wav");
    gameOverSoundBuffer.loadFromFile("src/sounds/game-over.wav");

    eatSound.setBuffer(eatSoundBuffer);
    gameOverSound.setBuffer(gameOverSoundBuffer);

    wallsGenerator.generateWalls(snake.getHead().getPosition().x, snake.getHead().getPosition().y);
}

void Game::run() {
    while (window.isOpen() && isRunning) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || 
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
            isRunning = false;
        }
    }
}

void Game::update() {
    snake.handleInput();
    float deltaTime = frameClock.restart().asSeconds();
    gameTime = gameClock.getElapsedTime().asSeconds();
    snake.update(deltaTime);

    if (checkFoodCollision()) {
        eatSound.play();
        snake.grow(food.isBigFood());
        score += food.isBigFood() ? SCORE_INCREMENT + 10 : SCORE_INCREMENT;
        food.setPosX(rand() % (width - 40));
        food.setPosY(rand() % (height - 40));
        food.setBigFood((rand() % 100) % 10 == 0);

        sf::CircleShape tempFood(FOOD_SIZE + 10);
        tempFood.setPosition(food.getPosX(), food.getPosY());

        while (!isAbleToGenerateFood(tempFood)) {
            food.setPosX(rand() % (width - 40));
            food.setPosY(rand() % (height - 40));
            tempFood.setPosition(food.getPosX(), food.getPosY());
        }

        if (snake.getParts().size() % 10 == 0) {
            wallsGenerator.generateWalls(snake.getHead().getPosition().x, snake.getHead().getPosition().y);
        }
    }

    if (snake.checkSelfCollision() || wallsGenerator.isCollidingWithWall(snake.getHead().getGlobalBounds())) {
        gameOverSound.play();
        float finalTime = gameClock.getElapsedTime().asSeconds();
        int result = showGameOverScreen();
        if (result == -1) isRunning = false;
        else reset();
    }
}

void Game::render() {
    window.clear();
    wallsGenerator.drawWalls(window);
    snake.draw(window);
    drawFood();
    drawUI();
    window.display();
}

void Game::drawUI() {
    std::stringstream scoreStream;
    scoreStream << "Score: " << score;
    scoreText.setString(scoreStream.str());
    window.draw(scoreText);

    std::stringstream timeStream;
    timeStream << "Time: " << std::fixed << std::setprecision(1) << gameClock.getElapsedTime().asSeconds() << "s";
    timeText.setString(timeStream.str());
    window.draw(timeText);
}

void Game::drawFood() {
    sf::CircleShape foodShape(food.isBigFood() ? FOOD_SIZE + 10 : FOOD_SIZE);
    foodShape.setPosition(food.getPosX(), food.getPosY());
    foodShape.setFillColor(food.isBigFood() ? sf::Color::Blue : sf::Color::Red);
    window.draw(foodShape);
}

bool Game::checkFoodCollision() {
    return snake.getHead().getGlobalBounds().intersects(
        sf::FloatRect(food.getPosX(), food.getPosY(), FOOD_SIZE * 2, FOOD_SIZE * 2)
    );
}

bool Game::isAbleToGenerateFood(const sf::CircleShape& food) {
    for (const sf::RectangleShape& wall : wallsGenerator.getGeneratedWalls()) {
        if (wall.getGlobalBounds().intersects(food.getGlobalBounds())) {
            return false;
        }
    }
    return true;
}

void Game::reset() {
    if (snake.getParts().size() > 1){
        snake.removeBody();
    }
    snake.setSize(20.f);
    snake.setSpeed(20.f);
    snake.setScreenWidth(width);
    snake.setScreenHeight(height);
    food.setPosX(rand() % (width - 40));
    food.setPosY(rand() % (height - 40));
    food.setBigFood(false);
    score = 0;
    gameClock.restart();
    wallsGenerator.generateWalls(snake.getHead().getPosition().x, snake.getHead().getPosition().y);
}

int Game::showGameOverScreen() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER!");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(width / 2.f - gameOverText.getLocalBounds().width / 2.f,
                             height / 2.f - 150);

    std::stringstream scoreStream;
    scoreStream << "Final Score: " << score;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(scoreStream.str());
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(width / 2.f - scoreText.getLocalBounds().width / 2.f,
                          height / 2.f);

    std::stringstream timeStream;
    timeStream << "Time: " << std::fixed << std::setprecision(1) << gameTime << " seconds";
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setString(timeStream.str());
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(width / 2.f - timeText.getLocalBounds().width / 2.f,
                         height / 2.f + 80);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setString("Press R to Restart or ESC to Exit");
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setPosition(width / 2.f - restartText.getLocalBounds().width / 2.f,
                            height / 2.f + 180);

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