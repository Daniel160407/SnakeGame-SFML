#include "Snake.hpp"

Snake::Snake(float size, float speed, int screenWidth, int screenHeight)
    : size(size), speed(speed), screenWidth(screenWidth), screenHeight(screenHeight),
      direction(3), timeSinceLastMove(0.0f), moveInterval(0.1f)
{

    sf::RectangleShape head(sf::Vector2f(size, size));
    head.setFillColor(sf::Color::Green);
    head.setPosition(screenWidth / 2, screenHeight / 2);
    parts.push_back(head);
}

void Snake::setSize(float size)
{
    this->size = size;
}

void Snake::setSpeed(float speed)
{
    this->speed = speed;
}

void Snake::setScreenWidth(int screenWidth)
{
    this->screenWidth = screenWidth;
}

void Snake::setScreenHeight(int screenHeight)
{
    this->screenHeight = screenHeight;
}

void Snake::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != 2)
        direction = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != 1)
        direction = 2;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != 4)
        direction = 3;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != 3)
        direction = 4;
}

void Snake::update(float deltaTime)
{
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove < moveInterval)
        return;
    timeSinceLastMove = 0;

    previousPositions.clear();
    for (auto &part : parts)
    {
        previousPositions.push_back(part.getPosition());
    }

    sf::Vector2f newPosition = parts[0].getPosition();
    switch (direction)
    {
    case 1:
        newPosition.y -= speed;
        if (newPosition.y < 0)
            newPosition.y = screenHeight - size;
        break;
    case 2:
        newPosition.y += speed;
        if (newPosition.y >= screenHeight)
            newPosition.y = 0;
        break;
    case 3:
        newPosition.x += speed;
        if (newPosition.x >= screenWidth)
            newPosition.x = 0;
        break;
    case 4:
        newPosition.x -= speed;
        if (newPosition.x < 0)
            newPosition.x = screenWidth - size;
        break;
    }
    parts[0].setPosition(newPosition);

    for (size_t i = 1; i < parts.size(); ++i)
    {
        parts[i].setPosition(previousPositions[i - 1]);
    }
}

void Snake::grow(bool bigFood)
{
    sf::RectangleShape newPart(sf::Vector2f(size, size));
    newPart.setFillColor(sf::Color(0, 200, 0));
    newPart.setPosition(previousPositions.back());

    parts.push_back(newPart);
    if (bigFood)
        parts.push_back(newPart);

    moveInterval = std::max(moveInterval - SPEED_INCREMENT, MIN_INTERVAL);
}

bool Snake::checkSelfCollision() const
{
    const auto &head = parts[0];
    for (size_t i = 1; i < parts.size(); ++i)
    {
        if (head.getGlobalBounds().intersects(parts[i].getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void Snake::draw(sf::RenderWindow &window) const
{
    for (const auto &part : parts)
    {
        window.draw(part);
    }
}

sf::RectangleShape Snake::getHead() const
{
    return parts[0];
}

std::vector<sf::RectangleShape> Snake::getParts() const
{
    return parts;
}
