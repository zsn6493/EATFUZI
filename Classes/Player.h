/*
	文件名：Player.h
	描   述： 游戏主角
	制作人： 周司南
	*/
#ifndef _Player_H_
#define _Player_H_

#include "Psoul.h"
#include "cocos2d.h"
#include "PowerEnum.h"
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

	void fightSpeedZombie(float dt);

	void updateCallBack(float dt);

	CC_SYNTHESIZE(std::string, m_BattleName, BattleName);	//称号
	CC_SYNTHESIZE(int, m_PepLevel, PepLevel);	//人物等级

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//基础攻击力
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //当前攻击力
	CC_SYNTHESIZE(int, m_iHP, iHP);			                     	//HP值
	CC_SYNTHESIZE(int, m_iDefens, iDefens);				    //防御力
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);				        //移动速度
	CC_SYNTHESIZE(int, m_iCurAtkSpeed, iAtkSpeed);		//攻击速度
	CC_SYNTHESIZE(int, m_type, moveType);	                    //zombie类型

	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//当前行动状态。

	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//当前行动状态。
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//当前行动状态。

	CC_SYNTHESIZE(int, m_iHurtedValue, hurtedValue);	//当前行动状态。
	CC_SYNTHESIZE(bool, m_iHurtedStatus, hurtedStatus);	//当前行动状态。
	CC_SYNTHESIZE(MonsterStatus, m_ZombieStatus, ZombieStatus);
	CC_SYNTHESIZE(float, m_DeltaTime, DeltaTime);
};
#endif