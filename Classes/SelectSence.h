/*
文件名：SelectSence.h
描   述：关卡选择
制作人：周司南
*/

#ifndef ___SelectSence_H__
#define ___SelectSence_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

class SelectSence : public Layer
{
public:
	SelectSence();
	~SelectSence();
	//初始化
	virtual bool init();

	//我的初始化
	void loadConfig();

	//创建场景
	static Scene* createScene();

	//创建create()函数
	CREATE_FUNC(SelectSence);

	//touches 响应函数
	void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	Vec2 setViewPoint();

	//update function
	void update(float delta);

	//调用选择场景
	void nextSceneCallback(Ref* pSender);

private:
	Sprite* m_Sp;
	int speed;
	Menu* m_menu;
	Layer* m_ColorLayer;
	int DirX;
	int DirY;
	bool m_Touch;
	float delta;
};
#endif