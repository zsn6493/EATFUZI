/*
    �ļ�����GameOverScene.h
    ��   ������Ϸʧ�ܳ���
    �����ˣ���˾��
*/

#ifndef _GameOverScene_H_
#define _GameOverScene_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOverScene : public Layer 
{
public:
    static Scene* createScene();
	CREATE_FUNC(GameOverScene);
	
	//��ʼ��
	virtual bool init();

    //�ص�����
	void backToTollgateSelectScene(float dt);
};

#endif