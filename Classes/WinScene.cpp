#include "WinScene.h"
#include "SelectLayer.h"
#include "SimpleAudioEngine.h"

Scene* WinScene::createScene() 
{
    auto scene = Scene::create();

    WinScene* layer = WinScene::create();
    scene->addChild(layer);

    return scene;
}

bool WinScene::init()
{
    if (!Layer::init())
	{
        return false;
	}

	//停止界面所有动作
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//添加一个标签
	auto winLab = Label::create("You Win!", "Aria", 35);
	        winLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winLab);

	// 3秒后返回关卡选择场景
	this->schedule(schedule_selector(WinScene::backToTollgateSelectScene), 3.0f);

    return true;
}

//回调函数 切换到选择界面
void WinScene::backToTollgateSelectScene( float dt )
{
	Director::getInstance()->replaceScene(SelectLayer::createScene());
}
