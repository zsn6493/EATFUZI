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

	//创建函数
	static Boss* create(Sprite* sprite, int ps);

	//以图片初始化
	virtual bool init(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

	//设置技能类型
	void changeStatus(PowerEnumStatus ps);

	void updatCallBack(float);

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(PowerEnumStatus, m_Ps, PowerStatus);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);

private:
	Player* m_Player;                                //player
};
#endif