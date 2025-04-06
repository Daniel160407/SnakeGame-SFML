#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu {
public:
    enum GameLevel { EASY = 0, MEDIUM = 1, HARD = 2 };
    enum HoveredItem { NONE, LEVEL_OPTION, WALLS_TOGGLE, PLAY_BUTTON };

    Menu(int width, int height);
    
    // Main interface methods
    void handleEvent(sf::Event& event);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Accessors
    bool shouldStartGame() const;
    int getGameLevel() const;
    bool getEnableWalls() const;

private:
    // Visual elements
    sf::Texture backgroundTex;
    sf::Sprite background;
    sf::Font font;
    
    // Text elements
    sf::Text titleText;
    sf::Text levelText;
    sf::Text easyText;
    sf::Text mediumText;
    sf::Text hardText;
    sf::Text wallsText;
    sf::Text wallsToggleText;
    sf::Text playText;
    
    // Interactive elements
    sf::RectangleShape playButton;
    sf::RectangleShape snakeIcon;
    
    // Audio
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    
    // State variables
    int selectedLevel;
    bool enableWalls;
    bool startGame;
    int windowWidth;
    int windowHeight;
    HoveredItem hoveredItem;
    float time;
    
    // Helper methods
    void initializeElements();
    void updateSelectionVisuals();
};

#endif