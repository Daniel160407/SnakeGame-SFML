#include "WallsGenerator.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

WallsGenerator::WallsGenerator(int screenWidth, int screenHeight, int wallsAmount)
    : screenWidth(screenWidth), screenHeight(screenHeight), wallsAmount(wallsAmount) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::vector<sf::RectangleShape> WallsGenerator::getGeneratedWalls() {
    return generatedWalls;
}

int WallsGenerator::getWallsAmount() const {
    return wallsAmount;
}

void WallsGenerator::setWallsAmount(int amount) {
    this->wallsAmount = amount;
}

void WallsGenerator::generateWalls(float snakePosX, float snakePosY) {
    walls.clear();
    for (int i = 0; i < wallsAmount; i++) {
        int wallPosX = (std::rand() % (screenWidth / TILE_SIZE)) * TILE_SIZE;
        int wallPosY = (std::rand() % (screenHeight / TILE_SIZE)) * TILE_SIZE;

        if (std::abs(wallPosX - static_cast<int>(snakePosX)) < TILE_SIZE &&
            std::abs(wallPosY - static_cast<int>(snakePosY)) < TILE_SIZE) {
            --i;
            continue;
        }

        Wall wall(1, 1, wallPosX, wallPosY);

        while ((std::rand() % 2) == 0) {
            wall.setWidth(wall.getWidth() + 1);
        }

        while ((std::rand() % 2) == 0) {
            wall.setHeight(wall.getHeight() + 1);
        }

        if ((wall.getPosX() + wall.getWidth() * TILE_SIZE > screenWidth) ||
            (wall.getPosY() + wall.getHeight() * TILE_SIZE > screenHeight)) {
            i--;
            continue;
        }

        sf::RectangleShape generatedWall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        generatedWall.setPosition(wall.getPosX(), wall.getPosY());

        generatedWalls.push_back(generatedWall);
        walls.push_back(wall);
    }
}

void WallsGenerator::drawWalls(sf::RenderWindow &window) {
    for (const auto &wall : walls) {
        sf::RectangleShape wallShape(sf::Vector2f(
            wall.getWidth() * TILE_SIZE,
            wall.getHeight() * TILE_SIZE
        ));
        wallShape.setFillColor(sf::Color(200, 250, 0));
        wallShape.setPosition(wall.getPosX(), wall.getPosY());

        window.draw(wallShape);
    }
}

bool WallsGenerator::isCollidingWithWall(const sf::FloatRect &bounds) const {
    for (const auto &wall : walls) {
        sf::FloatRect wallBounds(
            wall.getPosX(), wall.getPosY(),
            wall.getWidth() * TILE_SIZE,
            wall.getHeight() * TILE_SIZE
        );
        if (bounds.intersects(wallBounds)) {
            return true;
        }
    }
    return false;
}

void WallsGenerator::clearWalls() {
    walls.clear();
}
