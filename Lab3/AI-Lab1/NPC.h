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
	sf::Vector2f seek(sf::Vector2f t_targetPosition);
	sf::Vector2f arrive(sf::Vector2f t_targetPos);
	sf::Vector2f flee(sf::Vector2f t_targetPos);
	sf::Vector2f wander();
	sf::Vector2f normalize(sf::Vector2f normVector);
	float getNewOrientation();
	float face(sf::Vector2f targetPos);
	void setVisionCone(sf::Vector2f t_targetPos);
	void checkBoundary();

private:

	sf::Texture m_npcTexture;
	sf::Sprite m_npcSprite;
	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;

	
	float m_maxAcceleration = 20.0f;
	float m_speed = 10.0f;
	float m_rotation = 270.0f;
	float m_radianCalculation = 3.1415926536 / 180;
	float angleOfSight = 35;
	bool m_targetReached = true;
	Type m_npcType;
	std::string m_enemyTexture;

	sf::Clock clock;
	sf::Time dt;
	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_direction = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 3 }; //defines starting position of enemy, considering screen size 
};
#endif