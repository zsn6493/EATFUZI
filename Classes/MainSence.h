/*
文件名：MainSence.h
描   述：是主游戏场景
制作人：周司南
*/

#ifndef ___MAINSENCE_H__
#define ___MAINSENCE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ShowLayer.h"
USING_NS_CC;

class MainSence : public Layer
{
public:
	MainSence();
	~MainSence();

	//创建场景
	static cocos2d::Scene* createScene(int level);

	static MainSence*  create(int level);

	//初始化
	bool init(int level);

	void OnEnter();

	void update(float dt);

	//订阅函数GameOver
	void recvGameOver(Ref* pData);

	//订阅函数更换背景
	void recvChangeBK(Ref* pData);

	//消耗的点数
	void deNum(Ref* pData);

	//获得的点数
	void increNum(Ref* pData);

	//杀敌数
	CC_SYNTHESIZE(int, m_KillMonsterNum, KillMonsterNum);

	//存储当前场景
	CC_SYNTHESIZE(Scene*, m_oriScene, OriScene);

private:
	int        m_level;                        //背景选择选择
	Label*  m_Label;                       //杀怪数Label
	Layer*  m_BackGrandLayer;    //背景层
};
#endif // ___MAINSENCE_H__