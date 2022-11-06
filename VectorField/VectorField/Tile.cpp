#include "Tile.h"

Tile::Tile(sf::Vector2f size, sf::Vector2f pos,sf::Font& t_font)
{
	m_tile.setSize(size);
	m_tile.setOrigin(m_tile.getLocalBounds().width / 2, m_tile.getLocalBounds().height / 2);
	m_tile.setPosition(pos);
	

	if (std::rand() % 10 == 0)
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
	m_costText.setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 191.25f));
	m_costText.setPosition(m_tile.getPosition());

	m_vectorLine.setSize({ 1.0f,1.0f });
	m_vectorLine.setPosition(pos);
	m_vectorLine.setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 191.25f));
}

Tile::~Tile()
{
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
	if (m_showCostField && m_showCost && m_traversable)
	{
		t_window.draw(m_costText);
	}

	if (m_showCost && m_showVectorField && m_traversable)
	{
		t_window.draw(m_vectorLine);
	}

}

sf::FloatRect Tile::getGlobalBounds()
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

void Tile::addIntegrationField(float t_integrationField)
{
	integrationField = t_integrationField;
}

void Tile::rotateVectorField(float t_rot, bool t_target)
{
	if (!t_target)
	{
		m_vectorLine.setSize({ m_tile.getSize().x / 2,1.0f });
		m_vectorLine.setRotation(t_rot);
	}
	else
	{
		m_vectorLine.setSize({ 1.0f,1.0f });
	}
}

void Tile::changeMode(int t_mode)
{
	switch (t_mode)
	{
	case 0:
		m_showCostField = false;
		m_showVectorField = false;
		break;
	case 1:
		m_showCostField = true;
		m_showVectorField = false;
		break;
	case 2:
		m_showCostField = false;
		m_showVectorField = true;
		break;
	default:
		break;
	}
}

void Tile::setBoundary()
{
	m_traversable = false;
	m_tile.setFillColor(sf::Color::Black);

}

void Tile::heatMap(sf::Color t_color)
{
	if (m_traversable)
	{
		if (t_color != sf::Color(15, 138, 48) && t_color != sf::Color(209, 15, 15))
		{
			m_tile.setFillColor(t_color);
			colour = t_color;
		}
	}
}


