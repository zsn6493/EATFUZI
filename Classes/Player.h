/*
	�ļ�����Player.h
	��   ���� ��Ϸ����
	�����ˣ� ��˾��
	*/
#ifndef _Player_H_
#define _Player_H_

#include "Psoul.h"
#include "cocos2d.h"
USING_NS_CC;

class Player : public PSoul
{
public:
	Player(void);
	~Player(void);

	//����player
	static Player* create(Sprite* sprite);

	//csv����player
	static Player* createFromCsvFileByID(int iHeroID);

	//��ͼƬ��ʼ��
	virtual bool initWithFile(Sprite* sprite);

	//��csv��ʼ��
	bool  initFromCsvFileByID(int iHeroID);

	//��ҵ�moveby����
	void movePlayer(int flag);

	//��ʼ����������
	void initPhysicsBody();

	void moveZombie(float dt);

	void updateCallBack(float dt);

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//����������
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //��ǰ������
	CC_SYNTHESIZE(int, m_iAtkSpeed, iAtkSpeed);				//�����������λ�����룩
	CC_SYNTHESIZE(int, m_iAtkRange, iAtkRange);				//������Χ���뾶��
	CC_SYNTHESIZE(int, m_iUpgradeCostBase, iUpgradeCostBase);	//�������Ļ���ֵ
	CC_SYNTHESIZE(float, m_fUpgradeAtkBase, fUpgradeAtkBase);	//���������ӳ�ϵ��
	CC_SYNTHESIZE(int, m_speed, speed);	//���������ӳ�ϵ��                    //�ٶ�
	CC_SYNTHESIZE(int, m_type, moveType);	//���������ӳ�ϵ��                    //�ٶ�

	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//��ǰ�ж�״̬��

	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//��ǰ�ж�״̬��
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//��ǰ�ж�״̬��
};
#endif