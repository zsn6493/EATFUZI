/*
文件名：Monster.h
描   述：怪物模型
制作人：周司南
*/

#ifndef _Monster_Class_One_H_
#define _Monster_Class_One_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
#include "monsterInterface.h"
USING_NS_CC;

class MonsterOne : public PSoul, public monsterInterface
{
public:
	MonsterOne(void);
	~MonsterOne(void);

	//创建函数
	static MonsterOne* create(Sprite* sprite);

	//以图片初始化
	virtual bool init(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//基础攻击力
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //当前攻击力
	CC_SYNTHESIZE(int, m_iHP, iHP);			                     	//HP值
	CC_SYNTHESIZE(int, m_iDefens, iDefens);				    //防御力
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);				        //移动速度
	CC_SYNTHESIZE(int, m_iCurAtkSpeed, iAtkSpeed);		//攻击速度

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(CharType, m_CharType, CharType);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);
	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//当前行动状态
	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//当前行动状态。
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//当前战斗状态。
	CC_SYNTHESIZE(int, m_acceptBlood, AcceptBlood);	//当前受伤值。

	void updateCallBack(float dt);

private:
	int                          m_Speed;                  //怪物的速度
	Player*                   m_Player;                 //player
	std::string              m_FileName;            //图片资源路径
	Rect                      m_Rect;                    //图形显示矩形
};

#endif