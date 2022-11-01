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
	Tile(sf::Vector2f size, sf::Vector2f pos, sf::Font& t_font);
	~Tile();

	void render(sf::RenderWindow& t_window);
	sf::FloatRect passGlobalBounds();
	void changeColour(sf::Color t_color);
	void addCost(int t_cost);
	int getCost() { return m_cost; }
	float getXPos() { return m_tile.getPosition().x; }
private:
	bool m_traversable;
	int m_cost = -1;
	bool m_showCost = false;
	sf::RectangleShape m_tile;

	sf::Text m_costText;
};

#endif // !TILE_HPP

