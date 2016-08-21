#include "SelectLayer.h"
#include "AeranaScene.h"
#include "HomeScene.h"
#include "MainSence.h"
#include "GamePause.h"
#include "ScrollBarTest.h"
#include "AnimoTool.h"

using namespace cocos2d::ui;
using namespace cocostudio;

Scene* SelectLayer::createScene()
{
	//创建场景
	auto scene = Scene::create();

	//创建层
	auto layer = SelectLayer::create();

	scene->addChild(layer);

	return scene;
}

bool SelectLayer::init()
{
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	//加载资源，创建manager
	loadConfig();

	return true;
}

/*加载资源*/

void SelectLayer::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Sprite* bk = Sprite::create("bk_blue.png");
	bk->setAnchorPoint(Vec2(0, 0));
	this->addChild(bk, 1);

	//添加选择图片
    m_earth = Sprite::create("chose750.png");
	m_earth->setAnchorPoint(Vec2(0.5, 0.5));
	m_earth->setPosition(Vec2(visibleSize.width / 2, 0));
	this->addChild(m_earth, 2);
	
	//添加选择按钮
	auto closeItem = MenuItemImage::create(
		"plc.png",
		"plc.png",
		CC_CALLBACK_1(SelectLayer::callGameScene, this));

	closeItem->setAnchorPoint(Vec2(0.5, 0.5));
	closeItem->setPosition(Vec2(visibleSize.width / 2, m_earth->getContentSize().height / 2 + 50));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 4);

	//调用UI
	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("NewUi_1.ExportJson");
	       ui->setPosition(Vec2(0, 0));
	       ui->setTouchEnabled(true);

	//获取UI资源
	Button* leftBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Left");
	Button* rightBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Right");
	Button* taskBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Task");
	Button* homeBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Home");
	Button* playBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Play");
	Button* friendsBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Friends");
	Button* bagBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Bag");
	Button* settingBtn = (Button*)Helper::seekWidgetByName(ui, "Button_Setting");
	Button* ABtn = (Button*)Helper::seekWidgetByName(ui, "Button_A");
	Button* BBtn = (Button*)Helper::seekWidgetByName(ui, "Button_B");

	//添加按钮回调事件
	leftBtn->addTouchEventListener(this, toucheventselector(SelectLayer::moveToLeft));
	rightBtn->addTouchEventListener(this, toucheventselector(SelectLayer::moveToRight));
	taskBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callAeranaScene));
	homeBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callHomeScene));
	playBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callPlayScene));
	friendsBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callFriendsScene));
	bagBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callBagScene));
	settingBtn->addTouchEventListener(this, toucheventselector(SelectLayer::callSettingScene));
	ABtn->addTouchEventListener(this, toucheventselector(SelectLayer::useAButton));
	BBtn->addTouchEventListener(this, toucheventselector(SelectLayer::useBButton));
	this->addChild(ui, 3);

	m_sp = Sprite::create("YIN/YIN (7).png", Rect(0, 0, 68, 74));
	m_sp->setPosition(Vec2(m_earth->getPosition().x, m_earth->getPosition().y + m_earth->getContentSize().height / 2));
	this->addChild(m_sp, 5);
}

//向左移动
void SelectLayer::moveToLeft(Ref* sender, TouchEventType type)
{
	//逆时针10度
	auto rotoby = RotateBy::create(1, Vec3(0, 0, -10));

	switch (type)
	{
	    case TOUCH_EVENT_BEGAN:
			    m_sp->runAction(AnimoTool::newTypeOneLeftMoveAnimotion());
		        m_earth->runAction(rotoby);
			    break;
	    case TOUCH_EVENT_ENDED:
		        break;
	}
}

//向右移动
void SelectLayer::moveToRight(Ref* sender, TouchEventType type)
{
	//正时针10度
	auto rotoby = RotateBy::create(1, Vec3(0, 0, 10));

	switch (type)
	{
	    case TOUCH_EVENT_BEGAN:
			    m_sp->runAction(AnimoTool::newTypeOneLeftMoveAnimotion());
		        m_earth->runAction(rotoby);
		        break;
	    case TOUCH_EVENT_ENDED:
		        break;
	}
}

void SelectLayer::useAButton(Ref* sender, TouchEventType type)
{
	//正时针5圈
	auto rotoby = RotateBy::create(10, Vec3(0, 0, 360 * 5));

	switch (type)
	{
	    case TOUCH_EVENT_ENDED:
		        m_earth->runAction(rotoby);
		        break;
	}
}

void SelectLayer::useBButton(Ref* sender, TouchEventType type)
{
	//逆时针5圈
	auto rotoby = RotateBy::create(10, Vec3(0, 0, -360 * 5));

	switch (type)
	{
	    case TOUCH_EVENT_ENDED:
		        m_earth->runAction(rotoby);
		        break;
	}
}

//游戏主场景的回调
void SelectLayer::callGameScene(Ref* pSender)
{
	//auto scene = MainSence::createScene(1);
	//auto scene = MainSence::createScene(3);
	auto scene = MainSence::createScene(4);
	auto layer = scene->getChildByTag(1);
	MainSence* curlayer = (MainSence*)layer;
	curlayer->setOriScene(scene);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));
}

//竞技场回调
void SelectLayer::callAeranaScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:
		        Director::getInstance()->replaceScene(TransitionFade::create(2.0f, AeranaScene::createScene()));
		        break;
	}
}

//生产单元回调
void SelectLayer::callHomeScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:
		        Director::getInstance()->pushScene(TransitionFade::create(2.0f, HomeScene::createScene()));
		        break;
	}
}

//背包回调
void SelectLayer::callBagScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:

		     	//遍历Game类的所有子节点信息，画入renderTexture中。（这里类似截图）。
			    CCRenderTexture *renderTexture = CCRenderTexture::create(1200, 640);
			    renderTexture->begin();
			    this->getParent()->visit();
			    renderTexture->end();

			    //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
			    CCDirector::sharedDirector()->pushScene(GamePause::createScene(renderTexture, 2));
			break;
	}
}

//设置回调
void SelectLayer::callSettingScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:

		     	//遍历Game类的所有子节点信息，画入renderTexture中。（这里类似截图）。
			    CCRenderTexture *renderTexture = CCRenderTexture::create(1200, 640);
			    renderTexture->begin();
			    this->getParent()->visit();
			    renderTexture->end();

			    //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
			    CCDirector::sharedDirector()->pushScene(GamePause::createScene(renderTexture, 0));
		        break;
	}
}


void SelectLayer::callPlayScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:
				auto scene = MainSence::createScene(2);
				auto layer = scene->getChildByTag(1);
				MainSence* curlayer = (MainSence*)layer;
				curlayer->setOriScene(scene);
			    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));
		        break;
	}
}

//拍卖行回调
void SelectLayer::callFriendsScene(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	    case TOUCH_EVENT_ENDED:

			    //遍历Game类的所有子节点信息，画入renderTexture中。（这里类似截图）。
				//CCRenderTexture *renderTexture = CCRenderTexture::create(1200, 640);
				//renderTexture->begin();
				//this->getParent()->visit();
				//renderTexture->end();

				//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
				//CCDirector::sharedDirector()->pushScene(GamePause::createScene(renderTexture, 3));
			    auto sc_sence = ScrollBarTest::create();
				CCDirector::sharedDirector()->pushScene(sc_sence);
				break;
	}
}