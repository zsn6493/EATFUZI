/*
�ļ�����HomeSence.h
��   ������Ӫ����
�����ˣ���˾��
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
	//��ʼ��
	virtual bool init();

	//��ʼ��
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
	//�ص�����
	void backToTollgateSelectScene(Ref* pSender);

	//����������
	void retMainSence(Ref* pSender);

	//�ص�����ʱ��
	void callBackTime(float dt);

	//����ʱ
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