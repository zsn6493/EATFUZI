/*
    �ļ�����    WinScene.h
    �衡����    ʤ������
    �����ˣ�    ��˾��
*/
#ifndef _WinScene_H_
#define _WinScene_H_

#include "cocos2d.h"
USING_NS_CC;

class WinScene : public Layer 
{
public:
	static Scene* createScene();

	CREATE_FUNC(WinScene);

	//��ʼ��
	virtual bool init();

	//�ص�����
	void backToTollgateSelectScene(float dt);
};

#endif