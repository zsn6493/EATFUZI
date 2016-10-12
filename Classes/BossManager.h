/*
	文件名：BossManager.h
	描   述： 管理Boss创建，功能
	制作人： 周司南
	*/
#ifndef _BossManager_H_
#define _BossManager_H_

#include "cocos2d.h"
#include "Player.h"
#include "Boss.h"
#include "PlayerPower.h"
USING_NS_CC;

class BossManager : public Node
{
public:
	BossManager();
	~BossManager();

	//创建create()
	static BossManager* createWithLevel(Vec2 pt);

	//创建create()
	static BossManager* createWithLevel(Vec2 pt, int level);

	//初始化
	bool init(Vec2 pt, int level);

	//设置当前技能类型
	void changeStatus(CharType ps);

	//游戏逻辑
	void logic(float dt);

	CC_SYNTHESIZE(Vec2, m_BOrigin, BOrigin);  //玩家初始点

	CC_SYNTHESIZE(Boss*, m_Boss, boss);  //玩家初始点

	void createBoss(float dt);

	void initPhysicsBody(Boss* boss);

private:

	PlayerPower* m_Power;         //技能
	CharType m_CharType;        //技能类型
	int m_Destflag;                       //player之前的方向
	int m_Level;
};

#endif