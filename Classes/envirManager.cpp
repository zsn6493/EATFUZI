#include "envirManager.h"

EnvirManager::EnvirManager()
{
}

EnvirManager::~EnvirManager()
{
}

/*创建英雄*/
EnvirManager* EnvirManager::createWithLevel(Vec2 pt, int level)
{
	EnvirManager* envirMgr = new EnvirManager();
	if (envirMgr && envirMgr->initWithLevel(pt, level))
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
bool EnvirManager::initWithLevel(Vec2 pt, int level)
{
	return true;
}