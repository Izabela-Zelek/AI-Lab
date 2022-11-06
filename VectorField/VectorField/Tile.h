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
	void changeColour(sf::Color t_color);
	void addCost(int t_cost);
	void addIntegrationField(float t_integrationField);
	void rotateVectorField(float t_rot, bool t_target);
	void changeMode(int t_mode);
	void setBoundary();
	void heatMap(sf::Color t_color);

	bool getTraversable() { return m_traversable; }

	int getCost() { return m_cost; }
	int getRotation() { return m_tile.getRotation(); }

	float getXPos() { return m_tile.getPosition().x; }
	float getYPos() { return m_tile.getPosition().y; }
	float getIntegrationField() { return integrationField; }
	float getVectorLineRotation() { return m_vectorLine.getRotation(); }
	sf::FloatRect getGlobalBounds();

	sf::Color colour;

private:
	bool m_traversable;
	int m_cost = -1;
	bool m_showCost = false;
	bool m_showCostField = false;
	bool m_showVectorField = false;
	float integrationField = -1;
	sf::RectangleShape m_tile;

	sf::Text m_costText;

	sf::RectangleShape m_vectorLine;
};

#endif // !TILE_HPP

