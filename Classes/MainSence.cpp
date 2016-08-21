#include "MainSence.h"
#include "ControlLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define NOTIFY cocos2d::NotificationCenter::getInstance()

Scene* MainSence::createScene(int level)
{
	//创建一个物理场景。
	auto scene = Scene::createWithPhysics();
	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vect(0, -2000));
	world->setAutoStep(false);

	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//创建展示层
	auto showlayer = ShowLayer::create(level);
	scene->addChild(showlayer, 2);
	showlayer->setWorld(world);

	//创建控制层
	auto controlLayer = ControlLayer::create(showlayer);
	scene->addChild(controlLayer, 3);

	//背景层
	auto bgLayer_LV = MainSence::create(level, showlayer);
	scene->addChild(bgLayer_LV, 1);
	bgLayer_LV->setTag(1);

	//返回场景
	return scene;
}

void MainSence::OnEnter()
{
}

MainSence::MainSence()
{
	m_Num = 0;
	m_BK = nullptr;
}

MainSence::~MainSence()
{
	NOTIFY->removeAllObservers(this);
}

MainSence* MainSence::create(int level, ShowLayer* showLayer)
{
	MainSence *pobMain = new MainSence();
	if (pobMain && pobMain->init(level, showLayer))
	{
		pobMain->autorelease();
		return pobMain;
	}
	CC_SAFE_DELETE(pobMain);
	return NULL;
}

bool MainSence::init(int level, ShowLayer* showLayer)
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	scheduleUpdate();

	m_viewLayer = showLayer;

	m_Label = Label::createWithTTF(StringUtils::format("%d", m_Num), "fonts/Marker Felt.ttf", 52);
	m_Label->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(m_Label, 2);

	m_BK = Layer::create();
	this->addChild(m_BK, 1);

	if (level == 3)
	{
		//背景图片
		auto bg = Sprite::create("bk_boat.png");
		bg->setAnchorPoint(Vec2(0.0f, 0.0f));
		m_BK->addChild(bg, 1);
		bg->setTag(4);
	}

	//订阅切换胜利场景
	NOTIFY->addObserver(this,
		callfuncO_selector(MainSence::killedMonsterNum),
		"KillMonsterNum",
		NULL);

	//订阅切换失败场景
	NOTIFY->addObserver(this,
		callfuncO_selector(MainSence::recvGameOver),
		"GameOver",
		NULL);

	//订阅切换失败场景
	NOTIFY->addObserver(this,
		callfuncO_selector(MainSence::recvChangeBK),
		"ChangeBK",
		NULL);

	//订阅切换失败场景
	NOTIFY->addObserver(this,
		callfuncO_selector(MainSence::deNum),
		"DeNum",
		NULL);

	return true;
}
void MainSence::deNum(Ref* pData)
{
	int* s = (int*)pData;
	if ((m_Num - (*s)) < 0)
	{
		return;
	}
	m_Num -= *s;
	m_Label->setString(StringUtils::format("%d", m_Num));
	//Director::getInstance()->replaceScene(TransitionFade::create(2.0f, WinScene::createScene()));
}

void MainSence::killedMonsterNum(Ref* pData)
{
	m_Num++;
	m_Label->setString(StringUtils::format("%d", m_Num));
	//Director::getInstance()->replaceScene(TransitionFade::create(2.0f, WinScene::createScene()));
}

void MainSence::recvGameOver(Ref* pData)
{
	auto child = m_BK->getChildByTag(4);

	auto fadeout = FadeOut::create(3);

	auto Func = [&]()
	{
		auto sp = Sprite::create("bk_boat.png");
		sp->setAnchorPoint(Vec2(0.0f, 0.0f));
		auto fadein = FadeIn::create(3);
		m_BK->addChild(sp, 2);
		auto fadeout = FadeOut::create(0.1);
		sp->runAction(Sequence::create(fadeout, fadein, NULL));
	};

	auto callback = CallFunc::create(Func);
	child->runAction(Sequence::create(fadeout, callback, NULL));

	//Director::getInstance()->replaceScene(TransitionFade::create(2.0f, GameOverScene::createScene()));
	//auto blink = Blink::create(1, 1);
}

void MainSence::recvChangeBK(Ref* pData)
{
	/*
	//从输入端level控制背景技能效果
	if (m_BK != NULL && m_BK->getChildrenCount() == 0)
	{
	int level = (int)pData;
	Sprite* sp = nullptr;

	auto Func = [&]()
	{
	m_BK->removeAllChildren();
	};

	if (level == 3)
	{
	sp = Sprite::create("bk_sun.png");
	}

	sp->setAnchorPoint(Vec2(0, 0));
	m_BK->addChild(sp, 2);

	auto callback = CallFunc::create(Func);
	auto blink = Blink::create(1, 1);
	auto fadeout = FadeOut::create(2);

	sp->runAction(Sequence::create(blink, fadeout, callback, NULL));
	}*/
}

/*设置背景以人物为中心按比例运动*/
void MainSence::setViewPoint()
{
	//屏幕宽度
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(m_viewLayer->getPositionX() * -1, winSize.width / 2);
	//int y = MAX(position.y, winSize.height / 2);
	//x = MIN(x, (m_map->getMapSize().width * m_map->getTileSize().width) - winSize.width / 2);
	x = MIN(x, 9600 - winSize.width / 2);
	//y = MIN(y, (tm->getMapSize().height * tm->getTileSize().height) - winSize.height / 2);

	auto actualPosition = Point(x, 0);
	auto centerOfView = Point(winSize.width / 2, 0);
	auto viewPoint = centerOfView - actualPosition;
	viewPoint.x /= 16;
	m_moveLayer->setPosition(viewPoint);
}

void MainSence::logic(float dt)
{
	setViewPoint();
}

void MainSence::update(float dt)
{
	getOriScene()->getPhysicsWorld()->step(0.02f);
}