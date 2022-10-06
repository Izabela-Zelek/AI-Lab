
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
	sf::Font m_font;
	sf::Text m_instructions;
	std::string m_instrucText= "Toggle enemies by using numpad:\n1 - Seek\n2 - Wander\n3 - Slow Arrive\n4 - Pursue\n5 - Fast Arrive";

	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 }; 	//defines centre of screen, considering screen size

	Player m_player;
	NPC m_seekNpc;
	NPC m_fleeNpc;
	NPC m_wanderNpc;
	NPC m_arriveNpc;
	NPC m_otherArriveNpc;
	NPC m_pursueNpc;

	bool m_exitGame;
	int m_instrucOffset = 20;
	static const int NUM_ENEMY = 5;

	bool EnemyAlive[NUM_ENEMY] = {true,true,true,true,true};
};

#endif

