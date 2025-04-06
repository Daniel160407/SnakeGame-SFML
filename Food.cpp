#include "Food.hpp"

Food::Food(float posX, float posY, float foodSize) : posX(posX), posY(posY), foodSize(foodSize) {}

float Food::getPosX() const
{
    return posX;
}

float Food::getPosY() const
{
    return posY;
}

float Food::getFoodSize() const
{
    return foodSize;
}

bool Food::isBigFood() const
{
    return bigFood;
}

void Food::setPosX(float posX)
{
    this->posX = posX;
}

void Food::setPosY(float posY)
{
    this->posY = posY;
}

void Food::setBigFood(bool bigFood)
{
    this->bigFood = bigFood;
}

void Food::draw(sf::RenderWindow &window)
{
    sf::CircleShape foodShape(bigFood ? foodSize + 10 : foodSize);
    foodShape.setPosition(posX, posY);
    foodShape.setFillColor(bigFood ? sf::Color::Blue : sf::Color::Red);
    window.draw(foodShape);
}

Food::~Food()
{
}