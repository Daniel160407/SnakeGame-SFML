#ifndef WALLS_GENERATOR_HPP
#define WALLS_GENERATOR_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Wall.hpp"

constexpr int TILE_SIZE = 20;
constexpr int WALLS_AMOUNT = 15;

class WallsGenerator {
private:
    int screenWidth;
    int screenHeight;
    std::vector<Wall> walls;
    std::vector<sf::RectangleShape> generatedWalls;

public:
    WallsGenerator(int screenWidth, int screenHeight);
    
    std::vector<sf::RectangleShape> getGeneratedWalls();
    void generateWalls(float snakePosX, float snakePosY);
    void drawWalls(sf::RenderWindow &window);
    bool isCollidingWithWall(const sf::FloatRect &bounds) const;
    void clearWalls();
};

#endif
