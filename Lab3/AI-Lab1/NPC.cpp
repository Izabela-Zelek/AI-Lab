#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::initialize(int enemyType, sf::Font& t_font)
{
	switch (enemyType)
	{
	case 0:
		m_npcType = Type::FLEE;
		m_enemyTexture = "ASSETS\\IMAGES\\fleeShip.png";
		m_enemyTitleText = "Flee";
		break;
	case 1:
		m_npcType = Type::SEEK;
		m_enemyTexture = "ASSETS\\IMAGES\\enemyShip.png";
		m_enemyTitleText = "Seek";
		break;
	case 2:
		m_npcType = Type::WANDER;
		m_enemyTexture = "ASSETS\\IMAGES\\wanderShip.png";
		m_enemyTitleText = "Wander";

		break;
	case 3:
		m_npcType = Type::ARRIVE;
		m_enemyTexture = "ASSETS\\IMAGES\\arriveShip.png";
		m_enemyTitleText = "Slow Arrive";
		break;
	case 4:
		m_npcType = Type::PURSUE;
		m_enemyTexture = "ASSETS\\IMAGES\\pursueShip.png";
		m_enemyTitleText = "Pursue";
		break;
	case 5:
		m_npcType = Type::OTHERARRIVE;
		m_enemyTexture = "ASSETS\\IMAGES\\fastArriveShip.png";
		m_enemyTitleText = "Fast Arrive";
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

	m_title.setFont(t_font);
	m_title.setString(m_enemyTitleText);
	m_title.setCharacterSize(20);
	m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height / 2);
	m_title.setPosition(m_npcSprite.getPosition().x, m_npcSprite.getPosition().y - 70);

	dt = clock.getElapsedTime();

	if (m_npcType == Type::WANDER)
	{
		m_npcSprite.setRotation(std::rand() % 360);
	}
}
void NPC::update(sf::Vector2f t_targetPos,sf::Vector2f t_targetVelocity)
{
	m_npcSprite.move(m_velocity * dt.asSeconds());
	m_npcSprite.setRotation(getNewOrientation(m_velocity));

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
		m_speed = 50.0f;
		if (arrive(t_targetPos).x != 0.0f || arrive(t_targetPos).y != 0.0f)
		{
			m_velocity += arrive(t_targetPos) * dt.asSeconds();
		}
		else if (arrive(t_targetPos).x == 0.0f && arrive(t_targetPos).y == 0.0f)
		{
			m_velocity = { 0.0f, 0.0f };
		}
		break;
	case Type::PURSUE:
		m_velocity += pursue(t_targetPos,t_targetPos) * dt.asSeconds();
		break;	
	case Type::OTHERARRIVE:
		m_speed = 150.0f;
		if(arrive(t_targetPos).x != 0.0f || arrive(t_targetPos).y != 0.0f)
		{
			m_velocity += arrive(t_targetPos) * dt.asSeconds();
		}
		else if (arrive(t_targetPos).x == 0.0f && arrive(t_targetPos).y == 0.0f)
		{
			m_velocity = {0.0f, 0.0f };
		}
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
	m_title.setPosition(m_npcSprite.getPosition().x, m_npcSprite.getPosition().y - 70);

}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_leftLine);
	t_window.draw(m_rightLine);
	t_window.draw(m_npcSprite);
	t_window.draw(m_title);
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

	float radius = 10.0f;
	float slowRadius = 50.0f;
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

	float wanderRadius = 30;
	float wanderOffset = 30;
	float wanderOrientation = 0;

	wanderOrientation += (std::rand() % 3 - 1) * 5.0f;

	float targetOrientation = wanderOrientation + m_npcSprite.getRotation();
	m_target.x = m_npcSprite.getPosition().x + wanderOffset * std::cos(m_radianCalculation * (m_npcSprite.getRotation()));
	m_target.y = m_npcSprite.getPosition().y + wanderOffset * std::sin(m_radianCalculation * (m_npcSprite.getRotation()));
	m_target.x += wanderRadius * std::cos(m_radianCalculation * (targetOrientation));
	m_target.y += wanderRadius * std::sin(m_radianCalculation * (targetOrientation));

	linear.x = (m_target.x - m_npcSprite.getPosition().x) * m_maxAcceleration;
	linear.y = (m_target.y - m_npcSprite.getPosition().y) * m_maxAcceleration;



	return linear;
}

sf::Vector2f NPC::pursue(sf::Vector2f t_targetPos, sf::Vector2f t_targetVelocity)
{
	float maxTimePrediction = 0.1f;
	float timePrediction;
	sf::Vector2f newtarget;

	m_direction = t_targetPos - m_npcSprite.getPosition();
	float distance = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));
	m_speed = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
		
	if (m_speed <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else
	{
		timePrediction = distance / m_speed;
	}
	newtarget = t_targetPos + t_targetVelocity * timePrediction;
	
	return seek(newtarget);
}

sf::Vector2f NPC::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}

float NPC::getNewOrientation(sf::Vector2f t_dir)
{
	if(sqrt((t_dir.x * t_dir.x) + (t_dir.y * t_dir.y)) > 0.0f)
	{
		return atan2f(t_dir.y, t_dir.x) * 180.0 / 3.14f;
		
	}
	else
	{
		return m_npcSprite.getRotation();
	}

//TWAS A FAIL, I'M AFRAID
//
}/*float NPC::face(sf::Vector2f targetPos)
{
	float targerOr;

	targerOr = atan2f(m_velocity.y, m_velocity.x) * 180.0 / 3.14f;
	return align(targerOr);
}

float NPC::align(float targetRot)
{
	float targetRotation;
	float targetRadius = 250.0f;
	float slowRadius = 150.0f;
	float maxRotation = 30.0f;
	float timeToTarget = 0.1f;
	float angularAbs = 0.0f;
	float angular = 0.0f;
	float maxAngular = 360.0f;
	float maxAngularAcc = 10.0f;

	float rotation = targetRot - m_npcSprite.getRotation();
	rotation = atan2(::sin(rotation), ::cos(rotation));
	float rotationSize = abs(rotation);

	if (rotationSize < targetRadius)
	{
		targetRotation = 0;
	}
	else if (rotationSize > slowRadius)
	{
		targetRotation = maxRotation;
	}
	else
	{
		targetRotation = maxRotation * (rotationSize / slowRadius);
		angular = targetRotation - m_npcSprite.getRotation();
		angular = angular / timeToTarget;
		angularAbs = abs(angular);
	}
	if (angularAbs > maxAngular)
	{
		angular = angular / angularAbs;
		angular = angular * maxAngularAcc;
	}
	return angular;

}*/

void NPC::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_npcSprite.getRotation() - angleOfSight);
	m_rightLine.setRotation(m_npcSprite.getRotation() + angleOfSight);
	m_leftLine.setPosition(m_npcSprite.getPosition());
	m_rightLine.setPosition(m_npcSprite.getPosition());

	sf::Vector2f orientation = {std::cos(m_radianCalculation * m_npcSprite.getRotation()),std::sin( m_radianCalculation *  m_npcSprite.getRotation())};
	sf::Vector2f distance = t_targetPos - m_npcSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_npcSprite.getPosition().x) * (t_targetPos.x - m_npcSprite.getPosition().x) + (t_targetPos.y - m_npcSprite.getPosition().y) * (t_targetPos.y - m_npcSprite.getPosition().y)) <= 200.0f)
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
	else
	{
		m_leftLine.setFillColor(sf::Color::Green);
		m_rightLine.setFillColor(sf::Color::Green);
	}
}
