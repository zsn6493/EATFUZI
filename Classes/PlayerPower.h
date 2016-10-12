/*
文件名：PlayerPower.h
描   述： 主角技能
制作人： 周司南
*/
#ifndef _PlayerPower_H_
#define _PlayerPower_H_

#include "Power.h"
#include "Player.h"
#include "cocos2d.h"
#include "AnimoTool.h"
USING_NS_CC;
class Monster;
class Boss;
class PlayerPower : public PPower
{
public:
	PlayerPower(void);
	~PlayerPower(void);

	//创建player
	static PlayerPower* create(Node* node);

	//以图片初始化
	virtual bool initWithFile(Node* node);

	bool initWithFileSp(Sprite* sp, int powerNum, int bloodValue);

	static PlayerPower* createSp(Sprite* sprite, int powerNum, int bloodValue);

	int singlePowerkillMonster(Vector<Monster*>* monsterList);

	int singlePowerkillBoss(Boss* boss);

	int longPowerkillMonster(Vector<Monster*>* monsterList);

	void updateCallBack(float dt);

	virtual void singleUpdate(float dt);

	virtual void longUpdate(float dt);

	Vector<Monster*>* monsterList;
	Boss* boss;

	CC_SYNTHESIZE(bool, m_FirePower, FirePower);
	CC_SYNTHESIZE(int, m_Bload, Bload);

private:
	Sprite* m_power;                        //技能图片资源
	Animate* boom;                          //爆炸特效动画
	Sprite* m_boom;                         //爆炸资源
	NodeGrid* m_Nodegrid;
};
#endif