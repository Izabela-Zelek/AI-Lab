#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	void initialize();
	void update();
	void draw(sf::RenderWindow & t_window);
	void getInput();
	void checkBoundary();

	sf::Vector2f getPlayerPos() { return m_playerSprite.getPosition(); }
	sf::Vector2f getPlayerVelocity() { return m_velocity; }

private:

	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;

	const float MAX_SPEED = 8.0f;
	const float SPEED_INCREMENT = 2.0f;
	const float ROTATION_INCREMENT = 3.0f;

	float m_radianCalculation = 3.1415926536 / 180;
	float m_speed = 4.0f;
	float m_rotation = 0.0f;
	
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 7,sf::VideoMode::getDesktopMode().height / 7 }; //defines starting position of player, considering screen size 
};
#endif