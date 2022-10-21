#include "Tile.h"

Tile::Tile(sf::Vector2f size, sf::Vector2f pos)
{
	m_tile.setSize(size);
	m_tile.setOrigin(m_tile.getLocalBounds().width / 2, m_tile.getLocalBounds().height / 2);
	m_tile.setFillColor(sf::Color(64, 11, 60));
	m_tile.setOutlineColor(sf::Color(161, 138, 166));
	m_tile.setOutlineThickness(0.8f);
	m_tile.setPosition(pos);

	traversable = true;
}

Tile::~Tile()
{
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
}

sf::FloatRect Tile::passGlobalBounds()
{
	return m_tile.getGlobalBounds();
}

void Tile::changeColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
}
