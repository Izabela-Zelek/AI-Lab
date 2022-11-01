#include "Tile.h"

Tile::Tile(sf::Vector2f size, sf::Vector2f pos,sf::Font& t_font)
{
	m_tile.setSize(size);
	m_tile.setOrigin(m_tile.getLocalBounds().width / 2, m_tile.getLocalBounds().height / 2);
	m_tile.setPosition(pos);

	if (std::rand() % 4 == 0)
	{
		m_traversable = false;
	}
	else
	{
		m_traversable = true;
	}

	if (m_traversable)
	{
		m_tile.setFillColor(sf::Color(64, 11, 60));
	}
	else
	{
		m_tile.setFillColor(sf::Color::Black);

	}
	m_tile.setOutlineColor(sf::Color(161, 138, 166));
	m_tile.setOutlineThickness(0.8f);

	m_costText.setFont(t_font);
	m_costText.setCharacterSize(10U); //20U
	m_costText.setFillColor(sf::Color::White);
	m_costText.setPosition(m_tile.getPosition());
}

Tile::~Tile()
{
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
	if (m_showCost)
	{
		t_window.draw(m_costText);
	}
}

sf::FloatRect Tile::passGlobalBounds()
{
	return m_tile.getGlobalBounds();
}

void Tile::changeColour(sf::Color t_color)
{
	if (m_traversable)
	{
		m_tile.setFillColor(t_color);
	}
}

void Tile::addCost(int t_cost)
{
	m_cost = t_cost;

	if (m_cost != -1)
	{
		m_costText.setString(std::to_string(m_cost));
		m_costText.setOrigin(m_costText.getLocalBounds().width / 1.3f, m_costText.getLocalBounds().height / 1.3f);
		m_costText.setPosition(m_tile.getPosition());
		m_showCost = true;
	}
	else
	{
		m_showCost = false;
	}
}

