/*
文件名：ControlLayer.h
描   述：ControlLayer 控制层 加载UI 触摸屏幕信号接收
制作人：周司南
*/
#ifndef ___CONTROLLAYER_H__
#define ___CONTROLLAYER_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "cocostudio\CocoStudio.h"
#include "Player.h"
#include "Monster.h"
#include "ShowLayer.h"
USING_NS_CC;

using namespace cocostudio;
using namespace cocos2d::ui;

class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer();
	~ControlLayer();

	//创建场景
	static cocos2d::Scene* createScene();

	//创建图层
	static ControlLayer* create(Layer* layer);

	//初始化带layer参数
	bool init(Layer* layer);

	//加载资源
	void loadConfig();

	//关闭按钮的回调
	void menuCloseCallback(Ref* sender, TouchEventType type);

	//冒险者使用技能回调
	void userPowerCallback(Ref* sender, TouchEventType type);

	//冒险者获取技能回调
	void eatMonsterCallback(Ref* sender, TouchEventType type);

	//冒险者跳跃技能回调
	void useJumpCallback(Ref* sender, TouchEventType type);

	//冒险者使用大招回调
	void userBigPowerCallback(Ref* sender, TouchEventType type);

	//冒险者左移动回调
	void moveToLeft(Ref* sender, TouchEventType type);

	//冒险者右移动回调
	void moveToRight(Ref* sender, TouchEventType type);

	//返回选择界面接口
	void gameOverCallback(Ref* pSender);

	//使用技能
	void usePower1(Ref* pSender);

	//touches 响应函数
	void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	//void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	//update function
	void update(float delta);

	//左移
	Action* MoveLeft;

	//右移
	Action* MoveRight;

	//长按处理
	void updatelongprogress(float ft);

	//单点处理
	void updateSingleDelay(float ft);

	//双击处理
	void updateDoubleDelay(float ft);

	//获取当前点击时刻的时间点
	long long getCurrentTime();

	//技能提升函数
	void usePowerUp(Ref* pSender);

	//人物技能提升
	void usePeoUp(Ref* pSender);
private:
	ShowLayer* m_viewLayer;                	//游戏视图层
	int m_flag;                                            //移动方向标识
	int m_Num[100];
	int m_Count;
	bool m_longProgress;                           //长按状态标识
	Vec2 m_startPoint;
	Vec2 m_endPoint;
	long long m_startTime;
};

#endif // ___CONTROLLAYER_H__