#include "Player.h"

void Player::init(sf::Vector2f t_size)
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\death.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setScale(t_size.x * 1.5f / m_playerSprite.getGlobalBounds().width, t_size.y * 1.5f / m_playerSprite.getGlobalBounds().height);
	m_playerSprite.setOrigin(m_playerSprite.getLocalBounds().width / 2, m_playerSprite.getLocalBounds().height);
}

void Player::spawnPlayer(sf::Vector2f pos)
{
	m_playerSprite.setPosition(pos);
	m_spawnPlayer = true;
}

void Player::render(sf::RenderWindow& t_window)
{
	if (m_spawnPlayer)
	{
		t_window.draw(m_playerSprite);
	}
}

sf::Vector2f Player::normalize(sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

bool Player::movePlayer(sf::Vector2f t_pos)
{
	/*if (m_moving)
	{
		m_direction = normalize(t_pos - m_playerSprite.getPosition());
		m_moving = false;
	}
	if (m_playerSprite.getPosition().x != t_pos.x && m_playerSprite.getPosition().y != t_pos.y)
	{
		m_playerSprite.move(m_speed * m_direction.x, m_speed * m_direction.y);
	}*/

	return m_next;
}
