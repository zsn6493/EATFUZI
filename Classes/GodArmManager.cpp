#include "GodArmManager.h"
#include "GodArm.h"

GodArmManager::GodArmManager()
{
}

GodArmManager::~GodArmManager()
{
}

/*创建神器*/
GodArmManager* GodArmManager::createWithLevel(int level,
	PlayerManager* playerManager,
	MonsterManager*  monsterManager,
	BossManager*  bossManager)
{
	GodArmManager* godArmMgr = new GodArmManager();
	if (godArmMgr && godArmMgr->initWithLevel(level,
		playerManager,
		monsterManager,
		bossManager))
	{
		godArmMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(godArmMgr);
	}

	return godArmMgr;
}

/*初始化*/
bool GodArmManager::initWithLevel(int level,
	PlayerManager* playerManager,
	MonsterManager*  monsterManager,
	BossManager*  bossManager)
{
	m_PlayerManager = playerManager;
	m_MonsterManager = monsterManager;
	m_BossManager = bossManager;

	return true;
}

void GodArmManager::runPower()
{
	auto godArm = GodArm::create(1);
	godArm->setPosition(Vec2(0, 0));
	//monster->setScale(0.5f);
	this->addChild(godArm, 1);

	int value = godArm->runPower();
	m_PlayerManager->setHurtValue(value);
}