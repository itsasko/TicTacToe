#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

	std::pair<int, int> getClickedCell();

	void processEvents();
	void update();
	void render();

};

#endif
