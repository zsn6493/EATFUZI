#include "MonsterClassOne.h"
#include "AnimoTool.h"

USING_NS_CC;

MonsterOne::MonsterOne(void)
{
	this->m_Speed = 1;

	scheduleUpdate();
	m_startMoveAction = false;
	m_startFightAciton = false;
	m_acceptBlood = 1;

	m_iBaseAtk = 1;
	m_iCurAtk = 1;
	m_iHP = 1;
	m_iCurAtk = 1;
	m_iHP = 1;
	m_iDefens = 1;
	m_iSpeed = 1;
	m_iCurAtkSpeed = 1;
}

MonsterOne::~MonsterOne(void)
{
}

MonsterOne* MonsterOne::create(Sprite* sprite)
{
	MonsterOne *monster = new MonsterOne();

	if (monster && monster->init(sprite))
	{
		monster->autorelease();
		return monster;
	}

	CC_SAFE_DELETE(monster);
	return NULL;
}

bool MonsterOne::init(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);

		//loadConfigure();

		bRet = true;
	} while (0);

	return bRet;
}

void MonsterOne::updateCallBack(float dt)
{
	simpleAI(Vec2(0, 0));
}

/*¹ÖÎïAI*/
void MonsterOne::simpleAI(Vec2 pPos)
{
	if (this->getPosition().x <= 0)
	{
		hurtMe(100);
	}
	else
	{
		auto jumpBy = JumpBy::create(0.5, Vec2(-15, 1), 1, 1);
		this->runAction(jumpBy);
	}
}