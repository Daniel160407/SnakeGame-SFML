#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Menu.hpp"

Menu::Menu(int width, int height) 
    : windowWidth(width), windowHeight(height), 
      selectedLevel(MEDIUM), enableWalls(true), startGame(false),
      hoveredItem(NONE), time(0) {
    if (!font.loadFromFile("src/fonts/Pixel_Game.otf")) {
        std::cerr << "Failed to load menu font!" << std::endl;
    }
    if (!backgroundTex.loadFromFile("src/textures/background.png")) {
        std::cerr << "Failed to load menu background!" << std::endl;
    }
    if (!clickSoundBuffer.loadFromFile("src/sounds/click.wav")) {
        std::cerr << "Failed to load menu click sound!" << std::endl;
    }
    
    background.setTexture(backgroundTex);
    background.setScale(
        float(width) / backgroundTex.getSize().x,
        float(height) / backgroundTex.getSize().y
    );
    
    clickSound.setBuffer(clickSoundBuffer);
    initializeElements();
}

void Menu::initializeElements() {
    titleText.setFont(font);
    titleText.setString("SNAKE GAME");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color(0, 255, 100));
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(3);
    titleText.setPosition(windowWidth/2 - titleText.getLocalBounds().width/2, 50);

    levelText.setFont(font);
    levelText.setString("GAME LEVEL");
    levelText.setCharacterSize(36);
    levelText.setFillColor(sf::Color(200, 200, 200));
    levelText.setPosition(windowWidth/2 - levelText.getLocalBounds().width/2, 180);

    easyText.setFont(font);
    easyText.setString("EASY");
    easyText.setCharacterSize(32);
    easyText.setPosition(windowWidth/2 - 250, 240);

    mediumText.setFont(font);
    mediumText.setString("MEDIUM");
    mediumText.setCharacterSize(32);
    mediumText.setPosition(windowWidth/2 - mediumText.getLocalBounds().width/2, 240);

    hardText.setFont(font);
    hardText.setString("HARD");
    hardText.setCharacterSize(32);
    hardText.setPosition(windowWidth/2 + 150, 240);

    wallsText.setFont(font);
    wallsText.setString("WALLS");
    wallsText.setCharacterSize(36);
    wallsText.setFillColor(sf::Color(200, 200, 200));
    wallsText.setPosition(windowWidth/2 - wallsText.getLocalBounds().width/2, 320);

    wallsToggleText.setFont(font);
    wallsToggleText.setString(enableWalls ? "ON" : "OFF");
    wallsToggleText.setCharacterSize(32);
    wallsToggleText.setPosition(windowWidth/2 - wallsToggleText.getLocalBounds().width/2, 370);
    wallsToggleText.setFillColor(enableWalls ? sf::Color(0, 200, 0) : sf::Color(200, 0, 0));

    playButton.setSize(sf::Vector2f(300, 80));
    playButton.setPosition(windowWidth/2 - 150, 450);
    playButton.setFillColor(sf::Color(50, 50, 50, 200));
    playButton.setOutlineThickness(0);
    playButton.setOutlineColor(sf::Color::White);

    playText.setFont(font);
    playText.setString("START GAME");
    playText.setCharacterSize(40);
    playText.setPosition(
        windowWidth/2 - playText.getLocalBounds().width/2,
        450 + (80 - playText.getLocalBounds().height)/2
    );

    snakeIcon.setSize(sf::Vector2f(100, 100));
    snakeIcon.setPosition(50, windowHeight - 150);
    snakeIcon.setFillColor(sf::Color(0, 255, 100, 100));

    updateSelectionVisuals();
}

void Menu::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            selectedLevel = std::max(selectedLevel - 1, 0);
            updateSelectionVisuals();
            clickSound.play();
        }
        else if (event.key.code == sf::Keyboard::Right) {
            selectedLevel = std::min(selectedLevel + 1, 2);
            updateSelectionVisuals();
            clickSound.play();
        }
        else if (event.key.code == sf::Keyboard::Space || 
                 event.key.code == sf::Keyboard::Enter) {
            enableWalls = !enableWalls;
            wallsToggleText.setString(enableWalls ? "ON" : "OFF");
            wallsToggleText.setFillColor(enableWalls ? sf::Color(0, 200, 0) : sf::Color(200, 0, 0));
            clickSound.play();
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        hoveredItem = NONE;
        
        if (easyText.getGlobalBounds().contains(mousePos) || 
            mediumText.getGlobalBounds().contains(mousePos) || 
            hardText.getGlobalBounds().contains(mousePos)) {
            hoveredItem = LEVEL_OPTION;
        }
        else if (wallsToggleText.getGlobalBounds().contains(mousePos)) {
            hoveredItem = WALLS_TOGGLE;
        }
        else if (playButton.getGlobalBounds().contains(mousePos)) {
            hoveredItem = PLAY_BUTTON;
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            
            if (easyText.getGlobalBounds().contains(mousePos)) {
                selectedLevel = EASY;
                updateSelectionVisuals();
                clickSound.play();
            }
            else if (mediumText.getGlobalBounds().contains(mousePos)) {
                selectedLevel = MEDIUM;
                updateSelectionVisuals();
                clickSound.play();
            }
            else if (hardText.getGlobalBounds().contains(mousePos)) {
                selectedLevel = HARD;
                updateSelectionVisuals();
                clickSound.play();
            }
            else if (wallsToggleText.getGlobalBounds().contains(mousePos)) {
                enableWalls = !enableWalls;
                wallsToggleText.setString(enableWalls ? "ON" : "OFF");
                wallsToggleText.setFillColor(enableWalls ? sf::Color(0, 200, 0) : sf::Color(200, 0, 0));
                clickSound.play();
            }
            else if (playButton.getGlobalBounds().contains(mousePos)) {
                startGame = true;
                clickSound.play();
            }
        }
    }
}

void Menu::updateSelectionVisuals() {
    easyText.setFillColor(sf::Color(150, 150, 150));
    mediumText.setFillColor(sf::Color(150, 150, 150));
    hardText.setFillColor(sf::Color(150, 150, 150));
    
    easyText.setStyle(sf::Text::Regular);
    mediumText.setStyle(sf::Text::Regular);
    hardText.setStyle(sf::Text::Regular);
    
    switch(selectedLevel) {
        case EASY:
            easyText.setFillColor(sf::Color(0, 255, 100));
            easyText.setStyle(sf::Text::Bold);
            break;
        case MEDIUM:
            mediumText.setFillColor(sf::Color(255, 200, 0));
            mediumText.setStyle(sf::Text::Bold);
            break;
        case HARD:
            hardText.setFillColor(sf::Color(255, 50, 50));
            hardText.setStyle(sf::Text::Bold);
            break;
    }
}

void Menu::update(float deltaTime) {
    time += deltaTime;
    
    float titleScale = 1.0f + 0.05f * sin(time * 2.0f);
    titleText.setScale(titleScale, titleScale);
    titleText.setPosition(
        windowWidth/2 - titleText.getLocalBounds().width * titleScale/2,
        50 - 10 * sin(time * 1.5f)
    );
    
    snakeIcon.setRotation(sin(time) * 15.0f);
    snakeIcon.setPosition(
        50 + 10 * cos(time * 0.7f),
        windowHeight - 150 + 10 * sin(time * 0.5f)
    );
    
    switch(hoveredItem) {
        case LEVEL_OPTION:
            levelText.setFillColor(sf::Color::White);
            break;
        case WALLS_TOGGLE:
            wallsText.setFillColor(sf::Color::White);
            wallsToggleText.setScale(1.1f, 1.1f);
            break;
        case PLAY_BUTTON:
            playButton.setFillColor(sf::Color(80, 80, 80, 220));
            playButton.setOutlineThickness(2);
            playText.setScale(1.05f, 1.05f);
            break;
        default:
            levelText.setFillColor(sf::Color(200, 200, 200));
            wallsText.setFillColor(sf::Color(200, 200, 200));
            wallsToggleText.setScale(1.0f, 1.0f);
            playButton.setFillColor(sf::Color(50, 50, 50, 200));
            playButton.setOutlineThickness(0);
            playText.setScale(1.0f, 1.0f);
            break;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(snakeIcon);
    
    sf::RectangleShape titleBg(sf::Vector2f(titleText.getLocalBounds().width + 40, 
                                       titleText.getLocalBounds().height + 20));
    titleBg.setPosition(titleText.getPosition().x - 20, titleText.getPosition().y - 10);
    titleBg.setFillColor(sf::Color(0, 0, 0, 150));
    titleBg.setOutlineColor(sf::Color(0, 255, 100, 100));
    titleBg.setOutlineThickness(2);
    window.draw(titleBg);
    window.draw(titleText);
    
    sf::RectangleShape levelBg(sf::Vector2f(windowWidth - 100, 120));
    levelBg.setPosition(50, 170);
    levelBg.setFillColor(sf::Color(0, 0, 0, 120));
    levelBg.setOutlineColor(sf::Color(100, 100, 100, 100));
    levelBg.setOutlineThickness(1);
    window.draw(levelBg);
    
    window.draw(levelText);
    window.draw(easyText);
    window.draw(mediumText);
    window.draw(hardText);
    
    sf::RectangleShape wallsBg(sf::Vector2f(windowWidth - 100, 120));
    wallsBg.setPosition(50, 310);
    wallsBg.setFillColor(sf::Color(0, 0, 0, 120));
    wallsBg.setOutlineColor(sf::Color(100, 100, 100, 100));
    wallsBg.setOutlineThickness(1);
    window.draw(wallsBg);
    
    window.draw(wallsText);
    window.draw(wallsToggleText);
    
    if (hoveredItem == PLAY_BUTTON) {
        sf::CircleShape glow(200, 30);
        glow.setPosition(windowWidth/2 - 200, 430);
        glow.setFillColor(sf::Color(0, 255, 100, 30));
        window.draw(glow);
    }
    
    window.draw(playButton);
    window.draw(playText);
    
    sf::Text versionText;
    versionText.setFont(font);
    versionText.setString("v1.0 © 2025");
    versionText.setCharacterSize(20);
    versionText.setFillColor(sf::Color(150, 150, 150, 150));
    versionText.setPosition(windowWidth - versionText.getLocalBounds().width - 20, 
                          windowHeight - 30);
    window.draw(versionText);
}

bool Menu::shouldStartGame() const {
    return startGame;
}

int Menu::getGameLevel() const {
    return selectedLevel;
}

bool Menu::getEnableWalls() const {
    return enableWalls;
}