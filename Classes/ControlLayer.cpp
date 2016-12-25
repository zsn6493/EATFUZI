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

const int MAX_BLOOD_NUM = 3;

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
	m_LongTouchLabel = nullptr;
	m_Target = nullptr;
	m_LabelCount = 1;
	m_MonsterBloodNum = 0;
}

ControlLayer::~ControlLayer()
{
	NOTIFY->removeAllObservers(this);
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

	m_LongTouchLabel = Node::create();
	m_LongTouchLabel->setPosition(Vec2(0, 0));
	this->addChild(m_LongTouchLabel);

	//�������������/*��Ҫ�Ż�*/
	SpecialProgress(m_LongTouchLabel);

	Vec2 originPt = this->m_viewLayer->getPlayerManager()->getOriginPoint();

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

	powerUp->setPosition(Vec2(originPt.x - 25,
		originPt.y));

	auto powerUpMenu = Menu::create(powerUp, NULL);
	powerUpMenu->setPosition(Vec2::ZERO);
	this->addChild(powerUpMenu, 1);

	//zombie������ť
	auto peoUp = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ControlLayer::usePeoUp, this));

	peoUp->setPosition(Vec2(originPt.x + 75,
		originPt.y));

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

	//�����л�ʧ�ܳ���
	NOTIFY->addObserver(this,
		callfuncO_selector(ControlLayer::activeMonster),
		"ACMonster",
		NULL);

	return true;
}

void ControlLayer::SpecialProgress(Node* node)
{
	for (int i = 1; i <= 5; i++)
	{
		switch (i)
		{
		case 1:
		{
				  Sprite* sp = Sprite::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
				  sp->setPosition(Vec2(100, 500));
				  m_LongTouchLabel->addChild(sp);
				  sp->setColor(Color3B(0, 255, 255));
				  sp->setTag(i);
				  sp->setVisible(false);
				  break;
		}
		case 2:
		{
				  Sprite* sp = Sprite::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
				  sp->setPosition(Vec2(100 + 57 / 2 * (i - 1), 500));
				  m_LongTouchLabel->addChild(sp);
				  sp->setColor(Color3B(75, 0, 130));
				  sp->setVisible(false);
				  sp->setTag(i);
				  break;
		}
		case 3:
		{
				  Sprite* sp = Sprite::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
				  sp->setPosition(Vec2(100 + 57 / 2 * (i - 1), 500));
				  m_LongTouchLabel->addChild(sp);
				  sp->setColor(Color3B(255, 215, 0));
				  sp->setVisible(false);
				  sp->setTag(i);
				  break;
		}
		case 4:
		{
				  Sprite* sp = Sprite::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
				  sp->setPosition(Vec2(100 + 57 / 2 * (i - 1), 500));
				  m_LongTouchLabel->addChild(sp);
				  sp->setColor(Color3B(218, 165, 32));
				  sp->setVisible(false);
				  sp->setTag(i);
				  break;
		}
		case 5:
		{
				  Sprite* sp = Sprite::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
				  sp->setPosition(Vec2(100 + 57 / 2 * (i - 1), 500));
				  m_LongTouchLabel->addChild(sp);
				  sp->setColor(Color3B(255, 0, 0));
				  sp->setVisible(false);
				  sp->setTag(i);
				  break;
		}
		default:
			break;
		}
	}
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

	m_pProgressView = new ProgressView();
	m_pProgressView->setPosition(Vec2(visibleSize.width - 300, origin.y + visibleSize.height - 30));
	m_pProgressView->setScaleY(3.5f);
	m_pProgressView->setScaleX(4.0f);
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

		m_startPoint = touch->getLocation();

		isTouch = true;

		m_startTime = getCurrentTime();

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
			m_Target->setPosition(touch->getLocation());
		}
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
		if (m_longProgress)
		{
			touchCounts = 0;
			m_longProgress = false;
			m_viewLayer->useLongPower(location);
			return;
		}

		m_endPoint = touch->getLocation();
		long long endTime = getCurrentTime();
		long long timeDis = endTime - m_startTime;

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
			//this->scheduleOnce(schedule_selector(ControlLayer::updateDoubleDelay), 0.25);
			//touchCounts++;
		}
		else if (touchCounts == 0)
		{
			this->scheduleOnce(schedule_selector(ControlLayer::updateSingleDelay), 0.15);
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
	m_viewLayer->useZombie(m_LabelCount);
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

	m_viewLayer->setcharType(m_viewLayer->getcharType() + 1);
	NOTIFY->postNotification("DeNum", (Ref*)&s);

	if (m_LabelCount <= 5)
	{
		m_LongTouchLabel->getChildByTag(m_LabelCount)->setVisible(true);
	}

	++m_LabelCount;
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
		m_viewLayer->useSinglePower(m_startPoint);
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
	if (isTouch)
	{
		pressTimes++;

		if (pressTimes >= 2)
		{
			m_longProgress = true;
			m_Target->setVisible(true);
			//onLongPressed();
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

void ControlLayer::activeMonster(Ref* pData)
{
	static int i = 0;
	int data = *(int*)pData;
	m_viewLayer->setMonsterType(data);

	if (m_LabelCount <= 5)
	{
		m_LongTouchLabel->getChildByTag(m_LabelCount)->setVisible(true);
	}
	++m_LabelCount;
}

void ControlLayer::loseBlood(Ref* pData)
{
	int currentData = m_pProgressView->getCurrentProgress() - *(int*)pData;
	if (currentData <= 0)
	{
		m_pProgressView->setForegroundTexture("bloodBar/hr_slider.png");
		m_pProgressView->getProgressForeground()->setColor(Color3B(100, 100, 100));
		m_pProgressView->setCurrentProgress(100.0f);
		++m_MonsterBloodNum;
		if (m_MonsterBloodNum >= MAX_BLOOD_NUM)
		{
			m_viewLayer->retBeginLayer();
		}
		return;
	}
	m_pProgressView->setCurrentProgress(currentData);
}