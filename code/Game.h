#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <iostream>

class Game
{
public:
	Game(int board_size);
	void run();
private:
	sf::RenderWindow window;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::Image windowIcon;
	std::vector<std::vector<sf::Sprite>> x_o_s;
	std::vector<std::vector<int>> state;
	sf::Texture x_o_texture;

	int board_size = 3;

	int max_ = 1, min_ = -1;

	int x_o_textureSize = 81;
	int grid_textureSize = 300;
	int cellSize = 81;
	int gridPaddings = 3;
	int gridStartX = 27;
	int gridStartY = 27;

	std::pair<int, int> getClickedCell();
	void fillWithX_O();
	void fillIndividualCell(char mark, std::pair<int, int> cell_coordinates);

	int minimax(std::vector<std::vector<int>> curr_state);

	enum class TerminateValues;
	enum class CellValues;

	CellValues current_player;
	bool terminal(std::vector<std::vector<int>> curr_state);
	int value(std::vector<std::vector<int>> curr_state);
	int player(std::vector<std::vector<int>> curr_state);
	std::vector<std::pair<int, int>> actions(std::vector<std::vector<int>> curr_state);
	std::vector<std::vector<int>> result(std::vector<std::vector<int>> curr_state, std::pair<int, int> act, int x_o);
	
	bool end_alert = 0;
	int grid_size = 3;

	void processEvents();
	void update();
	void render();

};

#endif
