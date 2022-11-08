/// <summary>
/// author Izabela Zelek October 2022
/// </summary>
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	
	void init(sf::Vector2f t_size);
	void spawnPlayer(sf::Vector2f pos);
	void render(sf::RenderWindow& t_window);
	sf::Vector2f normalize(sf::Vector2f& source);
	bool movePlayer(sf::Vector2f t_pos);
	void resetValues();
	bool getNext() { return m_next; }
private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;
	sf::Vector2f m_direction;
	bool m_spawnPlayer = false;
	bool m_moving = true;
	bool m_next = false;
	int m_speed = 2;
};

#endif // !PLAYER_HPP