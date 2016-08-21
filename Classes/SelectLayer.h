/*
文件名：BeginLayer.h
描   述： 过度场景
制作人： 周司南
*/

#ifndef ___SelectLayer_H__
#define ___SelectLayer_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class SelectLayer : public Layer
{
public:
	//初始化
	virtual bool init();

	//我的初始化
	void loadConfig();

	static Scene* createScene();

	//创建create()函数
	CREATE_FUNC(SelectLayer);

	//控制选关按钮
	void moveToLeft(Ref* sender, TouchEventType type);
	void moveToRight(Ref* sender, TouchEventType type);

	//按钮AB 功能待定
	void useAButton(Ref* sender, TouchEventType type);
	void useBButton(Ref* sender, TouchEventType type);

	//主游戏场景
	void callGameScene(Ref* pSender);

	//竞技场场景
	void callAeranaScene(Ref* pSender, TouchEventType type);

	//获取特殊技能场景
	void callHomeScene(Ref* pSender, TouchEventType type);

	//测试场景
	void callPlayScene(Ref* pSender, TouchEventType type);

	//好友系统
	void callFriendsScene(Ref* pSender, TouchEventType type);

	//背包界面
	void callBagScene(Ref* pSender, TouchEventType type);

	//设置按钮
	void callSettingScene(Ref* pSender, TouchEventType type);

private:
	Sprite* m_earth;       //地球;
	Sprite* m_sp;
};

#endif