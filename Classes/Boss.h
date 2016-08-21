/*
文件名：Boss.h
描   述：Boss对象
制作人：周司南
*/
#ifndef _Boss_H_
#define _Boss_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
USING_NS_CC;

class Boss : public PSoul
{
public:
	Boss(void);
	~Boss(void);

	//通过csv创建monster
	Boss* createFromCsvFileByID(int iHeroID);

	//初始化
	bool initFromCsvFileByID(int iHeroID);

	//创建函数
	static Boss* create(Sprite* sprite, int ps);

	//以图片初始化
	virtual bool initWithFile(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

	//设置技能类型
	void changeStatus(PowerEnumStatus ps);

	void updatCallBack(float);

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(PowerEnumStatus, m_Ps, PowerStatus);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);

private:
	//PlayerPower* m_MonsterPower;          //怪物技能
	int m_Speed;                                       //怪物的速度
	Player* m_Player;                                //player
	//PowerEnumStatus m_Ps;                     //技能类型
	//Vec2 m_Orgin;                                     //初始座标点
	int m_Times;                                        //Boss嘚瑟次数
};
#endif