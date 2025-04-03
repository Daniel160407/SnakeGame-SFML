// Food.hpp
#ifndef FOOD_HPP
#define FOOD_HPP

class Food {
private:
    float posX;
    float posY;
    bool bigFood;
public:
    Food(float posX, float posY);
    
    float getPosX() const;
    float getPosY() const;
    bool isBigFood() const;
    
    void setPosX(float posX);
    void setPosY(float posY);
    void setBigFood(bool bigFood);
    ~Food();
};

#endif