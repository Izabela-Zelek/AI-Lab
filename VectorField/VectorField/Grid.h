/// <summary>
/// author Izabela Zelek October 2022
/// </summary>
#ifndef GRID_HPP
#define GRID_HPP
#include "Tile.h"
#include "ScreenSize.h"

class Grid
{
public:
	Grid();
	~Grid();

	void render(sf::RenderWindow& t_window);
	void checkMouseInput(sf::RenderWindow& t_window, bool t_leftClick);
	void createCostField(int t_gridNr);
	void setVertical(int t_gridNr, int rowCalc, int t_cost);
	void setHorizontal(int t_gridNr, int colCalc, int t_cost);
	void clearCostField();
	void setCost(int t_gridNr, int rowCalc, int cornerCalc, int t_cost);
	void setUpFont();

private:

	const int ROW = 50;
	const int COL = 50;
	const int MAX_TILE = ROW * COL;
	bool startChosen = false;
	bool targetChosen = false;
	int m_interactables[2];
	std::vector<Tile> m_grid;
	sf::Font m_font;

};

#endif // !GRID_HPP

