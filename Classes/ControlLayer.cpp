#include "AnimoTool.h"
#include "ControlLayer.h"
#include "PhysicsWorld.h"
#include "PlayerPower.h"
#include "MainSence.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

#define NOTIFY cocos2d::NotificationCenter::getInstance()

bool isTouch = false;

bool isMoved = false;

int pressTimes = 0;

int touchCounts = 0;

Scene* ControlLayer::createScene()
{
	//����������
	auto scene = Scene::createWithPhysics();

	return scene;
}

ControlLayer::ControlLayer()
{
	m_flag = 0;
	m_longProgress = false;
}

ControlLayer::~ControlLayer()
{
}

ControlLayer* ControlLayer::create(Layer* layer)
{
	ControlLayer *cLayer = new ControlLayer();
	if (cLayer && cLayer->init(layer))
	{
		cLayer->autorelease();
		return cLayer;
	}
	CC_SAFE_DELETE(cLayer);

	return NULL;
}

bool ControlLayer::init(Layer* layer)
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	this->m_viewLayer = (ShowLayer*)layer;        //����viewͼ��

	setTouchEnabled(true);                                  //��������

	scheduleUpdate();                                         //�߳̿���

	loadConfig();                                                 //������Դ

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʱ����һ������ѡ�����İ�ť
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ControlLayer::gameOverCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		50));

	auto Menu = Menu::create(closeItem, NULL);
	Menu->setPosition(Vec2::ZERO);
	this->addChild(Menu, 1);

	//�ٻ�zombie��ť
	auto power1 = MenuItemImage::create(
		"Power5.png",
		"Power5.png",
		CC_CALLBACK_1(ControlLayer::usePower1, this));

	power1->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 2,
		50));

	auto powerMenu = Menu::create(power1, NULL);
	powerMenu->setPosition(Vec2::ZERO);
	this->addChild(powerMenu, 1);

	//����������ť
	auto powerUp = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ControlLayer::usePowerUp, this));

	powerUp->setPosition(Vec2(origin.x + closeItem->getContentSize().width,
		200));

	auto powerUpMenu = Menu::create(powerUp, NULL);
	powerUpMenu->setPosition(Vec2::ZERO);
	this->addChild(powerUpMenu, 1);

	//zombie������ť
	auto peoUp = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ControlLayer::usePeoUp, this));

	peoUp->setPosition(Vec2(origin.x + closeItem->getContentSize().width,
		100));

	auto peoUpMenu = Menu::create(peoUp, NULL);
	peoUpMenu->setPosition(Vec2::ZERO);
	this->addChild(peoUpMenu, 1);

	m_Target = Sprite::create("CloseNormal.png");
	m_Target->setScale(5.0f);
	m_Target->setVisible(false);
	this->addChild(m_Target);

	//�����л�ʧ�ܳ���
	NOTIFY->addObserver(this,
		callfuncO_selector(ControlLayer::loseBlood),
		"LOSEBLOOD",
		NULL);

	return true;
}

//��ʼ��������Դ
void ControlLayer::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�������״̬UI��Ѫ����ħ��ֵ��
	//auto _rootNode = CSLoader::createNode("PlayerStats.csb");
	//_rootNode->setPosition(Vec2(origin.x, origin.y + 120));
	//_rootNode->setScale(0.5f);

	//this->addChild(_rootNode, 2);

	//��ʼ��ProgressView

	m_pProgressView = new ProgressView;
	m_pProgressView->setPosition(Vec2(visibleSize.width - 350, origin.y + visibleSize.height - 30));
	m_pProgressView->setScaleY(3.5f);
	m_pProgressView->setScaleX(5.0f);
	m_pProgressView->setBackgroundTexture("bloodBar/hr_slider_bg.png");
	m_pProgressView->setForegroundTexture("bloodBar/hr_slider.png");
	m_pProgressView->setTotalProgress(100.0f);
	m_pProgressView->setCurrentProgress(100.0f);
	this->addChild(m_pProgressView, 2);
}

//�����ƶ��¼���Ҳ������ָ����Ļ�����ʼ�Ĺ���
void ControlLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (auto &touch : touches)
	{
		//ʹ�ü���
		auto location = touch->getLocation();
		//m_viewLayer->useFZPower(location);

		m_startPoint = touch->getLocation();

		isTouch = true;

		m_startTime = getCurrentTime();

		//m_Target->setVisible(true);
		m_Target->setPosition(touch->getLocation());
		//�������¼�
		this->schedule(schedule_selector(ControlLayer::updatelongprogress), 0.5);
	}
}

//�����ƶ��¼���Ҳ������ָ����Ļ�����Ĺ���
void ControlLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (auto &touch : touches)
	{
		if (m_longProgress)
		{
			//m_Target->setVisible(true);
			m_Target->setPosition(touch->getLocation());
		}
		//m_viewLayer->removeJoint();
		/*
		m_Count++;
		if (m_Count % 10 == 0)
		{
		auto location = touch->getLocation();
		m_viewLayer->useFZPower(location);

		m_Count = 1;
		}*/
	}
}

//�����¼�������Ҳ������ָ�ɿ�ʱ
void ControlLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (auto &touch : touches)
	{
		auto location = touch->getLocation();
		m_Target->setVisible(false);
		isTouch = false;
		pressTimes = 0;
		this->unschedule(schedule_selector(ControlLayer::updatelongprogress));

		//�������ɳ����¼� ��Ѱ��´������� ����״̬�ÿ� ֱ�ӷ��� ������ִ��
		if (m_longProgress) {
			touchCounts = 0;
			m_longProgress = false;

			Sprite* sp = Sprite::create("CloseNormal.png");
			sp->setPosition(100, 400);
			auto mb = MoveTo::create(0.5, location);
			sp->runAction(mb);
			m_viewLayer->addChild(sp);
			return;
		}

		m_endPoint = touch->getLocation();

		long long endTime = getCurrentTime();

		long long timeDis = endTime - m_startTime;

		//E_SWIP_DIR dir = GetSwipDir(m_startPoint, m_endPoint, timeDis);

		//if (dir != E_INVAILD) {
		//onSwip(m_startPoint, m_endPoint, dir);
		//return;
		//}

		//�������ж�
		if (isMoved)
		{
			isMoved = false;
			return;
		}

		if (touchCounts == 2)
		{
			//onThreeClick();
			touchCounts = 0;
		}
		else if (touchCounts == 1)
		{
			this->scheduleOnce(schedule_selector(ControlLayer::updateDoubleDelay), 0.25);
			touchCounts++;
		}
		else if (touchCounts == 0)
		{
			this->scheduleOnce(schedule_selector(ControlLayer::updateSingleDelay), 0.25);
			touchCounts++;
		}
	}
}

//��ʱ���ӷ���ѡ��������
void ControlLayer::gameOverCallback(Ref* pSender)
{
	m_viewLayer->retBeginLayer();
}

//ʹ�ü���
void ControlLayer::usePower1(Ref* pSender)
{
	m_viewLayer->useZombie(1);
}

void ControlLayer::usePowerUp(Ref* pSender)
{
	int s = 10;

	auto layer = (MainSence*)this->getParent()->getChildByTag(1);
	int num = layer->getKillMonsterNum();
	if ((num - 10) < 0)
	{
		return;
	}

	if (!m_viewLayer->getFirePower())
	{
		m_viewLayer->setFirePower(true);
	}

	NOTIFY->postNotification("DeNum", (Ref*)&s);
}

void ControlLayer::usePeoUp(Ref* pSender)
{
	int s = 3;

	auto layer = (MainSence*)this->getParent()->getChildByTag(1);
	int num = layer->getKillMonsterNum();
	if ((num - 3) < 0)
	{
		return;
	}

	m_viewLayer->setRand(m_viewLayer->getRand() + 1);
	NOTIFY->postNotification("DeNum", (Ref*)&s);
}

//update function
void ControlLayer::update(float delta)
{
	//�����Ϊ����
	Point viewPoint = m_viewLayer->setViewPoint();
	m_viewLayer->setPosition(viewPoint);
}

void ControlLayer::updateSingleDelay(float ft)
{
	if (touchCounts == 1)
	{
		//onSingleCLick();
		m_viewLayer->useFZPower(m_startPoint);
		touchCounts = 0;
	}
}

void ControlLayer::updateDoubleDelay(float ft)
{
	if (touchCounts == 2)
	{
		//onDoubleClick();
		touchCounts = 0;
	}
}

void ControlLayer::updatelongprogress(float ft)
{
	if (isTouch) {
		pressTimes++;

		if (pressTimes >= 2) {
			m_longProgress = true;

			m_Target->setVisible(true);
			//onLongPressed();
			//m_viewLayer->removeJoint();
		}
	}
	else
	{
		pressTimes = 0;
	}
}

long long ControlLayer::getCurrentTime()
{
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return (long long)(tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void ControlLayer::loseBlood(Ref* pData)
{
	int loseBlood = *(int*)pData;
	int currValue = m_pProgressView->getCurrentProgress();
	if (currValue <= loseBlood)
	{
		m_pProgressView->getProgressForeground()->setColor(Color3B(200, 100, 100));
		m_pProgressView->setCurrentProgress(100);
		return;
	}
	m_pProgressView->setCurrentProgress(currValue - loseBlood);
}