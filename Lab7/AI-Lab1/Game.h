
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Player.h"
#include "FuzzySet.h"
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
	void initBG();
	void generate();

	sf::RenderWindow m_window;

	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 }; 	//defines centre of screen, considering screen size

	bool m_exitGame;

	int enemyCount;
	int m_ownArmyCount;

	float enemyRandY;
	float playerY;

	std::vector<Enemy> m_enemy;
	std::vector<Player> m_player;

	sf::RectangleShape m_FarLine;
	sf::RectangleShape m_MediumLine;
	sf::Font m_font;
	sf::Text m_FarText;
	sf::Text m_MediumText;
	sf::Text m_CloseText;

	FuzzySet fuzzySet;

	float m_Tiny;
	float m_Small;
	float m_Moderate;
	float m_Large;

	float m_Close;
	float m_MediumDistance;
	float m_Far;

	float m_Low;
	float m_Medium;
	float m_High;
};

#endif

