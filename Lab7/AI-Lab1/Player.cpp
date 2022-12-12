#include "Player.h"

void Player::init(sf::Vector2f t_pos)
{
	m_player.setPosition(t_pos);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_player);
}

Player::Player()
{
	m_player.setSize(sf::Vector2f(15, 15));
	m_player.setFillColor(sf::Color(94, 14, 92));
	m_player.setOutlineColor(sf::Color::Black);
	m_player.setOutlineThickness(1);
}
