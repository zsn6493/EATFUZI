#include "envirManager.h"

EnvirManager::EnvirManager()
{
}

EnvirManager::~EnvirManager()
{
}

/*����Ӣ��*/
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

/*��ʼ��*/
bool EnvirManager::initWithLevel(int level,
	PlayerManager* playerManager,
	MonsterManager*  monsterManager,
	BossManager*  bossManager)
{
	return true;
}