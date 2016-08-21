/*
	文件名：BeginLayer.h
	描   述：开始加载资源
	制作人：周司南
	*/

#ifndef ___BeginLayer_H__
#define ___BeginLayer_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

class BeginLayer : public Layer
{
public:
	//初始化
	virtual bool init();

	//我的初始化
	void loadConfig();

	//创建create()函数
	CREATE_FUNC(BeginLayer);

	//创建场景
	static Scene* createScene();

	//调用选择场景
	void nextSceneCallback(Ref* pSender);

private:
	Menu* m_menu;
};
#endif