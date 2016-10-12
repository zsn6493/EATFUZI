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

	//��������
	static Boss* create(Sprite* sprite, int ps);

	//��ͼƬ��ʼ��
	virtual bool init(Sprite* sprite);

	//AI
	void simpleAI(Vec2 pPos);

	//���ü�������
	void changeStatus(CharType ps);

	void updatCallBack(float);

	CC_SYNTHESIZE(PlayerPower*, m_MonsterPower, Power);
	CC_SYNTHESIZE(CharType, m_CharType, CharType);
	CC_SYNTHESIZE(Vec2, m_Orgin, Origin);

private:
	Player* m_Player;                                //player
};
#endif