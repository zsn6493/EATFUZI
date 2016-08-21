#include "GameOverScene.h"
#include "SelectLayer.h"
#include "SimpleAudioEngine.h"

Scene* GameOverScene::createScene() 
{
    auto scene = Scene::create();

    GameOverScene* layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;

    return scene;
}

bool GameOverScene::init() 
{
    if (!Layer::init()){
        return false;
    }

	//停止背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* 添加一个标签 */
    Label* winLab = Label::create("GameOver!", "Aria", 35);
    winLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(winLab);

    /* 3秒后返回关卡选择场景 */
    this->schedule(schedule_selector(GameOverScene::backToTollgateSelectScene), 3.0f);

    return true;
}

void GameOverScene::backToTollgateSelectScene( float dt ) 
{
	Director::getInstance()->replaceScene(SelectLayer::createScene());
}
