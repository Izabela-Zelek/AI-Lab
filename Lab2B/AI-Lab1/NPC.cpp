#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::initialize(int enemyType)
{
	switch (enemyType)
	{
	case 0:
		m_npcType = Type::SEEK;
		m_enemyTexture = "ASSETS\\IMAGES\\enemyShip.png";
		break;
	case 1:
		m_npcType = Type::FLEE;
		m_enemyTexture = "ASSETS\\IMAGES\\fleeShip.png";
		break;
	case 2:
		m_npcType = Type::WANDER;
		m_enemyTexture = "ASSETS\\IMAGES\\wanderShip.png";
		break;
	default:
		break;
	}

	if (!m_npcTexture.loadFromFile(m_enemyTexture))
	{
		std::cout << "problem loading enemy" << std::endl;
	}
	m_npcSprite.setTexture(m_npcTexture);
	m_npcSprite.setRotation(m_rotation);
	m_npcSprite.setOrigin(m_npcSprite.getGlobalBounds().width / 2, m_npcSprite.getGlobalBounds().height / 2);
	m_npcSprite.setPosition(m_pos);
}

/// <summary>
/// Grabs enemy rotation (degrees), turns to radians and gets facing direction
/// Then moves enemy in facing direction
/// </summary>
void NPC::update(sf::Vector2f t_targetPos)
{
	switch (m_npcType)
	{
	case Type::SEEK:
		seek(t_targetPos);
		arrive(t_targetPos);
		break;
	case Type::FLEE:
		flee(t_targetPos);
		break;
	case Type::WANDER:
		wander();
		break;
	default:
		break;
	}
	
	m_npcSprite.setPosition(m_npcSprite.getPosition() + m_velocity);
	
	checkBoundary();

}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_npcSprite);
}

/// <summary>
/// Makes enemy wrap around world if crosses screen borders
/// </summary>
void NPC::checkBoundary()
{
	if (m_npcSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_npcSprite.getGlobalBounds().width)
	{
		m_npcSprite.setPosition(-m_npcSprite.getGlobalBounds().width, m_npcSprite.getPosition().y);
	}
	else if (m_npcSprite.getPosition().x < -m_npcSprite.getGlobalBounds().width)
	{
		m_npcSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_npcSprite.getGlobalBounds().width, m_npcSprite.getPosition().y);
	}

	if (m_npcSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, -m_npcSprite.getGlobalBounds().height);
	}
	else if (m_npcSprite.getPosition().y < -m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height);
	}
}

void NPC::seek(sf::Vector2f t_targetPos)
{
	m_velocity = t_targetPos - m_npcSprite.getPosition();
	normalize();
	m_velocity = m_velocity * m_speed;
		
	m_npcSprite.setRotation(getNewOrientation());
}

void NPC::arrive(sf::Vector2f t_targetPos)
{
	float radius = 2.0f;
	float timeToTarget = 20.0f;

	m_velocity = t_targetPos - m_npcSprite.getPosition();
	if (sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) >= radius)
	{
		m_speed = MAX_SPEED;
		m_velocity = m_velocity / timeToTarget;
		if(sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) > m_speed)
		{
			normalize();
			m_velocity = m_velocity * m_speed;
			m_npcSprite.setRotation(getNewOrientation());
		}
	}
	else
	{
		m_speed = 0;
	}
}

void NPC::flee(sf::Vector2f t_targetPos)
{
	float fleeRadius = 400.0f;
	float speedUpRadius = 200.0f;

	std::cout << m_speed << std::endl;

	if (sqrt(((m_npcSprite.getPosition().x - t_targetPos.x) * (m_npcSprite.getPosition().x - t_targetPos.x)) +
		((m_npcSprite.getPosition().y - t_targetPos.y) * (m_npcSprite.getPosition().y - t_targetPos.y))) <= fleeRadius)
	{
		m_velocity = m_npcSprite.getPosition() - t_targetPos;
		if (m_speed < MAX_SPEED && sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) <= speedUpRadius)
		{
			m_speed = m_speed + 0.1f;
		}
		else if (m_speed > 2.0f && sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) > speedUpRadius)
		{
			m_speed = m_speed - 0.1f;
		}
		normalize();
		m_velocity = m_velocity * m_speed;

		m_npcSprite.setRotation(getNewOrientation());
	}
}

void NPC::wander()
{
		m_npcSprite.setRotation(getNewOrientation());
		m_npcSprite.setRotation(m_npcSprite.getRotation() + 5 * (std::rand() % 5 - 2));
		m_velocity = { std::cos(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed, std::sin(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed };
}

void NPC::normalize()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity = { m_velocity.x / length, m_velocity.y / length };
}

float NPC::getNewOrientation()
{
	if(sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) > 0.0f) 
	{
		return atan2f(m_velocity.y, m_velocity.x) * 180.0 / 3.14f;
		
	}
	else
	{
		return m_npcSprite.getRotation();
	}
	
}
