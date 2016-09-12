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
	auto backGrandLayer = MainSence::create(level);
	scene->addChild(backGrandLayer, 1);
	backGrandLayer->setTag(1);

	//返回场景
	return scene;
}

void MainSence::OnEnter()
{
}

MainSence::MainSence()
{
	m_KillMonsterNum = 0;
	m_BackGrandLayer = nullptr;
}

MainSence::~MainSence()
{
	NOTIFY->removeAllObservers(this);
}

MainSence* MainSence::create(int level)
{
	MainSence *mainSence = new MainSence();
	if (mainSence && mainSence->init(level))
	{
		mainSence->autorelease();
		return mainSence;
	}
	CC_SAFE_DELETE(mainSence);
	return NULL;
}

bool MainSence::init(int level)
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	//update func
	scheduleUpdate();

	//backgrand layer
	m_BackGrandLayer = Layer::create();
	this->addChild(m_BackGrandLayer);

	auto winSize = Director::getInstance()->getWinSize();
	m_Label = Label::createWithTTF(StringUtils::format("%d", m_KillMonsterNum), "fonts/Marker Felt.ttf", 52);
	m_Label->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	m_BackGrandLayer->addChild(m_Label, 2);

	//select backGrand
	switch (level)
	{
	case 1:
	case 2:
	case 3:
	{
			  //背景图片
			  auto bg = Sprite::create("bk_boat.png");
			  bg->setAnchorPoint(Vec2(0.0f, 0.0f));
			  m_BackGrandLayer->addChild(bg, 1);
			  bg->setTag(3);
	}
		break;
	default:
		break;
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
	int usedFeeNum = *(int*)pData;
	if ((m_KillMonsterNum - usedFeeNum) < 0)
	{
		return;
	}

	m_KillMonsterNum -= usedFeeNum;
	m_Label->setString(StringUtils::format("%d", m_KillMonsterNum));
}

void MainSence::killedMonsterNum(Ref* pData)
{
	++m_KillMonsterNum;
	m_Label->setString(StringUtils::format("%d", m_KillMonsterNum));
}

void MainSence::recvGameOver(Ref* pData)
{
	auto child = m_BackGrandLayer->getChildByTag(3);

	auto fadeout = FadeOut::create(3);
	auto Func = [&]()
	{
		auto sp = Sprite::create("bk_boat.png");
		sp->setAnchorPoint(Vec2(0.0f, 0.0f));
		auto fadein = FadeIn::create(3);
		m_BackGrandLayer->addChild(sp, 2);
		auto fadeout = FadeOut::create(0.1);
		sp->runAction(Sequence::create(fadeout, fadein, NULL));
	};
	auto callback = CallFunc::create(Func);
	child->runAction(Sequence::create(fadeout, callback, NULL));
}

void MainSence::recvChangeBK(Ref* pData)
{
}

void MainSence::update(float dt)
{
	getOriScene()->getPhysicsWorld()->step(0.02f);
}