#include "PSoul.h"

PSoul::PSoul()
{
	m_sprite = NULL;
	m_sName = "";
	m_iHP = 1;
	m_iDefense = 1;
	m_isDead = false;
	m_iSpeed = 1;
	m_iLevel = 1;
}

PSoul::~PSoul()
{
}

void PSoul::bindSprite(Sprite* sprite)
{
	if (this->m_sprite != NULL)
	{
		m_sprite->removeFromParentAndCleanup(true);
	}

	this->m_sprite = sprite;
	m_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_sprite->setPosition(Vec2(m_sprite->getContentSize().width / 2,
		m_sprite->getContentSize().height / 2));
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);

	onBindSprite();
}

Sprite* PSoul::getSprite()
{
	return this->m_sprite;
}

void PSoul::hurtMe(int iHurtValue)
{
	if (m_isDead)
		return;

	/* 最小伤害值为1 */
	if (iHurtValue <= getiDefense())
	{
		iHurtValue = 1;
	}

	int iCurHP = getiHP();      /* 当前HP */
	int iAfterHP = iCurHP - iHurtValue; /* 被攻击后的HP */

	onHurt(iHurtValue);

	if (iAfterHP > 0)
	{
		setiHP(iAfterHP);
	}
	else
	{
		m_isDead = true;
		/* 死亡 */
		onDead();
	}
}

bool PSoul::isDead()
{
	return this->m_isDead;
}

void PSoul::onDead()
{
}

void PSoul::cleanSprite()
{
	m_sprite->removeFromParentAndCleanup(true);
	m_sprite == NULL;
}

void PSoul::onBindSprite()
{
}

void PSoul::onHurt(int iHurtValue)
{
}