#pragma once

/*
文件名：GodArmManager.h
描   述： 神器管理
制作人： 周司南
*/

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "PlayerPower.h"
USING_NS_CC;

class GodArmManager : public Node
{
public:
	GodArmManager();
	~GodArmManager();

	//创建create()
	static GodArmManager* createWithLevel(Vec2 pt);

	//初始化
	bool initWithLevel(Vec2 pt);

	//创建create()
	static GodArmManager* createWithLevel(Vec2 pt, int level);

	//初始化
	bool initWithLevel(Vec2 pt, int level);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);

private:
	Player*                  m_Player;                //冒险家
	PlayerPower*        m_Power;                 //技能
	Monster*               m_FindMonster;        //探测到的怪物
};
