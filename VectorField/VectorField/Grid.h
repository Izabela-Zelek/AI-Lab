/// <summary>
/// author Izabela Zelek October 2022
/// </summary>
#ifndef GRID_HPP
#define GRID_HPP
#include "Tile.h"
#include "ScreenSize.h"
#include "Player.h"

class Grid
{
public:
	Grid();
	~Grid();

	void render(sf::RenderWindow& t_window);
	void checkMouseInput(sf::RenderWindow& t_window, bool t_leftClick, bool t_rightClick);
	void checkKeyInput(int t_mode);
	void createCostField();
	void setVertical(int t_gridNr, int rowCalc, int t_cost);
	void setHorizontal(int t_gridNr, int colCalc, int t_cost);
	void clearCostField();
	void setCost(int t_gridNr, int rowCalc, int cornerCalc, int t_cost);
	void setUpFont();
	void setUpIntegrationField();
	void setUpVectorField();
	void setUpHeatMap();
	void update();
	std::vector<int> pathFinding();

private:

	const int ROW = 50;
	const int COL = 50;
	const int MAX_TILE = ROW * COL;
	int targetLoc = -1;
	bool startChosen = false;
	bool targetChosen = false;
	bool calculated = false;
	bool goalReached = true;
	int m_interactables[2] = {-1,-2};
	int m_count = 0;
	std::vector<Tile> m_grid;
	std::vector<int> path;

	sf::Font m_font;

	Player m_player;

};

#endif // !GRID_HPP

