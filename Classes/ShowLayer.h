/*
	文件名：ShowSence.h
	描   述： 主游戏场景
	制作人： 周司南
	*/
#ifndef ___ShowSence_H__
#define ___ShowSence_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "BossManager.h"
#include "GodArmManager.h"
#include "Boss.h"

USING_NS_CC;

class ShowLayer : public Layer
{
public:
	ShowLayer();
	~ShowLayer();

	virtual void onEnter() override;

	bool init(int level);

	//我的初始化
	void loadConfig(int level);

	//初始化物理对象
	void initPhyscsObject(Rect* m);

	//退出回调
	void menuCloseCallback(cocos2d::Ref* pSender);

	//设置以player为中心
	Point setViewPoint();

	//移动player
	void movePlayer(int flag);

	static ShowLayer* create(int level);

	//使用技能
	void usePlayerPower();

	//使用大招
	void usePlayerBigPower();

	//获取怪物的技能
	void parseMonsterPower(int flag);

	//创建怪物
	void retBeginLayer();

	//跳跃
	void jumpPlayer();

	//逻辑
	void logic(float dt);

	//Boss逻辑
	void Bosslogic(float dt);

	//怪物逻辑
	void Monsterlogic(float dt);

	//人物移动动画
	void movePlayerAnimotion();

	//停止人物动画
	void stopPlayerAnimotion();

	//使用技能
	void useFZPower(Vec2 pt);

	//使用zombie
	void useZombie(int level);

	CC_SYNTHESIZE(bool, m_FirePower, FirePower);
	CC_SYNTHESIZE(int, m_Rand, Rand);
	CC_SYNTHESIZE(PhysicsWorld*, m_World, World);
	//void removeJoint();

private:
	PlayerManager*       m_PlayerManager;     //玩家
	MonsterManager*    m_MonsterManager;  // 怪物
	BossManager*         m_BossManager;       //Boss
	GodArmManager*    m_GodArmManager;     //玩家
	TMXTiledMap*         m_Map;         //地图
	Rect m_Rect;
	Boss* m_Boss;                           //Boss
	int m_MaxLength;                      //地图最大值
	int m_MinLength;                       //地图长度最小值
	int m_Level;                               //地图level
	//PhysicsJointDistance* m_Joint; 线连接
};
#endif