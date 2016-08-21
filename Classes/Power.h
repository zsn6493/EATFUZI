/*
	�ļ�����Power.h
	��   ���� ���ܻ���
	�����ˣ� ��˾��
	*/
#ifndef _PPower_H_
#define _PPower_H_

#include "cocos2d.h"
USING_NS_CC;

class PPower : public Node
{
public:
	PPower();
	~PPower();

	//��Sprite����Աm_sprite
	void bindSprite(Sprite* sprite);

	//��ȡSprite
	Sprite* getSprite();

	//������
	void hurtMe(int iHurtValue);

	//����m_sprite
	void cleanSprite();

private:
	Sprite* m_sprite;                                                    //����sprite
};

#endif