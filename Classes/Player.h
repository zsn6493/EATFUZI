/*
	文件名：Player.h
	描   述： 游戏主角
	制作人： 周司南
	*/
#ifndef _Player_H_
#define _Player_H_

#include "Psoul.h"
#include "cocos2d.h"
USING_NS_CC;

class Player : public PSoul
{
public:
	Player(void);
	~Player(void);

	//创建player
	static Player* create(Sprite* sprite);

	//以图片初始化
	virtual bool init(Sprite* sprite);

	void Player::setSpecialName(std::string battleName);

	//玩家的moveby动作
	void movePlayer(int flag);

	//初始化物理属性
	void initPhysicsBody();

	void moveZombie(float dt);

	void updateCallBack(float dt);

	CC_SYNTHESIZE(std::string, m_BattleName, BattleName);	//称号
	CC_SYNTHESIZE(int, m_PepLevel, PepLevel);	//人物等级

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//基础攻击力
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //当前攻击力
	CC_SYNTHESIZE(int, m_iAtkSpeed, iAtkSpeed);				//攻击间隔（单位：毫秒）
	CC_SYNTHESIZE(int, m_iAtkRange, iAtkRange);				//攻击范围（半径）
	CC_SYNTHESIZE(int, m_iUpgradeCostBase, iUpgradeCostBase);	//升级消耗基础值
	CC_SYNTHESIZE(float, m_fUpgradeAtkBase, fUpgradeAtkBase);	//升级攻击加成系数
	CC_SYNTHESIZE(int, m_speed, speed);	//升级攻击加成系数                    //速度
	CC_SYNTHESIZE(int, m_type, moveType);	//升级攻击加成系数                    //速度

	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//当前行动状态。

	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//当前行动状态。
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//当前行动状态。
};
#endif