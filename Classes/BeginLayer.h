/*
	�ļ�����BeginLayer.h
	��   ������ʼ������Դ
	�����ˣ���˾��
	*/

#ifndef ___BeginLayer_H__
#define ___BeginLayer_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

class BeginLayer : public Layer
{
public:
	//��ʼ��
	virtual bool init();

	//�ҵĳ�ʼ��
	void loadConfig();

	//��������
	static Scene* createScene();

	//����create()����
	CREATE_FUNC(BeginLayer);

	//����ѡ�񳡾�
	void nextSceneCallback(Ref* pSender);

private:
	Menu* m_menu;
};
#endif