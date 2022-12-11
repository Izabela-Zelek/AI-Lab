#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
public:
	void init(sf::Vector2f t_pos);
	void render(sf::RenderWindow& t_window);

	Enemy();

private:
	sf::RectangleShape m_enemy;
};
