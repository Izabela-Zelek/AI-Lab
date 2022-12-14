
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NPC.h"

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

	Player m_player;
	NPC m_npc;

	bool m_exitGame;
};

#endif

