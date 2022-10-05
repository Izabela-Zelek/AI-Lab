#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::initialize()
{
	if (!m_npcTexture.loadFromFile("ASSETS\\IMAGES\\fish.png"))
	{
		std::cout << "problem loading fish" << std::endl;
	}
	m_npcSprite.setTexture(m_npcTexture);
	m_npcSprite.setPosition(m_pos);
	m_npcSprite.setOrigin(m_npcSprite.getGlobalBounds().width / 2, m_npcSprite.getGlobalBounds().height / 2);
}

void NPC::update()
{
	m_npcSprite.move(0, m_speed);

	if (m_npcSprite.getPosition().y < -m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height);
	}
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_npcSprite);
}
