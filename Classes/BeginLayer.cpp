#include "BeginLayer.h"
#include "MainSence.h"
#include "ui/UIVideoPlayer.h"
#include "AnimoTool.h"
#include "HomeScene.h"
#include "SelectSence.h"

Scene* BeginLayer::createScene()
{
	//创建场景
	auto scene = Scene::create();

	//创建层
	auto layer = BeginLayer::create();
	scene->addChild(layer);

	return scene;
}

bool BeginLayer::init()
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
void BeginLayer::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//下一幕按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BeginLayer::nextSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3));

	// create menu, it's an autorelease object
	m_menu = Menu::create(closeItem, NULL);
	m_menu->setPosition(Vec2::ZERO);
	m_menu->setVisible(false);
	this->addChild(m_menu, 2);

	//创建一个空白sprite
	auto sp = Sprite::create();
	sp->setAnchorPoint(Vec2(0, 0));
	this->addChild(sp, 1);

	//播放动画
	auto callbackFunc = [&]()
	{
		m_menu->setVisible(true);
	};

	CallFunc* callFunc = CallFunc::create(callbackFunc);
	auto action = AnimoTool::createBeginAnimotion();
	//sp->runAction(Sequence::create(action, callFunc, NULL));
	sp->runAction(Sequence::create(callFunc, NULL));
}

void BeginLayer::nextSceneCallback(Ref* pSender)
{
	auto scene = SelectSence::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));
	/*auto scene = MainSence::createScene(3);
	auto layer = scene->getChildByTag(1);
	MainSence* curlayer = (MainSence*)layer;
	curlayer->setOriScene(scene);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));*/
}