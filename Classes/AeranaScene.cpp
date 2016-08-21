#include "AeranaScene.h"
#include "SelectLayer.h"
#include "MainSence.h"

Scene* AeranaScene::createScene()
{
	auto scene = Scene::create();

	AeranaScene* layer = AeranaScene::create();
	scene->addChild(layer);

	return scene;
}

bool AeranaScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 添加一个标签 */
	Label* winLab = Label::create("Doing Connecting!", "Aria", 35);
	winLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winLab);

	/* 3秒后返回关卡选择场景 */
	this->schedule(schedule_selector(AeranaScene::backToTollgateSelectScene), 3.0f);

	return true;
}

void AeranaScene::loadConfig()
{
}

void AeranaScene::backToTollgateSelectScene(float dt)
{
	auto scene = MainSence::createScene(0);
	auto layer = scene->getChildByTag(1);
	MainSence* curlayer = (MainSence*)layer;
	curlayer->setOriScene(scene);
	Director::getInstance()->replaceScene(scene);
}