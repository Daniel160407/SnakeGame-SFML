#include <SFML/Graphics.hpp>

#ifndef FOOD_HPP
#define FOOD_HPP

class Food {
private:
    float posX;
    float posY;
    float foodSize;
    bool bigFood;
public:
    Food(float posX, float posY, float foodSize);
    
    float getPosX() const;
    float getPosY() const;
    float getFoodSize() const;
    bool isBigFood() const;
    
    void setPosX(float posX);
    void setPosY(float posY);
    void setBigFood(bool bigFood);

    void draw(sf::RenderWindow& window);
    ~Food();
};

#endif