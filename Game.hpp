#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.hpp"
#include "Food.hpp"
#include "WallsGenerator.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define SNAKE_SIZE 20.f
#define FOOD_SIZE 10.f
#define SCORE_INCREMENT 1

class Game {
public:
    Game(int width, int height);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void reset();
    void drawUI();
    void drawFood();
    bool checkFoodCollision();
    bool isAbleToGenerateFood(const sf::CircleShape& food);
    int showGameOverScreen();

    sf::RenderWindow window;
    sf::Font font;
    sf::SoundBuffer eatSoundBuffer, gameOverSoundBuffer;
    sf::Sound eatSound, gameOverSound;
    sf::Text scoreText, timeText;

    Snake snake;
    Food food;
    WallsGenerator wallsGenerator;

    int width, height;
    int score;
    float gameTime = 0.f;
    sf::Clock gameClock, frameClock;
    bool isRunning;
};

#endif