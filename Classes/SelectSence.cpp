#include "SelectSence.h"
#include "MainSence.h"
#include "ui/UIVideoPlayer.h"
#include "AnimoTool.h"
#include "extensions\cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_MATH;

SelectSence::SelectSence()
{
	speed = 2;
	m_Sp = nullptr;
	m_ColorLayer = nullptr;
	DirX = 0;
	DirY = 0;
	m_Touch = false;
}

SelectSence::~SelectSence()
{
}

Scene* SelectSence::createScene()
{
	//��������
	auto scene = Scene::create();

	//������
	auto layer = SelectSence::create();
	scene->addChild(layer);

	return scene;
}

bool SelectSence::init()
{
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	setTouchEnabled(true);                                  //��������
	scheduleUpdate();                                          //update����

	//������Դ������manager
	loadConfig();

	return true;
}

/*������Դ*/
void SelectSence::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��һĻ��ť
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SelectSence::nextSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3));

	// create menu, it's an autorelease object
	m_menu = Menu::create(closeItem, NULL);
	m_menu->setPosition(Vec2::ZERO);
	m_menu->setVisible(false);
	this->addChild(m_menu, 2);

	m_ColorLayer = LayerColor::create(Color4B(128, 128, 128, 100), 5000, 5000);
	m_ColorLayer->setPosition(Vec2(0, 0));
	m_ColorLayer->setContentSize(Size(5000, 5000));
	m_ColorLayer->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_ColorLayer, 1);

	//����һ���հ�sprite
	Size contentSize = m_ColorLayer->getContentSize();
	m_Sp = Sprite::create(NEWTYPE_ONE, NEWTYPE_ONE_RECT);
	m_Sp->setPosition(2500, 2500);
	m_Sp->setAnchorPoint(Vec2(0.5, 0.5));
	m_ColorLayer->addChild(m_Sp, 2);

	auto sp = Sprite::create(NEWTYPE_ONE, NEWTYPE_ONE_RECT);
	sp->setPosition(2500 - 200, 2500);
	sp->setColor(Color3B(100, 100, 100));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	m_ColorLayer->addChild(sp, 2);
}

void SelectSence::nextSceneCallback(Ref* pSender)
{
	//auto scene = MainSence::createScene(3);
	//auto layer = scene->getChildByTag(1);
	//MainSence* curlayer = (MainSence*)layer;
	//curlayer->setOriScene(scene);
	//Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));
}

//�����ƶ��¼���Ҳ������ָ����Ļ�����ʼ�Ĺ���
void SelectSence::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	m_Touch = true;

	for (auto &touch : touches)
	{
		//(touch->getLocation().x - m_ColorLayer->getPositionX() - m_Sp->getPositionX() > 0) ? DirX = 1 : DirX = -1;
		//(touch->getLocation().y - m_ColorLayer->getPositionY() - m_Sp->getPositionY() > 0) ? DirY = 1 : DirY = -1;

		//m_Sp->setPosition(m_Sp->getPosition().x + speedX, m_Sp->getPosition().y + speedY);
	}
}

//�����ƶ��¼���Ҳ������ָ����Ļ�����Ĺ���
void SelectSence::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	m_Touch = true;

	for (auto &touch : touches)
	{
		int speedX = 0;
		int speedY = 0;

		(touch->getLocation().x - m_ColorLayer->getPositionX() - m_Sp->getPositionX() > 0) ? speedX = speed : speedX = -speed;
		(touch->getLocation().y - m_ColorLayer->getPositionY() - m_Sp->getPositionY() > 0) ? speedY = speed : speedY = -speed;

		m_Sp->setPosition(m_Sp->getPosition().x + speedX, m_Sp->getPosition().y + speedY);
	}
}

//�����¼�������Ҳ������ָ�ɿ�ʱ
void SelectSence::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	m_Touch = false;
	for (auto &touch : touches)
	{
		(touch->getLocation().x - m_ColorLayer->getPositionX() - m_Sp->getPositionX() > 0) ? DirX = 1 : DirX = -1;
		(touch->getLocation().y - m_ColorLayer->getPositionY() - m_Sp->getPositionY() > 0) ? DirY = 1 : DirY = -1;
	}
}

/*����playerΪ����*/
Vec2 SelectSence::setViewPoint()
{
	//��Ļ���
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(m_Sp->getPositionX(), 2500 - winSize.width / 2);
	x = MIN(x, 5000 - winSize.width / 2);

	int y = MAX(m_Sp->getPositionY(), 2500 - winSize.height / 2);
	y = MIN(y, 5000 - winSize.height / 2);

	//auto actualPosition = Point(x, y);
	auto actualPosition = Vec2(x, y);

	//Ҫ���õ������ĵ�λ�ã���λ����layer ��scene�ϵ�λ��
	auto centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;

	return viewPoint;
}

//update function
void SelectSence::update(float delta)
{
	//�����Ϊ����
	Vec2 viewPoint = setViewPoint();
	m_ColorLayer->setPosition(viewPoint);

	if (!m_Touch)
	{
		m_Sp->setPosition(m_Sp->getPosition().x + speed * DirX, m_Sp->getPosition().y + speed * DirY);
	}
}