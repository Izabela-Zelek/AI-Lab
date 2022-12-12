#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32U }, "They're coming! Oh god, oh no. Hide your wives" },
	m_exitGame{false} //when true game will exit
{
	std::srand(time(NULL));
	initBG();
	generate();
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); 
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type)
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type)
		{
			processKeys(newEvent);
		}
	}
}


void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

}

void Game::render()
{
	m_window.clear(sf::Color(10, 79, 11
	));
	m_window.draw(m_FarText);
	m_window.draw(m_MediumText);
	m_window.draw(m_CloseText);
	m_window.draw(m_FarLine);
	m_window.draw(m_MediumLine);
	for (int i = 0; i < enemyCount; i++)
	{
		m_enemy.at(i).render(m_window);
	}
	for (int i = 0; i < m_ownArmyCount; i++)
	{
		m_player.at(i).render(m_window);
	}
	m_window.display();
}

void Game::initBG()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_FarText.setFont(m_font);
	m_FarText.setString("Far");
	m_FarText.setCharacterSize(20);
	m_FarText.setFillColor(sf::Color::Black);
	
	m_MediumText.setFont(m_font);
	m_MediumText.setString("Medium");
	m_MediumText.setCharacterSize(20);
	m_MediumText.setFillColor(sf::Color::Black);

	m_CloseText.setFont(m_font);
	m_CloseText.setString("Close");
	m_CloseText.setCharacterSize(20);
	m_CloseText.setFillColor(sf::Color::Black);
}

void Game::generate()
{
	std::cout << "|          |  Close | Medium |   Far    |" << std::endl;
	std::cout << "|----------|--------|--------|----------|" << std::endl;
	std::cout << "|  Tiny    | Medium |  Low   |   Low    |" << std::endl;
	std::cout << "|  Small   |  High  |  Low   |   Low    |" << std::endl;
	std::cout << "| Moderate |  High  | Medium |   Low    |" << std::endl;
	std::cout << "|  Large   |  High  |  High  |  Medium  |" << std::endl;
	std::cout << "|----------|--------|--------|----------|\n" << std::endl;


	std::cout << "Tiny Army = 1 - 30 soldiers" << std::endl;
	std::cout << "Small Army = 20 - 60 soldiers" << std::endl;
	std::cout << "Moderate Army = 50 - 110 soldiers" << std::endl;
	std::cout << "Large Army = 100+ soldiers\n" << std::endl;

	enemyCount = std::rand() % 150 + 1;
	enemyRandY = std::rand() % (sf::VideoMode::getDesktopMode().height - 400) + 200;
	std::cout << "Enemy troop number : " << enemyCount << std::endl;
	m_enemy.reserve(enemyCount);

	int count = 0;
	float xValue = 25;
	float yValue = enemyRandY;
	for (int i = 0; i < enemyCount; i++)
	{
		m_enemy.push_back(Enemy());
		sf::Vector2f pos = { xValue,yValue };
		count++;
		xValue += 38;
		if (count % 50 == 0)
		{
			yValue -= 50;
			xValue = 25;
		}
		m_enemy.at(i).init(pos);
	}

	//Membership functions for the size of enemy army
	m_Tiny = fuzzySet.FuzzyTriangle(enemyCount, -30, 0, 30);
	m_Small = fuzzySet.FuzzyTrapezoid(enemyCount, 20, 35, 45, 60);
	m_Moderate = fuzzySet.FuzzyTrapezoid(enemyCount, 50, 70, 90, 110);
	m_Large = fuzzySet.FuzzyGrade(enemyCount, 100, 120);

	//Membership functions for the distance away
	float third = (sf::VideoMode::getDesktopMode().height / 3) / 5;
	float x0 = ((sf::VideoMode::getDesktopMode().height / 3) * 2);
	m_Close = fuzzySet.FuzzyGrade(enemyRandY, x0 - third, x0);

	float x1 = (sf::VideoMode::getDesktopMode().height / 3);
	m_MediumDistance = fuzzySet.FuzzyTrapezoid(enemyRandY, x1 - third, x1, x0 - third, x0);

	m_Far = fuzzySet.FuzzyTriangle(enemyRandY, -(x1 + third), 0, x1 + third);

	m_FarText.setPosition(20, 20);

	m_FarLine.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, 1));
	m_FarLine.setFillColor(sf::Color::Black);
	m_FarLine.setPosition(sf::Vector2f(0, x0));

	m_CloseText.setPosition(20, m_FarLine.getPosition().y + 20.0f);

	m_MediumLine.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, 1));
	m_MediumLine.setFillColor(sf::Color::Black);
	m_MediumLine.setPosition(sf::Vector2f(0, x1));

	m_MediumText.setPosition(20, m_MediumLine.getPosition().y + 20.0f);

	//Setting threat levels
	m_Low = fuzzySet.FuzzyOR(
		fuzzySet.FuzzyOR(
			fuzzySet.FuzzyAND(m_MediumDistance, m_Tiny), fuzzySet.FuzzyAND(m_MediumDistance, m_Small)),
		fuzzySet.FuzzyAND(m_Far, fuzzySet.FuzzyNOT(m_Large)));

	m_Medium = fuzzySet.FuzzyOR(
		fuzzySet.FuzzyOR(fuzzySet.FuzzyAND(m_Close, m_Tiny), fuzzySet.FuzzyAND(m_MediumDistance, m_Moderate)),
		fuzzySet.FuzzyAND(m_Far, m_Large));

	m_High = fuzzySet.FuzzyOR(
		fuzzySet.FuzzyAND(m_Close, fuzzySet.FuzzyNOT(m_Tiny)), fuzzySet.FuzzyAND(m_MediumDistance, m_Large));

	m_ownArmyCount = (m_Low * 50 + m_Medium * 100 + m_High * 150) /
		(m_Low + m_Medium + m_High);

	m_ownArmyCount = round(m_ownArmyCount);

	std::cout << "My troop number: " << m_ownArmyCount;

	m_player.reserve(m_ownArmyCount);
	int playerCount = 0;
	float playerXValue = 25;
	float playerYValue = sf::VideoMode::getDesktopMode().height - 50;

	for (int i = 0; i < m_ownArmyCount; i++)
	{
		m_player.push_back(Player());
		sf::Vector2f pos = { playerXValue,playerYValue };
		playerCount++;
		playerXValue += 38;
		if (playerCount % 50 == 0)
		{
			playerYValue -= 50;
			playerXValue = 25;
		}
		m_player.at(i).init(pos);
	}
}