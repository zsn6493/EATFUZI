#pragma once
/*
�ļ�����GodArmManager.h
��   ���� ��������
�����ˣ� ��˾��
*/

#include "PlayerManager.h"
#include "MonsterManager.h"
#include "BossManager.h"
#include "GodArmManager.h"

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
	static GodArmManager* createWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	//��ʼ��
	bool initWithLevel(int level,
		PlayerManager* playerManager,
		MonsterManager*  monsterManager,
		BossManager*  bossManager);

	void runPower();
	void runPower1();

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);

private:
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	Monster*               m_FindMonster;        //̽�⵽�Ĺ���
	PlayerManager*    m_PlayerManager;
	MonsterManager* m_MonsterManager;
	BossManager*      m_BossManager;
};
