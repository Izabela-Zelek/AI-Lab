#include "Grid.h"

Grid::Grid()
{
	setUpFont();

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			sf::Vector2f size = { (float)SCREEN_WIDTH / COL,(float)SCREEN_HEIGHT / ROW };
			sf::Vector2f pos = { size.x / 2 + size.x * (j), size.y / 2 +size.y * (i)};
			Tile m_square(size,pos,m_font);
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
	int targetLoc = 0;
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (m_grid[i].passGlobalBounds().contains(translated_pos))
		{
			if (t_leftClick)
			{
				if (startChosen)
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
				targetLoc = i;

			}
		}
	}
	if (targetChosen)
	{
		clearCostField();
		createCostField(targetLoc);
	}
}

void Grid::createCostField(int t_gridNr)
{
	int cost = 0;
	m_grid[t_gridNr].addCost(cost);
	setVertical(t_gridNr, ROW, cost);
	setVertical(t_gridNr, -ROW, cost);
	setHorizontal(t_gridNr, +1, cost);
	setHorizontal(t_gridNr, -1, cost);

	setCost(t_gridNr,-ROW,-1, cost );
	setCost(t_gridNr,-ROW,+1, cost );
	setCost(t_gridNr,+ROW,-1, cost);
	setCost(t_gridNr,+ROW,+1, cost );

}

void Grid::setVertical(int t_gridNr, int t_rowCalc, int t_cost)
{
	int nr = t_gridNr;
	int cost = t_cost;
	while (nr >= 0 && nr < MAX_TILE)
	{
		m_grid[nr].addCost(cost);
		nr += t_rowCalc;
		cost++;
	}
}

void Grid::setHorizontal(int t_gridNr, int t_colCalc, int t_cost)
{	
	int nr = t_gridNr + t_colCalc;
	int cost = t_cost + 1;

	if (t_colCalc > 0)
	{
		while (nr % 50 <= 49 && nr % 50 != 0)
		{
			m_grid[nr].addCost(cost);
			nr += t_colCalc;
			cost++;
		}
	}
	else if (t_colCalc < 0)
	{
		while (nr % 50 != 49 && nr % 50 >= 0)
		{
			m_grid[nr].addCost(cost);
			nr += t_colCalc;
			cost++;
		}
	}
}

void Grid::clearCostField()
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		m_grid[i].addCost(-1);
	}
}

void Grid::setCost(int t_gridNr,int t_rowCalc,int t_cornerCalc, int t_cost)
{
	int calc = t_gridNr + t_rowCalc + t_cornerCalc;
	if ( calc > 0 && calc < MAX_TILE && t_gridNr % 50 <= 1)
	{
		m_grid[calc].addCost(t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
	}
	else if (calc > 0 && calc < MAX_TILE && t_gridNr % 50 >= 48)
	{
		m_grid[calc].addCost(t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
	}
	else if (calc >= 0 && calc < MAX_TILE)
	{
		m_grid[calc].addCost(t_cost);
		setCost(calc,t_rowCalc,t_cornerCalc , t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
		setHorizontal(calc, t_cornerCalc, t_cost + 1);
	}
}



void Grid::setUpFont()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "Problem loading font" << std::endl;
	}
}
