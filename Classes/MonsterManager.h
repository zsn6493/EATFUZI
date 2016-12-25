/*
	�ļ�����MonsterManager.h
	��   ����������ﴴ�����߼�
	�����ˣ���˾��
	*/

#ifndef _MonsterManager_H_
#define _MonsterManager_H_

#include "cocos2d.h"
#include "PlayerPower.h"
#include "Boss.h"
USING_NS_CC;

class Monster;
class MonsterManager : public Node
{
public:
	MonsterManager();
	~MonsterManager();

	static MonsterManager* create(ValueVector monsterPoints, int level);

	//��ʼ������
	bool init(ValueVector monsterPoints, int level);

	//�߼�����
	void logic();

	//����player
	Vector<Monster*>* getMonsterList();

	//�����صĹ���vivsiable
	void visiableMonster();

	//ʹ�ü���
	void usePower();

	//�ж����
	int killPlayer(Player* player);

	int killPlayer(Vector<Player*>* playerList);

	//��ʼ��monster ������� ��ʱ����
	void initPhysicsBody(Monster* monster);

	void MonsterManager::initMonsterProper(Monster* monster,
		int baseAtk,
		int curAtk,
		int hp,
		int defens,
		int speed,
		int curAtkSpeed);

	void callMonsterIntoMap(float dt);
	void callMonsterIntoMap2(float dt);

	CC_SYNTHESIZE(int, m_MonsterNum, MonsterNum);
	CC_SYNTHESIZE(int, m_DeadMonsterNum, DeadMonsterNum);

	void updateCallback(float dt);

	void MonsterManager::controlAction(float dt);

private:
	ValueVector                 m_monsterPoints;
	Vector<Monster*>        m_monsterList;                  //�����б�
	Boss*                           m_boss;
	int                                m_level;
};
#endif