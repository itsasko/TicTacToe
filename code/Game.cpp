#include "Game.h"
#include <utility>
#include <iostream>

Game::Game() : window(sf::VideoMode(300, 300), "fxx") {
    windowIcon.loadFromFile("images/icon.png");
    window.setIcon(80, 80, windowIcon.getPixelsPtr());
    background.loadFromFile("images/grid.png");
    backgroundSprite.setTexture(background);
}

void Game::run() {
    // Game loop
    while (window.isOpen()) {
        processEvents();
        update();
        render();

    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::pair<int, int> pair = getClickedCell();
                std::cout << pair.first << " " << pair.second << std::endl;
            }
            break;
        }
    }
}

void Game::update() {

}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.display();
}

std::pair<int, int> Game::getClickedCell() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    int gridStartX = 27;
    int gridStartY = 27;
    int cellSize = 81;
    int padding = 3;

    int adjustedX = mousePos.x - gridStartX;
    int adjustedY = mousePos.y - gridStartY;

    if (adjustedX < 0 || adjustedY < 0 || adjustedX >= 300 || adjustedY >= 300) {
        return { -1, -1 };
    }

    int row = adjustedY / (cellSize + padding);
    int col = adjustedX / (cellSize + padding);

    return { row, col };
}