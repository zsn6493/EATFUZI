#include "envirManager.h"

EnvirManager::EnvirManager()
{
}

EnvirManager::~EnvirManager()
{
}

/*创建英雄*/
EnvirManager* EnvirManager::createWithLevel(int level,
	PlayerManager* playerManager,
	MonsterManager*  monsterManager,
	BossManager*  bossManager)
{
	EnvirManager* envirMgr = new EnvirManager();
	if (envirMgr && envirMgr->initWithLevel(level,
		playerManager,
		monsterManager,
		bossManager))
	{
		envirMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(envirMgr);
	}

	return envirMgr;
}

/*初始化*/
bool EnvirManager::initWithLevel(int level,
	PlayerManager* playerManager,
	MonsterManager*  monsterManager,
	BossManager*  bossManager)
{
	return true;
}