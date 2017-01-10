/*
	�ļ�����Monster.h
	��   ��������ģ��
	�����ˣ���˾��
	*/

#ifndef _Monster_H_
#define _Monster_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
USING_NS_CC;

class Monster : public PSoul
{
public:
	Monster(void);
	~Monster(void);

	//��������
	static Monster* create(Sprite* sprite, int ps);

	//��ͼƬ��ʼ��
	virtual bool init(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);
	void simpleAI2(Vec2 pPos);

	//���ü�������
	void changeStatus(CharType ps);

	bool ContainMonsterPower(Player* player);

	void loadConfigure();

	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				//����������
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);				    //��ǰ������
	CC_SYNTHESIZE(int, m_iHP, iHP);			                     	//HPֵ
	CC_SYNTHESIZE(int, m_iDefens, iDefens);				    //������
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);				        //�ƶ��ٶ�
	CC_SYNTHESIZE(int, m_iCurAtkSpeed, iAtkSpeed);		//�����ٶ�

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(CharType, m_CharType, CharType);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);
	CC_SYNTHESIZE(bool, m_moveStatus, moveStatus);	//��ǰ�ж�״̬
	CC_SYNTHESIZE(bool, m_startMoveAction, startMoveAction);	//��ǰ�ж�״̬��
	CC_SYNTHESIZE(bool, m_startFightAciton, startFightAciton);	//��ǰս��״̬��
	CC_SYNTHESIZE(int, m_acceptBlood, AcceptBlood);	//��ǰ����ֵ��

	CC_SYNTHESIZE(int, m_iHurtedValue, hurtedValue);	//��ǰ�ж�״̬��
	CC_SYNTHESIZE(bool, m_iHurtedStatus, hurtedStatus);	//��ǰ�ж�״̬��
	CC_SYNTHESIZE(MonsterStatus, m_MStatus, MStatus);
	CC_SYNTHESIZE(float, m_DeltaTime, DeltaTime);

	void updateCallBack(float dt);

	void fightSpeedMonster(float dt);

private:
	int                          m_Speed;                  //������ٶ�
	Player*                   m_Player;                 //player
	std::string              m_FileName;            //ͼƬ��Դ·��
	Rect                      m_Rect;                    //ͼ����ʾ����
};
#endif