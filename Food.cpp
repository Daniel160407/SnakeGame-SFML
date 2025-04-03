#include "Food.hpp"

Food::Food(float posX, float posY) : posX(posX), posY(posY) {}

float Food::getPosX() const {
    return posX;
}

float Food::getPosY() const {
    return posY;
}

void Food::setPosX(float posX) {
    this->posX = posX;
}

void Food::setPosY(float posY) {
    this->posY = posY;
}

Food::~Food() {
   
}