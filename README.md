# 🐍 Snake Game (SFML)

A classic Snake game built with **C++** and **SFML**. Eat food, grow longer, avoid crashing into yourself or randomly generated walls!

![Screenshot 1](/src/screenshots/game.png)
![Screenshot 2](/src/screenshots/gameover.png)

---

## 🎮 Features

- Classic Snake movement and growth mechanics
- Randomly generated **walls** after every 10 food pieces
- **Big food** bonuses (worth extra points!)
- Real-time **score** and **timer** UI
- Sound effects: food eaten, game over
- Game over screen with restart option

---

## 🧰 Built With

- C++
- [SFML 2.5+](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)

---

## 🚀 How to Build and Run

### Prerequisites

- C++ Compiler (e.g. g++, clang++)
- SFML installed and configured properly

### Build (Linux/macOS)

```bash
g++ -std=c++17 -o SnakeGame main.cpp Game.cpp Snake.cpp Wall.cpp WallsGenerator.cpp Food.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
