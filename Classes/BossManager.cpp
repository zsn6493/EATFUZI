#include "BossManager.h"
#include "PowerEnum.h"
#include "WinScene.h"

#define NOTIFY cocos2d::NotificationCenter::getInstance()

BossManager::BossManager()
{
	m_Ps = PowerEnumStatus::useNone;
	m_Power = nullptr;
	m_Destflag = 1;
	m_Boss = nullptr;
	m_BOrigin = Vec2(0, 0);
	m_Boss = nullptr;
}

BossManager::~BossManager()
{
	this->unscheduleAllSelectors();
}

/*初始化*/
bool BossManager::initWithLevel(Vec2 pt, int level)
{
	m_Level = level;

	if (level == 3)
	{
	}

	//创建player的技能
	//m_power = PlayerPower::create(m_boss);
	//this->addChild(m_power);

	return true;
}

/*创建英雄*/
BossManager* BossManager::createWithLevel(Vec2 pt, int level)
{
	BossManager* bossMgr = new BossManager();
	if (bossMgr && bossMgr->initWithLevel(pt, level))
	{
		bossMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bossMgr);
	}

	return bossMgr;
}

void BossManager::createBoss(float dt)
{
	m_Boss = Boss::create(Sprite::create(BOSS_TWO), useFire);
	m_Boss->setAnchorPoint(Vec2(0.5, 0.5));
	m_Boss->setOrigin(m_BOrigin);
	m_Boss->setPosition(m_BOrigin);
	m_Boss->setiHP(50);

	initPhysicsBody(m_Boss);

	auto action = AnimoTool::createBoss2Animotion();
	m_Boss->getSprite()->runAction(action);

	this->addChild(m_Boss, 1);

	this->schedule(schedule_selector(BossManager::logic), 1.0f);
}

void BossManager::initPhysicsBody(Boss* boss)
{
	auto bossBody = PhysicsBody::createBox(boss->getContentSize(),
		PHYSICSBODY_MATERIAL_DEFAULT);
	bossBody->setRotationEnable(false);
	bossBody->getShape(0)->setDensity(0.0f);
	bossBody->getShape(0)->setMass(50);

	bossBody->setCategoryBitmask(1);
	bossBody->setContactTestBitmask(2);
	bossBody->setCollisionBitmask(2);

	//设置物体是否受重力系数影响
	bossBody->setGravityEnable(true);

	boss->setPhysicsBody(bossBody);
}

/*英雄逻辑*/
void BossManager::logic(float dt)
{
	//m_boss->simpleAI(playerPos);
	if (m_Boss == nullptr)
		return;

	if (m_Boss->isDead())
	{
		this->unschedule(schedule_selector(BossManager::logic));
		m_Boss->removeFromParentAndCleanup(true);
		m_Boss = nullptr;
		NOTIFY->postNotification("GameOver");
	}
}