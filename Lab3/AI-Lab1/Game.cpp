#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32U }, "Not Under Da Sea :(" },
	m_exitGame{false} //when true game will exit
{
	std::srand(time(NULL));
	initBG();
	m_player.initialize();
	m_seekNpc.initialize(1,m_font);
	//m_fleeNpc.initialize(0,m_font); //FROM OLD PROJECT
	m_wanderNpc.initialize(2,m_font);
	m_arriveNpc.initialize(3, m_font);
	m_pursueNpc.initialize(4,m_font);
	m_otherArriveNpc.initialize(5, m_font);
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
	switch (t_event.key.code)
	{
	case sf::Keyboard::Num1:
		EnemyAlive[0] = !EnemyAlive[0];
		break;	
	case sf::Keyboard::Num2:
		EnemyAlive[1] = !EnemyAlive[1];
		break;	
	case sf::Keyboard::Num3:
		EnemyAlive[2] = !EnemyAlive[2];
		break;	
	case sf::Keyboard::Num4:
		EnemyAlive[3] = !EnemyAlive[3];
		break;	
	case sf::Keyboard::Num5:
		EnemyAlive[4] = !EnemyAlive[4];
		break;
	default:
		break;
	}

	m_player.getInput();
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_player.update();
	
	if(EnemyAlive[0])
	{
		m_seekNpc.update(m_player.getPlayerPos(), m_player.getPlayerVelocity());
	}
	if(EnemyAlive[1])
	{
		m_wanderNpc.update(m_player.getPlayerPos(), m_player.getPlayerVelocity());
	}
	if (EnemyAlive[2])
	{
		m_arriveNpc.update(m_player.getPlayerPos(), m_player.getPlayerVelocity());
	}
	if (EnemyAlive[3])
	{
		m_pursueNpc.update(m_player.getPlayerPos(), m_player.getPlayerVelocity());
	}
	if (EnemyAlive[4])
	{
		m_otherArriveNpc.update(m_player.getPlayerPos(), m_player.getPlayerVelocity());
	}

	//m_fleeNpc.update(m_player.getPlayerPos(),m_player.getPlayerVelocity());

}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_bgSprite);

	m_player.draw(m_window);


	if (EnemyAlive[0])
	{
		m_seekNpc.draw(m_window);
	}
	if (EnemyAlive[1])
	{
		m_wanderNpc.draw(m_window);
	}
	if (EnemyAlive[2])
	{
		m_arriveNpc.draw(m_window);
	}
	if (EnemyAlive[3])
	{
		m_pursueNpc.draw(m_window);
	}
	if (EnemyAlive[4])
	{
		m_otherArriveNpc.draw(m_window);
	}
	//m_fleeNpc.draw(m_window);

	m_window.draw(m_instructions);

	m_window.display();
}

/// <summary>
/// initialises background texture and pos
/// </summary>
void Game::initBG()
{
	if (!m_bgTexture.loadFromFile("ASSETS\\IMAGES\\bg.png"))
	{
		std::cout << "problem loading bg" << std::endl;
	}
	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setScale(sf::VideoMode::getDesktopMode().width / m_bgSprite.getGlobalBounds().width, sf::VideoMode::getDesktopMode().height / m_bgSprite.getGlobalBounds().height);
	m_bgSprite.setOrigin(m_bgSprite.getLocalBounds().width / 2, m_bgSprite.getLocalBounds().height / 2);
	m_bgSprite.setPosition(m_pos);

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_instructions.setFont(m_font);
	m_instructions.setString(m_instrucText);
	m_instructions.setCharacterSize(20);
	m_instructions.setOrigin(m_instructions.getLocalBounds().width / 2, m_instructions.getLocalBounds().height / 2);
	m_instructions.setPosition(m_instrucOffset + (m_instructions.getLocalBounds().width /2), m_instrucOffset + (m_instructions.getLocalBounds().height / 2));

}
