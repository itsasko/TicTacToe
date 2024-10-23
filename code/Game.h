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
	Game();
	void run();
private:
	sf::RenderWindow window;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::Image windowIcon;
	std::vector<std::vector<sf::Sprite>> x_o_s;
	std::vector<std::vector<int>> cell_occupation_state;
	sf::Texture x_o_texture;

	int grid_textureSize = 300;
	int x_o_textureSize = 81;
	int gridPaddings = 3;

	std::pair<int, int> getClickedCell();
	void fillWithX_O();
	void fillIndividualCell(int figure, std::pair<int, int> cell_coordinates);

	void processEvents();
	void update();
	void render();

};

#endif
