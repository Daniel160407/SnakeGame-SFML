#include "Wall.hpp"

Wall::Wall() {}

Wall::Wall(int width, int height, int posX, int posY) 
    : width(width), height(height), posX(posX), posY(posY) {}

int Wall::getWidth() const {
    return width;
}

int Wall::getHeight() const {
    return height;
}

int Wall::getPosX() const {
    return posX;
}

int Wall::getPosY() const {
    return posY;
}

void Wall::setWidth(int width) {
    this->width = width;
}

void Wall::setHeight(int height) {
    this->height = height;
}

void Wall::setPosX(int posX) {
    this->posX = posX;
}

void Wall::setPosY(int posY) {
    this->posY = posY;
}
