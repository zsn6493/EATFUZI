/*
    文件名：GameOverScene.h
    描   述：游戏失败场景
    制作人：周司南
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
	
	//初始化
	virtual bool init();

    //回调函数
	void backToTollgateSelectScene(float dt);
};

#endif