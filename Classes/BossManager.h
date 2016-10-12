/*
	�ļ�����BossManager.h
	��   ���� ����Boss����������
	�����ˣ� ��˾��
	*/
#ifndef _BossManager_H_
#define _BossManager_H_

#include "cocos2d.h"
#include "Player.h"
#include "Boss.h"
#include "PlayerPower.h"
USING_NS_CC;

class BossManager : public Node
{
public:
	BossManager();
	~BossManager();

	//����create()
	static BossManager* createWithLevel(Vec2 pt);

	//����create()
	static BossManager* createWithLevel(Vec2 pt, int level);

	//��ʼ��
	bool init(Vec2 pt, int level);

	//���õ�ǰ��������
	void changeStatus(CharType ps);

	//��Ϸ�߼�
	void logic(float dt);

	CC_SYNTHESIZE(Vec2, m_BOrigin, BOrigin);  //��ҳ�ʼ��

	CC_SYNTHESIZE(Boss*, m_Boss, boss);  //��ҳ�ʼ��

	void createBoss(float dt);

	void initPhysicsBody(Boss* boss);

private:

	PlayerPower* m_Power;         //����
	CharType m_CharType;        //��������
	int m_Destflag;                       //player֮ǰ�ķ���
	int m_Level;
};

#endif