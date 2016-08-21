/*
	文件名：    AeranaScene.h
	描　述：    竞技场场景
	创建人：    周司南
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

	//初始化
	virtual bool init();

	//加载资源
	void loadConfig();

	//回调函数
	void backToTollgateSelectScene(float dt);
};

#endif