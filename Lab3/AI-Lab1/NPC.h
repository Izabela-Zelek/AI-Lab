#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
enum class Type { SEEK, FLEE, WANDER, ARRIVE, PURSUE, OTHERARRIVE };
class NPC
{
public:
	NPC();
	~NPC();

	void initialize(int enemyType,sf::Font& t_font);
	void update(sf::Vector2f t_targetPos, sf::Vector2f t_targetVelocity);
	void draw(sf::RenderWindow& t_window);
	sf::Vector2f seek(sf::Vector2f t_targetPosition);
	sf::Vector2f arrive(sf::Vector2f t_targetPos);
	sf::Vector2f flee(sf::Vector2f t_targetPos);
	sf::Vector2f wander();
	sf::Vector2f pursue(sf::Vector2f t_targetPos, sf::Vector2f t_targetVelocity);
	sf::Vector2f normalize(sf::Vector2f normVector);
	float getNewOrientation();

	//TWAS A FAIL, I'M AFRAID
	//float face(sf::Vector2f targetPos);
	//float align(float targetRot);

	void setVisionCone(sf::Vector2f t_targetPos);
	void checkBoundary();

private:

	sf::Texture m_npcTexture;
	sf::Sprite m_npcSprite;
	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;

	
	float m_maxAcceleration = 66.6f;	//prev 200
	float m_speed = 50.0f;
	float m_maxSpeed = 100.0f; //prev 300
	float m_rotation = 90.0f; //prev 270
	float m_radianCalculation = 3.1415926536 / 180;
	float angleOfSight = 35;
	float m_angularVelocity;
	bool m_targetReached = true;
	Type m_npcType;
	std::string m_enemyTexture;
	std::string m_enemyTitleText;

	sf::Clock clock;
	sf::Time dt;
	sf::Text m_title;
	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_direction = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 3 }; //defines starting position of enemy, considering screen size 
};
#endif