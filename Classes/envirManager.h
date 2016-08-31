#pragma once

/*
文件名：EnvirManager.h
描   述： 管理环境变化造成场面变化
制作人： 周司南
*/

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "PlayerPower.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "BossManager.h"
USING_NS_CC;

class EnvirManager : public Node
{
public:
	EnvirManager();
	~EnvirManager();

	//创建create()
	static EnvirManager* createWithLevel(Vec2 pt);

	//初始化
	bool initWithLevel(Vec2 pt);

	//创建create()
	static EnvirManager* createWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	//初始化
	bool initWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);

private:
	Player*                  m_Player;                //冒险家
	PlayerPower*        m_Power;                 //技能
	Monster*               m_FindMonster;        //探测到的怪物
};
