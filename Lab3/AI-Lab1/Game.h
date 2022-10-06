
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

	void initBG(); //initialises background texture and pos

	sf::RenderWindow m_window;

	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;


	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 }; 	//defines centre of screen, considering screen size

	Player m_player;
	NPC m_seekNpc;
	NPC m_fleeNpc;
	NPC m_wanderNpc;
	NPC m_arriveNpc;
	NPC m_pursueNpc;

	bool m_exitGame;
};

#endif

