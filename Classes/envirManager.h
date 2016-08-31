#pragma once

/*
�ļ�����EnvirManager.h
��   ���� �������仯��ɳ���仯
�����ˣ� ��˾��
*/

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "PlayerPower.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "BossManager.h"
USING_NS_CC;

class EnvirManager : public Node
{
public:
	EnvirManager();
	~EnvirManager();

	//����create()
	static EnvirManager* createWithLevel(Vec2 pt);

	//��ʼ��
	bool initWithLevel(Vec2 pt);

	//����create()
	static EnvirManager* createWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	//��ʼ��
	bool initWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);

private:
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	Monster*               m_FindMonster;        //̽�⵽�Ĺ���
};
