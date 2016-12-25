#include "Boss.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
USING_NS_CC;

#define NOTIFY cocos2d::NotificationCenter::getInstance()

Boss::Boss(void)
{
	scheduleUpdate();
}

Boss::~Boss(void)
{
}

Boss* Boss::create(Sprite* sprite, int ps)
{
	Boss *boss = new Boss();
	boss->m_CharType = (CharType)ps;                 //怪物类型
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

		this->schedule(schedule_selector(Boss::updatCallBack));

		bRet = true;
	} while (0);

	return bRet;
}

/*怪物AI*/
void Boss::simpleAI(Vec2 pPos)
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

/*怪物技能类型设置*/
void Boss::changeStatus(CharType ct)
{
	this->m_CharType = ct;
}

void Boss::updatCallBack(float dt)
{
	simpleAI(m_Orgin);
}