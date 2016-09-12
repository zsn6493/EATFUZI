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
	void changeStatus(PowerEnumStatus ps);

	bool ContainMonsterPower(Player* player);

	void loadConfigure();

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(PowerEnumStatus, m_Ps, PowerStatus);
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