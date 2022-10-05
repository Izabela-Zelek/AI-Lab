#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::initialize()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\dolphin.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(m_pos);
	m_playerSprite.setOrigin(m_playerSprite.getGlobalBounds().width / 2, m_playerSprite.getGlobalBounds().height / 2);
}

void Player::update()
{
	m_playerSprite.move(m_speed, 0);

	if (m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width / 2 && m_headingRight)
	{
		m_playerSprite.setPosition(-m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}
	if (m_playerSprite.getPosition().x < -m_playerSprite.getGlobalBounds().width && !m_headingRight)
	{
		m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}


	if (m_speed < 0)
	{
		m_playerSprite.setScale(-1, 1);
		m_headingRight = false;
	}
	else if (m_speed > 0)
	{
		m_playerSprite.setScale(1, 1);
		m_headingRight = true;
	}
}

void Player::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_playerSprite);
}

void Player::getInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += 0.2f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= 0.2f;
	}
}
