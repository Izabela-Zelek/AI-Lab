
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;

	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 }; 	//defines centre of screen, considering screen size

	bool m_exitGame;
	int enemyCount;
	int ownArmyCount;
	float enemyRandY;

	std::vector<Enemy> m_enemy;
};

#endif

