#include "Monster.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"

USING_NS_CC;
using namespace CocosDenshion;

Monster::Monster(void)
{
	this->m_Speed = 1;

	scheduleUpdate();
	m_startMoveAction = false;
	m_startFightAciton = false;
	m_acceptBlood = 1;
}

Monster::~Monster(void)
{
}

Monster* Monster::create(Sprite* sprite, int ps)
{
	Monster *monster = new Monster();
	monster->m_Ps = (PowerEnumStatus)ps;  //怪物类型

	if (monster && monster->initWithFile(sprite))
	{
		monster->autorelease();
		return monster;
	}

	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Monster::initWithFile(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);

		loadConfigure();

		bRet = true;
	} while (0);

	return bRet;
}

void Monster::loadConfigure()
{
	//判断人物类型 关联不同资源
	switch (m_Ps)
	{
	case useFire:
		//this->schedule(schedule_selector(Monster::updateCallBack), 0.1f);
		break;
	case useIce:
		//this->schedule(schedule_selector(Monster::updateCallBack), 0.05f);
		break;
	}
}

void Monster::updateCallBack(float dt)
{
	if (m_Ps == PowerEnumStatus::useIce)
	{
		simpleAI(Vec2(0, 0));
	}
	else if (m_Ps == PowerEnumStatus::useFire)
	{
		simpleAI2(Vec2(0, 0));
	}
}

/*怪物AI*/
void Monster::simpleAI(Vec2 pPos)
{
	if (this->getPosition().x <= 0)
	{
		hurtMe(100);
	}
	else
	{
		auto jb = JumpBy::create(0.5, Vec2(-10, 5), 10, 1);
		this->runAction(jb);
	}
}

/*怪物AI*/
void Monster::simpleAI2(Vec2 pPos)
{
	if (this->getPosition().x <= 0)
	{
		hurtMe(100);
	}
	else
	{
		auto jb = JumpBy::create(0.5, Vec2(-5, 20), 10, 1);
		this->runAction(jb);
	}
}

bool Monster::ContainMonsterPower(Player* player)
{
	if (m_Ps == useFire)
	{
		/*
		Rect rect = player->boundingBox();
		Rect mrect = m_MonsterPower->boundingBox();

		if (m_MonsterPower->m_visiable)
		{
		if (rect.containsPoint(m_MonsterPower->getPosition())
		|| mrect.containsPoint(player->getPosition()))
		{
		auto jumpby = JumpBy::create(0.5, Vec2(-50, 50), 25, 1);
		player->runAction(Sequence::create(jumpby, NULL));
		player->getPhysicsBody()->resetForces();
		}
		else
		{
		}
		}*/
	}

	return 0;
}

/*怪物技能类型设置*/
void Monster::changeStatus(PowerEnumStatus ps)
{
	this->m_Ps = ps;
}