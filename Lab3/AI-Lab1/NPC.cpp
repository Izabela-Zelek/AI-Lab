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
	case 3:
		m_npcType = Type::ARRIVE;
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
		break;
	case Type::FLEE:
		m_velocity += flee(t_targetPos) * dt.asSeconds();
		break;
	case Type::WANDER:
		m_velocity += wander() * dt.asSeconds();
		break;
	case Type::ARRIVE:
		m_velocity += arrive(t_targetPos) * dt.asSeconds();
		break;
	default:
		break;
	}

	if (sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)) > m_maxSpeed)
	{
		m_velocity = normalize(m_velocity);
		m_velocity = m_velocity * m_maxSpeed;
	}
	
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

	float radius = 50.0f;
	float slowRadius = 100.0f;
	float timeToTarget = 0.1f;
	float targetSpeed;

	m_direction = t_targetPos - m_npcSprite.getPosition();
	float distance = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));

	if (distance < radius)
	{
		return { 0.0f, 0.0f };
	}

	if (distance > slowRadius)
	{
		targetSpeed = m_speed;
	}
	else
	{
		targetSpeed = m_speed * distance / slowRadius;
	}

	m_direction = normalize(m_direction);
	m_direction *= targetSpeed;

	linear = m_direction - m_velocity;
	linear = linear / timeToTarget;


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

sf::Vector2f NPC::wander()
{
	sf::Vector2f linear;

		float wanderRadius = 400;
		float wanderOffset = 300;
		float wanderOrientation = 0;

		wanderOrientation += (std::rand() % 3 - 1) * 2;
		float targetOrientation = wanderOrientation + m_npcSprite.getRotation();
		m_target.x = m_npcSprite.getPosition().x + wanderOffset * std::cos(m_radianCalculation * (m_npcSprite.getRotation()));
		m_target.y = m_npcSprite.getPosition().y + wanderOffset * std::sin(m_radianCalculation * (m_npcSprite.getRotation()));
		m_target.x += wanderRadius * std::cos(m_radianCalculation * (targetOrientation));
		m_target.y += wanderRadius * std::sin(m_radianCalculation * (targetOrientation));

		m_npcSprite.setRotation(face(m_target));

		linear.x = std::cos(m_radianCalculation * (m_npcSprite.getRotation())) * m_maxAcceleration;
		linear.y = std::sin(m_radianCalculation * (m_npcSprite.getRotation())) * m_maxAcceleration;

		return linear;

}

sf::Vector2f NPC::pursue(sf::Vector2f t_targetPos)
{
	/*m_direction = t_targetPos - m_npcSprite.getPosition();
	float distance = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));;
		speed = my.velocity.length
		if speed <= distance / maxTimePrediction:
	timePrediction = maxTimeprediction
		else:
	timePrediction = distance / speed
		newtarget.position = target.position + target.velocity * timePrediction
		seek(me, newTarget)

		or if we encapsulate this code in a Pursue function :
	return seek(me, newTarget)*/

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
