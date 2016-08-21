/*
�ļ�����Boss.h
��   ����Boss����
�����ˣ���˾��
*/
#ifndef _Boss_H_
#define _Boss_H_

#include "cocos2d.h"
#include "Player.h"
#include "PowerEnum.h"
#include "PlayerPower.h"
USING_NS_CC;

class Boss : public PSoul
{
public:
	Boss(void);
	~Boss(void);

	//ͨ��csv����monster
	Boss* createFromCsvFileByID(int iHeroID);

	//��ʼ��
	bool initFromCsvFileByID(int iHeroID);

	//��������
	static Boss* create(Sprite* sprite, int ps);

	//��ͼƬ��ʼ��
	virtual bool initWithFile(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

	//���ü�������
	void changeStatus(PowerEnumStatus ps);

	void updatCallBack(float);

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(PowerEnumStatus, m_Ps, PowerStatus);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);

private:
	//PlayerPower* m_MonsterPower;          //���＼��
	int m_Speed;                                       //������ٶ�
	Player* m_Player;                                //player
	//PowerEnumStatus m_Ps;                     //��������
	//Vec2 m_Orgin;                                     //��ʼ�����
	int m_Times;                                        //Boss�Nɪ����
};
#endif