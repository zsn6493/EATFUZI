#include "Boss.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"

USING_NS_CC;
using namespace CocosDenshion;

#define NOTIFY cocos2d::NotificationCenter::getInstance()

Boss::Boss(void)
{
	m_MonsterPower = NULL;
	scheduleUpdate();
}

Boss::~Boss(void)
{
}

Boss* Boss::create(Sprite* sprite, int ps)
{
	Boss *boss = new Boss();
	boss->m_Ps = (PowerEnumStatus)ps;                 //怪物类型
	if (boss && boss->init(sprite))
	{
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return NULL;
}

bool Boss::init(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);

		if (m_Ps == useFire)
		{
			this->schedule(schedule_selector(Boss::updatCallBack));
		}
		else if (m_Ps == useIce)
		{
			//auto action = AnimoTool::createBoss2Animotion();
			//sprite->runAction(action);
		}
		bRet = true;
	} while (0);

	return bRet;
}

/*怪物AI*/
void Boss::simpleAI(Vec2 pPos)
{
	if (m_Ps == useFire)
	{
		if (this->getPosition().x <= 0)
		{
			hurtMe(100);
		}
		else
		{
			//auto jb = JumpBy::create(0.5, Vec2(-10, 30), 30, 1);
			//auto mb = MoveBy::create(0.5, Vec3(-1, 0, 0));
			//this->runAction(mb);
		}
	}
	else if (m_Ps == useIce)
	{
	}
}

/*怪物技能类型设置*/
void Boss::changeStatus(PowerEnumStatus ps)
{
	this->m_Ps = ps;
}

void Boss::updatCallBack(float dt)
{
	simpleAI(m_Orgin);
}