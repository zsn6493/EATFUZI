#include "envirManager.h"

EnvirManager::EnvirManager()
{
}

EnvirManager::~EnvirManager()
{
}

/*����Ӣ��*/
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

/*��ʼ��*/
bool EnvirManager::initWithLevel(Vec2 pt, int level)
{
	return true;
}