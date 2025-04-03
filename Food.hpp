// Food.hpp
#ifndef FOOD_HPP
#define FOOD_HPP

class Food {
private:
    float posX;
    float posY;
public:
    Food(float posX, float posY);
    
    float getPosX() const;
    float getPosY() const;
    
    void setPosX(float posX);
    void setPosY(float posY);
    ~Food();
};

#endif