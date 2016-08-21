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

	//csv创建player
	static PlayerPower* createFromCsvFileByID(int iHeroID);

	//以图片初始化
	virtual bool initWithFile(Node* node);

	//以csv初始化
	bool  initFromCsvFileByID(int iHeroID);

	//火技能
	void useFire(Vec2 vec2);

	//冰技能
	void useIce(Vec2 vec2);

	//boom特效（待定）
	void useboom(Vec2 vec);

	//怪物使用火技能
	void useMonsterFire(Vec2 vec2, int flag);

	bool m_visiable;                          //怪物的是否可利用

	bool initWithFileSp(Sprite* sp);

	static PlayerPower* createSp(Sprite* sprite);

	void updateCallBack(float dt);

	int killMonster2(Vector<Monster*>* monsterList);

	virtual void update(float dt);

	Vector<Monster*>* monsterList;

	Boss* boss;

	CC_SYNTHESIZE(bool, m_FirePower, FirePower);

	int killBoss(Boss* boss);

private:
	Sprite* m_power;                        //技能图片资源
	Animate* boom;                          //爆炸特效动画
	Sprite* m_boom;                         //爆炸资源
	NodeGrid* m_Nodegrid;
};
#endif