/*
	�ļ�����    GameTimer.h
	�衡����    ����ʱ
	�����ˣ�    ��˾��
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

	//��ʼ��
	bool init(float time);

	//update����
	void update(float delta);

private:
	LabelTTF*			m_label;            //ʱ����ʾ
	float					m_pTime;          //ʱ��
};

#endif