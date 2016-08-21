/*
�ļ�����PSoul.h
��   ���� ����͹���Ļ���
�����ˣ� ��˾��
*/
#ifndef _PSoul_H_
#define _PSoul_H_

#include "cocos2d.h"
USING_NS_CC;

class PSoul : public Node
{
public:
	PSoul();
	~PSoul();

	//��Sprite����Աm_sprite
	void bindSprite(Sprite* sprite);

	//��ȡSprite
	Sprite* getSprite();

	//������
	void hurtMe(int iHurtValue);

	//�Ƿ�����
	bool isDead();

	//����Sprite
	void cleanSprite();

protected:
	virtual void onDead();		                                        //ʵ������ʱ����
	virtual void onBindSprite();                                      // �󶨾������ʱ����
	virtual void onHurt(int iHurtValue);                            //���˺�ʱ����

private:
	Sprite* m_sprite;                                                    //����sprite
	bool m_isDead;                                                     //����Ƿ�����

	CC_SYNTHESIZE(int, m_ID, ID);	                        //ʵ��ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);	    //ģ��ID����ԴID��
	CC_SYNTHESIZE(std::string, m_sName, sName);	//����
	CC_SYNTHESIZE(int, m_iHP, iHP);			                //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);	        //����
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);		        //�ƶ��ٶ�
	CC_SYNTHESIZE(int, m_iLevel, iLevel);	            	//�ȼ�
};

#endif