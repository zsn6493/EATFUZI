/*
	文件名：Monster.h
	描   述：怪物模型
	制作人：周司南
	*/

#ifndef _Monster_H_
#define _Monster_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
USING_NS_CC;

class Monster : public PSoul
{
public:
	Monster(void);
	~Monster(void);

	//通过csv创建monster
	Monster* createFromCsvFileByID(int iHeroID);

	//初始化
	bool initFromCsvFileByID(int iHeroID);

	//创建函数
	static Monster* create(Sprite* sprite, int ps);

	//以图片初始化
	virtual bool initWithFile(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);
	void simpleAI2(Vec2 pPos);

	//设置技能类型
	void changeStatus(PowerEnumStatus ps);

	bool ContainMonsterPower(Player* player);

	void loadConfigure();

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(PowerEnumStatus, m_Ps, PowerStatus);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);
	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//当前行动状态
	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//当前行动状态。
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//当前行动状态。

	void updateCallBack(float dt);

private:
	int                          m_Speed;                  //怪物的速度
	Player*                   m_Player;                 //player
	std::string              m_FileName;            //图片资源路径
	Rect                      m_Rect;                    //图形显示矩形
};
#endif