#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32U }, "They're coming! Oh god, oh no. Hide your wives" },
	m_exitGame{false} //when true game will exit
{
	std::srand(time(NULL));
	enemyCount = std::rand() % 150 + 1;
	enemyRandY = std::rand() % (sf::VideoMode::getDesktopMode().height - 400) + 200;
	std::cout << enemyCount;
	m_enemy.reserve(enemyCount);

	int count = 0;
	float xValue = 20;
	float yValue = enemyRandY;
	for (int i = 0; i < enemyCount; i++)
	{
		m_enemy.push_back(Enemy());
		sf::Vector2f pos = {xValue,yValue};
		count++;
		xValue += 50;
		if (count % 38 == 0)
		{
			yValue += 50;
			xValue = 20;
		}
		m_enemy.at(i).init(pos);
	}
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
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < enemyCount; i++)
	{
		m_enemy.at(i).render(m_window);
	}
	m_window.display();
}
