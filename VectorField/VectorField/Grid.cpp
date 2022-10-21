#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			sf::Vector2f size = { (float)SCREEN_WIDTH / COL,(float)SCREEN_HEIGHT / ROW };
			sf::Vector2f pos = { size.x / 2 + size.x * (j), size.y / 2 +size.y * (i)};
			Tile m_square(size,pos);
			m_grid.push_back(m_square);
		}
	}
}

Grid::~Grid()
{
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		m_grid.at(i).render(t_window);
	}
}

void Grid::checkMouseInput(sf::RenderWindow& t_window, bool t_leftClick)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(t_window); // Mouse position relative to the window
	sf::Vector2f translated_pos = t_window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

	for (int i = 0; i < MAX_TILE; i++)
	{
		if (m_grid[i].passGlobalBounds().contains(translated_pos))
		{
			if (t_leftClick)
			{
				if(startChosen)
				{
					m_grid[m_interactables[0]].changeColour(sf::Color(64, 11, 60));
				}
				m_grid[i].changeColour(sf::Color::Green);
				startChosen = true;
				m_interactables[0] = i;
			}
			else
			{
				if (targetChosen)
				{
					m_grid[m_interactables[1]].changeColour(sf::Color(64, 11, 60));
				}
				m_grid[i].changeColour(sf::Color::Red);
				targetChosen = true;
				m_interactables[1] = i;

			}
		}
	}
}
