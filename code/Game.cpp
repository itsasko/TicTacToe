#include "Game.h"
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