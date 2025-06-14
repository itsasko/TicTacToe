#include "Game.h"

Game::Game(int board_size_) : grid_textureSize(board_size_ *100), window(sf::VideoMode(board_size_ * 100, board_size_ * 100), "tic-tac-toe") {
    windowIcon.loadFromFile("images/icon.png");
    board_size = board_size_;
    window.setIcon(80, 80, windowIcon.getPixelsPtr());
    switch (board_size){
    case 3:
        background.loadFromFile("images/grid.png");
        break;
    case 4:
        background.loadFromFile("images/grid4.png");
        grid_textureSize = 400;
        cellSize = 92;
        gridPaddings = 4;
        gridStartX = 10;
        gridStartY = 10;
        break;

    }   
    backgroundSprite.setTexture(background);
    x_o_s.resize(board_size, std::vector<sf::Sprite>(board_size));
    state.resize(board_size, std::vector<int>(board_size, 0));
    x_o_texture.loadFromFile("images/x_o.png");
    fillWithX_O();
}

enum class Game::TerminateValues {
    MAX = 1,
    ZERO = 0,
    MIN = -1
};

enum class Game::CellValues {
    EMPTY,
    MARK_X,
    MARK_O
};

void Game::run() {
    current_player = CellValues::MARK_X;
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
                if (!terminal(state) && current_player == CellValues::MARK_X) {
                    std::pair<int, int> cell_coordinates = getClickedCell();
                    if (!state[cell_coordinates.first][cell_coordinates.second]) {
                        fillIndividualCell('x', cell_coordinates);
                        state[cell_coordinates.first][cell_coordinates.second] = 1;
                        current_player = CellValues::MARK_O;
                    }
                }
            }
            break;
        }
    }
}

void Game::update() {
    if (!terminal(state) && current_player == CellValues::MARK_O) {
        int new_min_value = 100, min_value = 100;
        std::vector<std::vector<int>> possible_state = state;
        std::vector<std::pair<int, int>> possible_actions = actions(state);
        std::pair<int, int> optimal_coord;
        for (auto i : possible_actions) {
            possible_state[i.first][i.second] = 2;
            new_min_value = minimax(possible_state);
            if (new_min_value < min_value) {
                min_value = new_min_value;
                optimal_coord = i;
            }
            possible_state[i.first][i.second] = 0;
        }
        fillIndividualCell('o', optimal_coord);
        state[optimal_coord.first][optimal_coord.second] = 2;
        current_player = CellValues::MARK_X;
    }
    else if (terminal(state) && !end_alert) {
        std::cout << "end";
        end_alert = 1;
    }
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

    int adjustedX = mousePos.x - gridStartX;
    int adjustedY = mousePos.y - gridStartY;

    if (adjustedX < 0 || adjustedY < 0 || adjustedX >= grid_textureSize || adjustedY >= grid_textureSize) {
        return { -1, -1 };
    }

    int row = adjustedY / (cellSize + gridPaddings);
    int col = adjustedX / (cellSize + gridPaddings);

    return { row, col };
}

void Game::fillWithX_O() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            x_o_s[i][j].setTexture(x_o_texture);
            x_o_s[i][j].setPosition(gridStartX + j * (cellSize + gridPaddings), gridStartY + i * (cellSize + gridPaddings));
            fillIndividualCell('e', { i, j });
        }
    }
}

void Game::fillIndividualCell(char mark, std::pair<int, int> cell_coordinates) {
    if (mark == 'x') {
        x_o_s[cell_coordinates.first][cell_coordinates.second].setTextureRect(sf::IntRect(0, 1* x_o_textureSize, x_o_textureSize, x_o_textureSize));
    }
    else if (mark == 'o') {
        x_o_s[cell_coordinates.first][cell_coordinates.second].setTextureRect(sf::IntRect(0, 2* x_o_textureSize, x_o_textureSize, x_o_textureSize));
    }
    else {
        x_o_s[cell_coordinates.first][cell_coordinates.second].setTextureRect(sf::IntRect(0, 0, x_o_textureSize, x_o_textureSize));
    }
}

//Max is 1, Min is 2

int Game::minimax(std::vector<std::vector<int>> curr_state) {
    if (terminal(curr_state))
        return value(curr_state);
    if (player(curr_state) == 1) {
        int value_ = -100;
        for (auto a : actions(curr_state)) {
            value_ = std::max(value_, minimax(result(curr_state, a, 1)));
        }
        return value_;
    }
    else if (player(curr_state) == 2) {
        int value_ = 100;
        for (auto a : actions(curr_state)) {
            value_ = std::min(value_, minimax(result(curr_state, a, 2)));
        }
        return value_;
    }
}

bool Game::terminal(std::vector<std::vector<int>> curr_state) {
    bool isFull = true;
    int counter_x_row = 0;
    int counter_x_col = 0;
    int counter_o_row = 0;
    int counter_o_col = 0;

    for (int i = 0; i < board_size; i++) {
        counter_x_row = 0;
        counter_x_col = 0;
        counter_o_row = 0;
        counter_o_col = 0;

        for (int j = 0; j < board_size; j++) {

            if (curr_state[i][j] == 1) counter_x_row++;
            if (curr_state[i][j] == 2) counter_o_row++;

            if (curr_state[j][i] == 1) counter_x_col++;
            if (curr_state[j][i] == 2) counter_o_col++;

            if (curr_state[i][j] == 0) isFull = false;
        }
        if (counter_x_row == board_size || counter_x_col == board_size) return true;
        if (counter_o_row == board_size || counter_o_col == board_size) return true;
    }

    int counter_x_diag1 = 0, counter_o_diag1 = 0;
    int counter_x_diag2 = 0, counter_o_diag2 = 0;
    for (int i = 0; i < board_size; i++) {
        if (curr_state[i][i] == 1) counter_x_diag1++;
        if (curr_state[i][i] == 2) counter_o_diag1++;

        if (curr_state[i][board_size - i - 1] == 1) counter_x_diag2++;
        if (curr_state[i][board_size - i - 1] == 2) counter_o_diag2++;
    }

    if (counter_x_diag1 == board_size || counter_x_diag2 == board_size) return true;
    if (counter_o_diag1 == board_size || counter_o_diag2 == board_size) return true;
    return isFull;
}

int Game::value(std::vector<std::vector<int>> curr_state) {
    TerminateValues sum;
    bool isFull = true;
    int counter_x_row = 0;
    int counter_x_col = 0;
    int counter_o_row = 0;
    int counter_o_col = 0;

    for (int i = 0; i < board_size; i++) {
        counter_x_row = 0;
        counter_x_col = 0;
        counter_o_row = 0;
        counter_o_col = 0;

        for (int j = 0; j < board_size; j++) {

            if (curr_state[i][j] == 1) counter_x_row++;
            if (curr_state[i][j] == 2) counter_o_row++;

            if (curr_state[j][i] == 1) counter_x_col++;
            if (curr_state[j][i] == 2) counter_o_col++;

            if (curr_state[i][j] == 0) isFull = false;
        }
        if (counter_x_row == board_size || counter_x_col == board_size) sum = TerminateValues::MAX;
        if (counter_o_row == board_size || counter_o_col == board_size) sum = TerminateValues::MIN;
    }

    int counter_x_diag1 = 0, counter_o_diag1 = 0;
    int counter_x_diag2 = 0, counter_o_diag2 = 0;
    for (int i = 0; i < board_size; i++) {
        if (curr_state[i][i] == 1) counter_x_diag1++;
        if (curr_state[i][i] == 2) counter_o_diag1++;

        if (curr_state[i][board_size - i - 1] == 1) counter_x_diag2++;
        if (curr_state[i][board_size - i - 1] == 2) counter_o_diag2++;
    }

    if (counter_x_diag1 == board_size || counter_x_diag2 == board_size) sum = TerminateValues::MAX;
    if (counter_o_diag1 == board_size || counter_o_diag2 == board_size) sum = TerminateValues::MIN;
    if (isFull) sum = TerminateValues::ZERO;
    return static_cast<int>(sum);
}
int Game::player(std::vector<std::vector<int>> curr_state) {
    int counter_x = 0;
    int counter_o = 0;
    for (int i = 0; i < board_size; i++) {

        for (int j = 0; j < board_size; j++) {

            if (curr_state[i][j] == 1) counter_x++;
            if (curr_state[i][j] == 2) counter_o++;
        }
    }
    if (counter_x == counter_o) return 1;
    return 2;
}

std::vector<std::pair<int, int>> Game::actions(std::vector<std::vector<int>> curr_state) {
    std::vector<std::pair<int, int>> actions;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (curr_state[i][j] == 0) actions.push_back({ i, j });
        }
    }
    return actions;
}
std::vector<std::vector<int>> Game::result(std::vector<std::vector<int>> curr_state, std::pair<int, int> act, int x_o) {
    if (x_o == 1) curr_state[act.first][act.second] = 1;
    if (x_o == 2) curr_state[act.first][act.second] = 2;
    return curr_state;
}
