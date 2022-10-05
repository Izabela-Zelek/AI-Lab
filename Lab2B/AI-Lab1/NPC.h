#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
enum class Type { SEEK, FLEE, WANDER };
class NPC
{
public:
	NPC();
	~NPC();

	void initialize(int enemyType);
	void update(sf::Vector2f t_targetPos);
	void draw(sf::RenderWindow& t_window);
	void seek(sf::Vector2f t_targetPosition);
	void arrive(sf::Vector2f t_targetPos);
	void flee(sf::Vector2f t_targetPos);
	void wander();
	void normalize();
	float getNewOrientation();
	void checkBoundary();

private:

	sf::Texture m_npcTexture;
	sf::Sprite m_npcSprite;

	const float MAX_SPEED = 6.0f;
	float m_speed = 2.0f;
	float m_rotation = 270.0f;
	float m_radianCalculation = 3.1415926536 / 180;
	bool m_targetReached = true;
	Type m_npcType;
	std::string m_enemyTexture;

	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 3 }; //defines starting position of enemy, considering screen size 
};
#endif