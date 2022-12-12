#include "Enemy.h"

void Enemy::init(sf::Vector2f t_pos)
{
	m_enemy.setPosition(t_pos);
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_enemy);
}

Enemy::Enemy()
{
	m_enemy.setSize(sf::Vector2f(15, 15));
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setOutlineColor(sf::Color::Black);
	m_enemy.setOutlineThickness(1);
}
