/*
文件名：HomeSence.h
描   述：经营场景
制作人：周司南
*/

#ifndef _HomeScene_H_
#define _HomeScene_H_

#include "cocos2d.h"
#include "GameTimer.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HomeScene : public Layer, TableViewDataSource, TableViewDelegate
{
public:
	HomeScene();
    ~HomeScene();

	static Scene* createScene();

	//CREATE_FUNC(HomeScene);
	static HomeScene* create();
	//初始化
	virtual bool init();

	//初始化
	virtual bool init2(HomeScene* layer);

	void update(float delta);

	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);

	void onBtnCallback(Ref * obj);

	Vec2 treeOnePoint;

private:
	//回调函数
	void backToTollgateSelectScene(Ref* pSender);

	//返回主场景
	void retMainSence(Ref* pSender);

	//回调返回时间
	void callBackTime(float dt);

	//倒计时
	GameTimer* m_timer;

	Vector<Sprite*> m_sp;

	int m_num;
	TableView * m_tableView;

	Sprite* m_pView;
	Sprite* m_pBg;

	bool m_Creating;

	int m_TouchIDx;
};
#endif