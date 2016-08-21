/*
	文件名：    GameTimer.h
	描　述：    倒计时
	制作人：    周司南
	*/
#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameTimer : public cocos2d::Node
{
public:
	GameTimer();

	virtual ~GameTimer();

	static GameTimer* createTimer(float time);

	//初始化
	bool init(float time);

	//update函数
	void update(float delta);

private:
	LabelTTF*			m_label;            //时间显示
	float					m_pTime;          //时间
};

#endif