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
	m_npcSprite.setOrigin(m_npcSprite.getLocalBounds().width / 2, m_npcSprite.getLocalBounds().height / 2);
	m_npcSprite.setPosition(m_pos);

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);

	dt = clock.getElapsedTime();
}

/// <summary>
/// Grabs enemy rotation (degrees), turns to radians and gets facing direction
/// Then moves enemy in facing direction
/// </summary>
void NPC::update(sf::Vector2f t_targetPos)
{
	m_npcSprite.move(m_velocity * dt.asSeconds());

	switch (m_npcType)
	{
	case Type::SEEK:
		m_velocity += seek(t_targetPos) * dt.asSeconds();
		m_velocity += arrive(t_targetPos) * dt.asSeconds();
		break;
	case Type::FLEE:
		m_velocity += flee(t_targetPos) * dt.asSeconds();
		break;
	case Type::WANDER:
		wander();
		break;
	default:
		break;
	}

	//m_npcSprite.rotate(m_angularVelocity * dt.asSeconds());



	//m_npcSprite.setPosition(m_npcSprite.getPosition() + m_velocity);
	
	setVisionCone(t_targetPos);
	checkBoundary();

}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_leftLine);
	t_window.draw(m_rightLine);
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

sf::Vector2f NPC::seek(sf::Vector2f t_targetPos)
{
	sf::Vector2f linear;

	m_direction = t_targetPos - m_npcSprite.getPosition();
	m_direction = normalize(m_direction);

	linear = m_direction * m_maxAcceleration;
		

	return linear;

}

sf::Vector2f NPC::arrive(sf::Vector2f t_targetPos)
{
	sf::Vector2f linear;

	float radius = 20.0f;
	float slowRadius = 50.0f;
	float timeToTarget = 0.1f;
	float targetSpeed;

	sf::Vector2f direction = t_targetPos - m_npcSprite.getPosition();
	float distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	if (distance < radius)
	{
		return { 0.0f, 0.0f };
	}

	if (distance > slowRadius)
		targetSpeed = m_speed;
	else
		targetSpeed = m_speed * distance / slowRadius;

	normalize(m_direction);
	m_direction *= targetSpeed;

	linear = m_direction - m_velocity;
	linear /= timeToTarget;


	if (sqrt((linear.x * linear.x) + (linear.y * linear.y)) > m_maxAcceleration)
	{
		linear = normalize(linear);
		linear *= m_maxAcceleration;
	}

	return linear;
}

sf::Vector2f NPC::flee(sf::Vector2f t_targetPos)
{
	sf::Vector2f linear;

	m_direction = m_npcSprite.getPosition() - t_targetPos;
	m_direction = normalize(m_direction);
	linear = m_direction * m_maxAcceleration;

	return linear;
}

void NPC::wander()
{
//		//m_npcSprite.setRotation(getNewOrientation());
//		//m_npcSprite.setRotation(m_npcSprite.getRotation() + 5 * (std::rand() % 5 - 2));
//		//m_velocity = { std::cos(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed, std::sin(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed };
//		float wanderRadius = 400;
//		float wanderOffset = 300;
//		float wanderOrientation = 0;
//
//		wanderOrientation += (std::rand() % 3 - 1) * 2;
//		float targetOrientation = wanderOrientation + m_npcSprite.getRotation();
//		m_target.x = m_npcSprite.getPosition().x + wanderOffset * std::cos(m_radianCalculation * (m_npcSprite.getRotation()));
//		m_target.y = m_npcSprite.getPosition().y + wanderOffset * std::sin(m_radianCalculation * (m_npcSprite.getRotation()));
//		m_target.x += wanderRadius * std::cos(m_radianCalculation * (targetOrientation));
//		m_target.y += wanderRadius * std::sin(m_radianCalculation * (targetOrientation));
//		m_npcSprite.setRotation(face(m_target));
//
//		m_velocity.x = std::cos(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed;
//		m_velocity.y = std::sin(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed;

}

sf::Vector2f NPC::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
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
	
}float NPC::face(sf::Vector2f targetPos)
{
	sf::Vector2f direction = targetPos - m_npcSprite.getPosition();
	if(sqrt((direction.x * direction.x) + (direction.y * direction.y)) > 0.0f)
	{
		return atan2f(direction.y, direction.x) * 180.0 / 3.14f;
		
	}
	else
	{
		return m_npcSprite.getRotation();
	}
}

void NPC::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_npcSprite.getRotation() - angleOfSight);
	m_rightLine.setRotation(m_npcSprite.getRotation() + angleOfSight);
	m_leftLine.setPosition(m_npcSprite.getPosition());
	m_rightLine.setPosition(m_npcSprite.getPosition());

	sf::Vector2f targetDirection = {t_targetPos.x - m_npcSprite.getPosition().x,t_targetPos.y - m_npcSprite.getPosition().y};
	sf::Vector2f orientation = { std::cos(m_radianCalculation * (m_npcSprite.getRotation())), -std::sin(m_radianCalculation * (m_npcSprite.getRotation())) };
	float dotProduct = (targetDirection.x * orientation.x) + (targetDirection.y * orientation.y);

	if (dotProduct >= 360)
	{
		dotProduct = dotProduct - 360;
	}
	std::cout << dotProduct <<std::endl;
	if (dotProduct < angleOfSight)
	{
		m_leftLine.setFillColor(sf::Color::Red);
		m_rightLine.setFillColor(sf::Color::Red);
	}
	else
	{
		m_leftLine.setFillColor(sf::Color::Green);
		m_rightLine.setFillColor(sf::Color::Green);
	}
}
