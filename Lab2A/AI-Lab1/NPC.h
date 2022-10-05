#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <iostream>

class NPC
{
public:
	NPC();
	~NPC();

	void initialize();
	void update();
	void draw(sf::RenderWindow& t_window);

private:

	sf::Texture m_npcTexture;
	sf::Sprite m_npcSprite;

	float m_speed = 7.0f;
	float m_rotation = 270.0f;
	float m_radianCalculation = 3.1415926536 / 180;

	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 3 }; //defines starting position of enemy, considering screen size 
};
#endif