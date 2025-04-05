#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
    Snake(float size, float speed, int screenWidth, int screenHeight);

    void setSize(float size);
    void setSpeed(float speed);
    void setScreenWidth(int screenWidth);
    void setScreenHeight(int screenHeight);
    void setMoveInterval(float moveInterval);
    void handleInput();
    void update(float deltaTime);
    void grow(bool bigFood);
    void removeBody();
    bool checkSelfCollision() const;
    void draw(sf::RenderWindow& window) const;
    sf::RectangleShape getHead() const;
    std::vector<sf::RectangleShape> getParts() const;

private:
    std::vector<sf::RectangleShape> parts;
    std::vector<sf::Vector2f> previousPositions;
    float size;
    float speed;
    int screenWidth;
    int screenHeight;
    float timeSinceLastMove;
    float moveInterval;
    const float MIN_INTERVAL = 0.05f;
    const float SPEED_INCREMENT = 0.0005f;
    int direction;
};

#endif