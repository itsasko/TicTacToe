#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

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

	std::pair<int, int> getClickedCell();
	void fillWithX_O();

	void processEvents();
	void update();
	void render();

};

#endif
