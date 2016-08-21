#include "GodArmManager.h"

GodArmManager::GodArmManager()
{
}

GodArmManager::~GodArmManager()
{
}

/*创建英雄*/
GodArmManager* GodArmManager::createWithLevel(Vec2 pt, int level)
{
	GodArmManager* godArmMgr = new GodArmManager();
	if (godArmMgr && godArmMgr->initWithLevel(pt, level))
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
bool GodArmManager::initWithLevel(Vec2 pt, int level)
{
	return true;
}