#include "Power.h"

PPower::PPower()
{
	m_sprite = NULL;
}

PPower::~PPower()
{
}

/*绑定Sprite*/
void PPower::bindSprite(Sprite* sprite)
{
	if (this->m_sprite != NULL)
	{
		m_sprite->removeFromParentAndCleanup(true);
	}

	this->m_sprite = sprite;
	m_sprite->setPosition(Vec2(sprite->getContentSize().width / 2,
		sprite->getContentSize().height / 2));
	this->addChild(m_sprite, 2);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);
}

/*清理sprite*/
void PPower::cleanSprite()
{
	if (m_sprite != NULL)
	{
		m_sprite->removeFromParentAndCleanup(true);
		m_sprite = nullptr;
	}
}

/*获取Sprite*/
Sprite* PPower::getSprite()
{
	return this->m_sprite;
}