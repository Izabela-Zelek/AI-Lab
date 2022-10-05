#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::initialize()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\playerShip.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setRotation(m_rotation);
	m_playerSprite.setOrigin(m_playerSprite.getGlobalBounds().width / 2, m_playerSprite.getGlobalBounds().height / 2);
	m_playerSprite.setPosition(m_pos);
}

void Player::update()
{
	m_playerSprite.setRotation(m_rotation);

	/// <summary>
	/// Grabs player rotation (degrees), turns to radians and gets facing direction
	/// Then moves player in facing direction
	/// </summary>
	
	m_velocity.x = std::cos(m_radianCalculation * (m_playerSprite.getRotation())) * m_speed;
	m_velocity.y = std::sin(m_radianCalculation * (m_playerSprite.getRotation())) * m_speed;

	m_playerSprite.setPosition(m_playerSprite.getPosition() + m_velocity);

	/// <summary>
	/// Makes player wrap around world if crosses screen borders
	/// </summary>

	if (m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width)
	{
		m_playerSprite.setPosition(-m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}
	else if (m_playerSprite.getPosition().x < -m_playerSprite.getGlobalBounds().width)
	{
		m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}

	if (m_playerSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_playerSprite.getGlobalBounds().height)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, -m_playerSprite.getGlobalBounds().height);
	}
	else if (m_playerSprite.getPosition().y < -m_playerSprite.getGlobalBounds().height)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_playerSprite.getGlobalBounds().height);
	}

}

void Player::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_playerSprite);
}

void Player::getInput()
{
	/// <summary>
	/// Pressing UP increases speed
	/// Pressing DOWN decreases speed
	/// </summary>
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_speed < MAX_SPEED)
		{
			m_speed += SPEED_INCREMENT;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_speed >= SPEED_INCREMENT)
		{
			m_speed -= SPEED_INCREMENT;
		}
	}
	
	/// <summary>
	/// Pressing RIGHT turns clockwise
	/// Pressing LEFT turns anti-clockwise
	/// </summary>

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= ROTATION_INCREMENT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += ROTATION_INCREMENT;
	}
}
