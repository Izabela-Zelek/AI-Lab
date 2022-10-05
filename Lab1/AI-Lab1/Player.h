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

private:

	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;

	bool m_headingRight = true;
	float m_speed = 5.0f;
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 };
};
#endif