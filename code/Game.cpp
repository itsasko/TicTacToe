#include "Game.h"
#include <utility>
#include <iostream>

Game::Game() : window(sf::VideoMode(300, 300), "fxx") {
    windowIcon.loadFromFile("images/icon.png");
    window.setIcon(80, 80, windowIcon.getPixelsPtr());
    background.loadFromFile("images/grid.png");
    backgroundSprite.setTexture(background);
    x_o_s.resize(3, std::vector<sf::Sprite>(3));
    cell_occupation_state.resize(3, std::vector<int>(3, 0));
    x_o_texture.loadFromFile("images/x_o.png");
    fillWithX_O();
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
                if (!cell_occupation_state[pair.first][pair.second]) {
                    x_o_s[pair.first][pair.second].setTextureRect(sf::IntRect(0, 81, 81, 81));
                    cell_occupation_state[pair.first][pair.second] = 1;
                    std::cout << pair.first << " " << pair.second << std::endl;
                }
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
    for (auto i : x_o_s) {
        for (auto j : i) {
            window.draw(j);
        }
    }
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

void Game::fillWithX_O() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            x_o_s[i][j].setTexture(x_o_texture);
            x_o_s[i][j].setPosition(27 + j * (81 + 3), 27 + i * (81 + 3));
            x_o_s[i][j].setTextureRect(sf::IntRect(0, 0, 81, 81));
        }
    }
}