#include "GameTimer.h"

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

bool GameTimer::init(float time)
{
	m_pTime = time;

	m_label = LabelTTF::create();
	m_label->setPosition(0, 0);
	this->addChild(m_label);

	schedule(schedule_selector(GameTimer::update));

	return true;
}

void GameTimer::update(float delta)
{
	m_pTime -= delta;
	char* mtime = new char[10];
	//此处只是显示分钟数和秒数  自己可以定义输出时间格式
	sprintf(mtime, "%d : %d", (int)m_pTime / 60, (int)m_pTime % 60);
	m_label->setString(mtime);
}

GameTimer* GameTimer::createTimer(float time)
{
	GameTimer* gametimer = new GameTimer;
	if (gametimer && gametimer->init(time))
	{
		gametimer->autorelease();
		return gametimer;
	}
	else
	{
		delete gametimer;
		gametimer = NULL;
	}
	return NULL;
}