#pragma once

/*
�ļ�����GodArmManager.h
��   ���� ��������
�����ˣ� ��˾��
*/

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "PlayerPower.h"
USING_NS_CC;

class GodArmManager : public Node
{
public:
	GodArmManager();
	~GodArmManager();

	//����create()
	static GodArmManager* createWithLevel(Vec2 pt);

	//��ʼ��
	bool initWithLevel(Vec2 pt);

	//����create()
	static GodArmManager* createWithLevel(Vec2 pt, int level);

	//��ʼ��
	bool initWithLevel(Vec2 pt, int level);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);

private:
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	Monster*               m_FindMonster;        //̽�⵽�Ĺ���
};
