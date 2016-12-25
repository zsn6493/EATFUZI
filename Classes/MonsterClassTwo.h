/*
�ļ�����Monster.h
��   ��������ģ��
�����ˣ���˾��
*/

#ifndef _Monster_Class_Two_H_
#define _Monster_Class_Two_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
#include "monsterInterface.h"
USING_NS_CC;

class MonsterTwo : public PSoul
{
public:
	MonsterTwo(void);
	~MonsterTwo(void);

	//��������
	static MonsterTwo* create(Sprite* sprite);

	//��ͼƬ��ʼ��
	virtual bool init(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

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

	void updateCallBack(float dt);

private:
	int                          m_Speed;                  //������ٶ�
	Player*                   m_Player;                 //player
	std::string              m_FileName;            //ͼƬ��Դ·��
	Rect                      m_Rect;                    //ͼ����ʾ����
};

#endif