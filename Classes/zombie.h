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

class Zombie : public PSoul
{
public:
	Zombie(void);
	~Zombie(void);

	//����Zombie
	static Zombie* create(Sprite* sprite);

	//��ͼƬ��ʼ��
	virtual bool init(Sprite* sprite);

	void setSpecialName(std::string battleName);

	//��ʼ����������
	void initPhysicsBody();

	void moveZombie(float dt);

	void updateCallBack(float dt);

	CC_SYNTHESIZE(std::string, m_BattleName, BattleName);	//�ƺ�
	CC_SYNTHESIZE(int, m_PepLevel, PepLevel);	//����ȼ�

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//����������
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //��ǰ������
	CC_SYNTHESIZE(int, m_iHP, iHP);			                     	//HPֵ
	CC_SYNTHESIZE(int, m_iDefens, iDefens);				    //������
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);				        //�ƶ��ٶ�
	CC_SYNTHESIZE(int, m_iCurAtkSpeed, iAtkSpeed);		//�����ٶ�
	CC_SYNTHESIZE(int, m_type, moveType);	                    //zombie����

	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//��ǰ�ж�״̬��

	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//��ǰ�ж�״̬��
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//��ǰ�ж�״̬��
};
#endif