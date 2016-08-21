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

	//ֹͣ�������ж���
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���һ����ǩ
	auto winLab = Label::create("You Win!", "Aria", 35);
	        winLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winLab);

	// 3��󷵻عؿ�ѡ�񳡾�
	this->schedule(schedule_selector(WinScene::backToTollgateSelectScene), 3.0f);

    return true;
}

//�ص����� �л���ѡ�����
void WinScene::backToTollgateSelectScene( float dt )
{
	Director::getInstance()->replaceScene(SelectLayer::createScene());
}
