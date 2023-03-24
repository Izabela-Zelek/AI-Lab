#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Droid.h"
#include "MoveTo.h"
#include "HealthPill.h"
#include <SFML/Graphics.hpp>

//using namespace std;

class Game
{
public:

	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	
/// <summary>
/// This is the grid.
/// It will also contain a list of all the nodes and what type of nodes they are.
/// </summary>
	Grid gridWorld = Grid(20);
	bool debug = true;

private:
	//I'm sorry, I got too ambitious
	int m_obstacles[70] = {40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,
		93,113,133,153,173,193,213,233,253,273,293,313,333,353,373,393,243,244,
		245,246,247,248,249,250,251,252,135,136,137,138,139,174,175,176,177,178,
		215,216,217,218,219,235,255,275,315,316,317,318,335,355,375,395 };

	void test();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void updateDroids();
	void render();
	void setupFontAndText();
	void setupDroids();
	void setupGrid();
	void drawGrid(sf::RenderWindow& t_window);
	void drawDroids(sf::RenderWindow& t_window);
	void drawHealthPills(sf::RenderWindow& t_window);
	void initGridObjects();

	sf::RenderWindow m_window; // main SFML window
//	unsigned int worldWidth = (unsigned)2000;
//	unsigned int worldHeight = (unsigned)1800;
	unsigned int worldWidth = (unsigned)1000;
	unsigned int worldHeight = (unsigned)900;
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	bool m_exitGame; // control exiting game
	int goalX;
	int goalY;
	bool goalSet = false;
	std::vector<Droid*> m_droids;
	std::vector<HealthPill*> m_healthPills;
};

#endif // !GAME_H

