#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::initialize()
{
	if (!m_npcTexture.loadFromFile("ASSETS\\IMAGES\\enemyShip.png"))
	{
		std::cout << "problem loading enemy" << std::endl;
	}
	m_npcSprite.setTexture(m_npcTexture);
	m_npcSprite.setRotation(m_rotation);
	m_npcSprite.setOrigin(m_npcSprite.getGlobalBounds().width / 2, m_npcSprite.getGlobalBounds().height / 2);
	m_npcSprite.setPosition(m_pos);
}

void NPC::update()
{
	m_npcSprite.setRotation(m_rotation);

	/// <summary>
	/// Grabs enemy rotation (degrees), turns to radians and gets facing direction
	/// Then moves enemy in facing direction
	/// </summary>
	
	m_velocity.x = std::cos(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed;
	m_velocity.y = std::sin(m_radianCalculation * (m_npcSprite.getRotation())) * m_speed;

	m_npcSprite.setPosition(m_npcSprite.getPosition() + m_velocity);

	/// <summary>
	/// Makes enemy wrap around world if crosses screen borders
	/// </summary>

	if (m_npcSprite.getPosition().y < -m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height);
	}
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_npcSprite);
}
