#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	void init(sf::Vector2f t_pos);
	void render(sf::RenderWindow& t_window);

	Player();

private:
	sf::RectangleShape m_player;
};
