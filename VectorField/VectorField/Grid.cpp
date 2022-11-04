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
		std::cout << i << std::endl;
	}

	for (int i = 0; i < MAX_TILE; i++)
	{
		if (i < ROW || i > MAX_TILE - ROW || m_grid[i].getXPos() == m_grid[0].getXPos() || m_grid[i].getXPos() == m_grid[MAX_TILE - 1].getXPos())
		{
			m_grid[i].setBoundary();
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
		if (m_grid[i].getGlobalBounds().contains(translated_pos))
		{
			if (t_leftClick)
			{
				if (i != m_interactables[1])
				{
					if (startChosen)
					{
						m_grid[m_interactables[0]].changeColour(sf::Color(64, 11, 60));
					}
					m_grid[i].changeColour(sf::Color::Green);
					startChosen = true;
					m_interactables[0] = i;
				}
			}
			else
			{
				if (i != m_interactables[0])
				{
					if (targetChosen)
					{
						m_grid[m_interactables[1]].changeColour(sf::Color(64, 11, 60));
					}
					m_grid[i].changeColour(sf::Color::Red);
					targetChosen = true;
					m_interactables[1] = i;
					targetLoc = i;
					calculated = false;
				}

			}
		}
	}
	if (targetChosen && startChosen && !calculated)
	{
		clearCostField();
		createCostField();
		setUpIntegrationField();
		setUpVectorField();
		calculated = true;
	}
}

void Grid::checkKeyInput()
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		m_grid[i].changeMode();
	}
}

void Grid::createCostField()
{
	if (m_grid[targetLoc].getTraversable())
	{
		int cost = 0;
		m_grid[targetLoc].addCost(cost);
		setVertical(targetLoc, ROW, cost);
		setVertical(targetLoc, -ROW, cost);
		setHorizontal(targetLoc, +1, cost);
		setHorizontal(targetLoc, -1, cost);

		setCost(targetLoc, -ROW, -1, cost);
		setCost(targetLoc, -ROW, +1, cost);
		setCost(targetLoc, +ROW, -1, cost);
		setCost(targetLoc, +ROW, +1, cost);
	}
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
		m_grid[i].addIntegrationField(-1);
	}
}

void Grid::setCost(int t_gridNr,int t_rowCalc,int t_cornerCalc, int t_cost)
{
	int calc = t_gridNr + t_rowCalc + t_cornerCalc;
	if ( calc > 0 && calc < MAX_TILE && t_gridNr % 50 == 0)
	{
		m_grid[calc].addCost(t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
		setVertical(calc, t_rowCalc, t_cost + 1);
	}
	else if (calc > 0 && calc < MAX_TILE && t_gridNr % 50 >= 49)
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

void Grid::setUpIntegrationField()
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (i != targetLoc)
		{
			float tempCost = (float)m_grid[i].getCost();
			float xPosCalc = m_grid[i].getXPos() - m_grid[targetLoc].getXPos();
			float yPosCalc = m_grid[i].getYPos() - m_grid[targetLoc].getYPos();
			float distance = sqrt((xPosCalc * xPosCalc) + (yPosCalc * yPosCalc));
			m_grid[i].addIntegrationField(tempCost + distance);
		}
		else
		{
			m_grid[i].addIntegrationField(0);
		}
	}
}

void Grid::setUpVectorField()
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		std::vector<int> neighbourTiles;
		std::vector<float> neighbourIntFields;
		std::vector<int> rotations;
		bool goalAdjacentNeighbour = false;

		if (m_grid[i].getTraversable())
		{
			//If its a neihbour cell to the target, it will choose to go directly to it
			if (i == targetLoc - 1 || i == targetLoc + 1 || i == targetLoc - ROW || i == targetLoc + ROW)
			{
				if (i == targetLoc - 1)
				{
					m_grid[i].rotateVectorField(0, false);
				}
				else if (i == targetLoc + 1)
				{
					m_grid[i].rotateVectorField(180, false);
				}
				else if (i == targetLoc - ROW)
				{
					m_grid[i].rotateVectorField(90, false);
				}
				else if (i == targetLoc + ROW)
				{
					m_grid[i].rotateVectorField(270, false);
				}

			}
			else if (i != targetLoc - 1 && i != targetLoc + 1 && i != targetLoc - ROW && i != targetLoc + ROW)
			{
				//LEFT, RIGHT,TOP,BOTTOM
				if (m_grid[i].getXPos() > m_grid[0].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i - 1].getTraversable() && m_grid[i - 1].getRotation() != 0)
					{
						neighbourTiles.push_back(i - 1);
						neighbourIntFields.push_back(m_grid[i - 1].getIntegrationField());
						rotations.push_back(180);
					}

				}
				if (m_grid[i].getXPos() < m_grid[MAX_TILE - 1].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i + 1].getTraversable() && m_grid[i + 1].getRotation() != 180)
					{
						neighbourTiles.push_back(i + 1);
						neighbourIntFields.push_back(m_grid[i + 1].getIntegrationField());
						rotations.push_back(0);
					}

				}
				if (i > ROW)
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i - ROW].getTraversable() && m_grid[i - ROW].getRotation() != 90)
					{
						neighbourTiles.push_back(i - ROW);
						neighbourIntFields.push_back(m_grid[i - ROW].getIntegrationField());
						rotations.push_back(270);
					}

				}
				if (i < MAX_TILE - ROW)
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i + ROW].getTraversable() && m_grid[i + ROW].getRotation() != 270)
					{
						neighbourTiles.push_back(i + ROW);
						neighbourIntFields.push_back(m_grid[i + ROW].getIntegrationField());
						rotations.push_back(90);
					}

				}

				//TOP LEFT, RIGHT
				if (i > ROW && m_grid[i].getXPos() > m_grid[0].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i - ROW - 1].getTraversable() && m_grid[i - ROW - 1].getRotation() != 45)
					{
						neighbourTiles.push_back(i - ROW - 1);
						neighbourIntFields.push_back(m_grid[i - ROW - 1].getIntegrationField());
						rotations.push_back(225);
					}
				}
				if (i > ROW && m_grid[i].getXPos() < m_grid[MAX_TILE - 1].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i - ROW + 1].getTraversable() && m_grid[i - ROW + 1].getRotation() != 135)
					{
						neighbourTiles.push_back(i - ROW + 1);
						neighbourIntFields.push_back(m_grid[i - ROW + 1].getIntegrationField());
						rotations.push_back(315);
					}

				}


				//BOTTOM LEFT,RIGHT
				if (i < MAX_TILE - ROW && m_grid[i].getXPos() > m_grid[0].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i + ROW - 1].getTraversable() && m_grid[i + ROW - 1].getRotation() != 315)
					{
						neighbourTiles.push_back(i + ROW - 1);
						neighbourIntFields.push_back(m_grid[i + ROW - 1].getIntegrationField());
						rotations.push_back(135);
					}

				}
				if (i < MAX_TILE - ROW && m_grid[i].getXPos() < m_grid[MAX_TILE - 1].getXPos())
				{
					//Checks that neighbour is not an obstacle and isn't heading towards current tile (to avoid endless loops of back and forth)
					if (m_grid[i + ROW + 1].getTraversable() && m_grid[i + ROW + 1].getRotation() != 225)
					{
						neighbourTiles.push_back(i + ROW + 1);
						neighbourIntFields.push_back(m_grid[i + ROW + 1].getIntegrationField());
						rotations.push_back(45);
					}

				}
			
				float lowestCost = neighbourIntFields.at(0);
				int lowestCell = 0;

				for (int j = 0; j < neighbourIntFields.size(); j++)
				{
					if (neighbourIntFields[j] < lowestCost)
					{
						lowestCost = neighbourIntFields[j];
						lowestCell = j;
					}
				}

				if (i != targetLoc)
				{
					m_grid[i].rotateVectorField(rotations[lowestCell], false);
				}
				else
				{
					m_grid[i].rotateVectorField(rotations[lowestCell], true);
				}
			}
		}
	}
}
