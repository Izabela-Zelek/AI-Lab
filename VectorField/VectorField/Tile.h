/// <summary>
/// author Izabela Zelek October 2022
/// </summary>
#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
public:
	Tile(sf::Vector2f size, sf::Vector2f pos);
	~Tile();

	void render(sf::RenderWindow& t_window);
	sf::FloatRect passGlobalBounds();
	void changeColour(sf::Color t_color);
private:
	bool traversable;
	sf::RectangleShape m_tile;
};

#endif // !TILE_HPP

