#include "Monster.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include <string>

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

Monster::Monster(void)
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

	m_iHurtedStatus = false;

	m_MStatus = MonsterStatus::MoveStatus;
	m_DeltaTime = 0.0f;
}

Monster::~Monster(void)
{
}

Monster* Monster::create(Sprite* sprite, int level)
{
	Monster *monster = new Monster();
	monster->m_CharType = (CharType)level;  //��������

	if (monster && monster->init(sprite))
	{
		monster->autorelease();
		return monster;
	}

	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Monster::init(Sprite* sprite)
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
	//�ж��������� ������ͬ��Դ
	switch (m_CharType)
	{
	case t1:
		//this->schedule(schedule_selector(Monster::updateCallBack), 0.1f);
		break;
	case t2:
		//this->schedule(schedule_selector(Monster::updateCallBack), 0.05f);
		break;
	}
}

void Monster::fightSpeedMonster(float dt)
{
	this->hurtMe(this->gethurtedValue());

	//�˺�չʾ
	string boold = StringUtils::format("%d", this->gethurtedValue());
	FlowWord* flowWord = FlowWord::create();
	flowWord->showWord(boold.c_str(),
		Vec2(this->getSprite()->getPosition().x,
		this->getSprite()->getPosition().y +
		this->getContentSize().height / 2));
	flowWord->gettextLab()->setColor(Color3B(255, 0, 0));
	this->addChild(flowWord);

	m_iHurtedStatus = false;
}

void Monster::updateCallBack(float dt)
{
	switch (getMStatus())
	{
	case MoveStatus:
	{
					   if (m_CharType == CharType::t1)
					   {
						   simpleAI(Vec2(0, 0));
					   }
					   else if (m_CharType == CharType::t2)
					   {
						   simpleAI2(Vec2(0, 0));
					   }
					   break;
	}
	case FigthStatus:
		this->stopAllActions();
		fightSpeedMonster(dt);
		break;
	case DieStatus:
		break;
	default:
		break;
	}
}

/*����AI*/
void Monster::simpleAI(Vec2 pPos)
{
	if (this->getPosition().x <= 0)
	{
		hurtMe(100);
	}
	else
	{
		auto jumpBy = JumpBy::create(0.5, Vec2(-10, 1), 1, 1);
		this->runAction(jumpBy);
	}
}

/*����AI*/
void Monster::simpleAI2(Vec2 pPos)
{
	if (this->getPosition().x <= 0)
	{
		hurtMe(100);
	}
	else
	{
		auto jumpBy = JumpBy::create(0.5, Vec2(-5, 1), 1, 1);
		this->runAction(jumpBy);
	}
}

bool Monster::ContainMonsterPower(Player* player)
{
	if (m_CharType == t1)
	{
	}

	return 0;
}

/*���＼����������*/
void Monster::changeStatus(CharType ct)
{
	this->m_CharType = ct;
}