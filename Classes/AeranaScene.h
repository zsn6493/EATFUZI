/*
	�ļ�����    AeranaScene.h
	�衡����    ����������
	�����ˣ�    ��˾��
	*/

#ifndef _AeranaScene_H_
#define _AeranaScene_H_

#include "cocos2d.h"
USING_NS_CC;

class AeranaScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(AeranaScene);

	//��ʼ��
	virtual bool init();

	//������Դ
	void loadConfig();

	//�ص�����
	void backToTollgateSelectScene(float dt);
};

#endif