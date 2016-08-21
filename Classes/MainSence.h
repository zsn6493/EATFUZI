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

	static MainSence*  create(int level, ShowLayer* showLayer);

	//初始化
	bool init(int level, ShowLayer* showLayer);

	void OnEnter();

	void update(float dt);

	//订阅函数GameWin
	void killedMonsterNum(Ref* pData);

	//订阅函数GameOver
	void recvGameOver(Ref* pData);

	//订阅函数更换背景
	void recvChangeBK(Ref* pData);

	//消耗杀敌数
	void deNum(Ref* pData);

	//逻辑
	void logic(float dt);

	//设置背景与游戏视角
	void setViewPoint();

	//杀敌数
	CC_SYNTHESIZE(int, m_Num, DeNum);

	//存储当前场景
	CC_SYNTHESIZE(Scene*, m_oriScene, OriScene);

private:
	Layer*  m_BK;                   //背景层
	int        m_level;                        //功能选择
	ShowLayer* m_viewLayer; //视图层
	Layer*         m_moveLayer;        //移动背景
	Label*         m_Label;        //杀怪数Label
};
#endif // ___MAINSENCE_H__