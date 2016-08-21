/*
    文件名：    WinScene.h
    描　述：    胜利场景
    制作人：    周司南
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

	//初始化
	virtual bool init();

	//回调函数
	void backToTollgateSelectScene(float dt);
};

#endif