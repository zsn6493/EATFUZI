#include "ShowLayer.h"
#include "PhysicsWorld.h"
#include "SimpleAudioEngine.h"
#include "BeginLayer.h"

ShowLayer::ShowLayer()
{
	m_PlayerManager = NULL;
	m_MonsterManager = NULL;
	m_BossManager = NULL;

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/dls.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/dls1.wav");

	for (int i = 1; i <= 6; i++)
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(StringUtils::format("music/m%d.wav", i).c_str());

	m_FirePower = false;
	m_Rand = 1;
}

ShowLayer::~ShowLayer()
{
}

Scene* ShowLayer::createScene()
{
	//��������
	auto scene = Scene::create();

	//������
	auto layer = ShowLayer::create();

	scene->addChild(layer);

	return scene;
}

ShowLayer* ShowLayer::create(int level)
{
	ShowLayer *cLayer = new ShowLayer();
	if (cLayer && cLayer->initShow(level))
	{
		cLayer->autorelease();
		return cLayer;
	}
	CC_SAFE_DELETE(cLayer);
	return NULL;
}

bool ShowLayer::initShow(int level)
{
	if (!Layer::init())
	{
		return false;
	}

	//������Դ������manager
	loadConfig(level);

	//����update
	scheduleUpdate();

	return true;
}

bool ShowLayer::init()
{
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	//������Դ������manager
	loadConfig();

	//����update
	scheduleUpdate();

	return true;
}

/*������Դ*/
void ShowLayer::loadConfig()
{
}

void  ShowLayer::onEnter()
{
	Layer::onEnter();
}

void randNum()
{
	struct timeval now;
	gettimeofday(&now, NULL);

	//��ʼ���������
	//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ��
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //��ת��Ϊ����
	srand(rand_seed);
}

/*������Դ*/
void ShowLayer::loadConfig(int level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Level = level;

	//��ʼ���������
	randNum();

	if (level == 3)
	{
		int rand = CCRANDOM_0_1() * 5;

		//���ص�ͼ��Դ
		m_Map = CCTMXTiledMap::create("LastMap2.tmx");

		m_MaxLength = 1600;
		m_MinLength = 0;

		//��ȡ��ͼ��player������
		TMXObjectGroup* objGoup = m_Map->getObjectGroup("playerPoint");
		ValueMap playerPointMap = objGoup->getObject("Player");

		float playerX = playerPointMap.at("x").asFloat();
		float playerY = playerPointMap.at("y").asFloat();

		//����playerManager
		m_PlayerManager = PlayerManager::createWithLevel(Vec2(playerX, playerY + 24), level);
		m_PlayerManager->setPosition(Vec2(0, 0));
		m_Map->addChild(m_PlayerManager, 3);

		//��ȡ��ͼ�Ϲ�������
		TMXObjectGroup* mobjGoup = m_Map->getObjectGroup("monsterPoint");
		ValueVector monsterPoints = mobjGoup->getObjects();

		//ValueMap monsterPoint = mobjGoup->getObject("monster1");

		//float monsterX = monsterPoint.at("x").asFloat();
		//float monsterY = monsterPoint.at("y").asFloat();

		PhyscisWorld::createWorld(m_Map, level);

		//����monsterManager
		m_MonsterManager = MonsterManager::createWithLevel(monsterPoints, level);    //change
		m_MonsterManager->setAnchorPoint(Vec2(0, 0));
		m_MonsterManager->setPosition(Vec2(0, 0));
		m_Map->addChild(m_MonsterManager, 2);

		TMXObjectGroup* bobjGoup = m_Map->getObjectGroup("Boss");
		ValueMap bossPoint = bobjGoup->getObject("boss");

		float bossPointX = bossPoint.at("x").asFloat();
		float bossPointY = bossPoint.at("y").asFloat();

		m_BossManager = BossManager::createWithLevel(Vec2(bossPointX, bossPointY), level);
		m_BossManager->setAnchorPoint(Vec2(0, 0));
		m_BossManager->setPosition(Vec2(0, 0));
		m_BossManager->setBOrigin(Vec2(bossPointX, bossPointY));
		m_Map->addChild(m_BossManager, 2);

		//m_boss->setOrigin(Vec2(bossPointX, bossPointY));
		//m_boss->setPosition(Vec2(bossPointX, bossPointY));
		//this->addChild(m_boss, 3);
		m_GodArmManager = GodArmManager::createWithLevel(1, m_PlayerManager, m_MonsterManager, m_BossManager);
		m_GodArmManager->setPosition(Vec2(0, 0));
		m_Map->addChild(m_GodArmManager, 4);

		m_GodArmManager->runPower();

		this->schedule(schedule_selector(ShowLayer::Monsterlogic), 0.1f);
		this->schedule(schedule_selector(ShowLayer::logic), 1 / 20.0f);
		this->schedule(schedule_selector(ShowLayer::Bosslogic), 1.0f);
		//�����ͼ
		this->addChild(m_Map, 0, 1);
	}
}

void ShowLayer::initPhyscsObject(Rect* m)
{
	for (int i = 0; i < 26; i++)
	{
		Sprite* sp = Sprite::create();
		auto maskLayer = LayerColor::create(Color4B(0, 0, 255, 200));
		maskLayer->setContentSize(m[i].size);
		maskLayer->setAnchorPoint(Vec2(0, 0));
		sp->addChild(maskLayer, 15);

		PhysicsBody* playerBody = PhysicsBody::createBox(m[i].size, PHYSICSBODY_MATERIAL_DEFAULT);

		playerBody->setDynamic(false);

		//��������
		playerBody->getShape(0)->setMass(100);

		//���������Ƿ�������ϵ��Ӱ��
		playerBody->setGravityEnable(false);

		playerBody->setCategoryBitmask(3);
		playerBody->setContactTestBitmask(3);
		playerBody->setCollisionBitmask(3);

		sp->setContentSize(m[i].size);
		sp->setPosition(Vec2(m[i].getMidX(), m[i].getMidY()));
		sp->setAnchorPoint(Vec2(0.0, 0.0));
		sp->setPhysicsBody(playerBody);

		this->addChild(sp);
	}
}

/*�رհ�ť�Ļص�����*/
void ShowLayer::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->replaceScene(SelectLayer::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

/*����playerΪ����*/
Point ShowLayer::setViewPoint()
{
	//��Ļ���
	auto winSize = Director::getInstance()->getWinSize();

	//int x = MAX(m_PlayerManager->getPlayer()->getPosition().x, m_MinLength + winSize.width / 2);
	int y = MAX(m_PlayerManager->getPlayer()->getPosition().y, winSize.height / 2);
	//x = MIN(x, (m_map->getMapSize().width * m_map->getTileSize().width) - winSize.width / 2);
	//x = MIN(x, (m_MaxLength)- winSize.width / 2);
	y = MIN(y, (m_Map->getMapSize().height * m_Map->getTileSize().height) - winSize.height / 2);

	//auto actualPosition = Point(x, y);
	auto actualPosition = Point(winSize.width / 2, y);
	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;

	return viewPoint;
}

void ShowLayer::useZombie(int level)
{
	m_PlayerManager->useZombie(Vec2(0, 0), m_MonsterManager->getMonsterList(),
		m_BossManager->getboss(), m_Rand);
}

void ShowLayer::useFZPower(Vec2 pt)
{
	//���������Ч
	CCParticleSystemQuad *mParticle = CCParticleSystemQuad::create("showClick.plist");
	mParticle->setScale(0.5f);
	mParticle->setPosition(pt);

	//���������,���Ӳ��ź��ڴ治�ͷ�
	mParticle->setAutoRemoveOnFinish(true);
	this->addChild(mParticle);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 pt2;
	pt2.x = (pt.x - visibleSize.width / 2) < 0 ? -5 : 5;
	pt2.y = (pt.y - visibleSize.height / 2) < 0 ? -5 : 5;

	auto action = MoveTo::create(0.2f, pt2);
	auto action2 = MoveTo::create(0.5f, Vec2(-pt2.x, -pt2.y));
	auto action3 = ScaleTo::create(0.2f, 1.1f);
	auto action4 = ScaleTo::create(0.5f, 1.0f);

	//��Ļ����Ч
	this->m_Map->runAction(Sequence::create(Spawn::create(action, action3, NULL),
		Spawn::create(action2, action4, NULL), NULL));

	//ʹ�����＼��
	m_PlayerManager->useFZ(pt, m_MonsterManager->getMonsterList(),
		m_BossManager->getboss(), m_FirePower);
}

/*
void ShowLayer::removeJoint()
{
m_World->removeJoint(m_Joint);
}*/

/*��������ʹ�õĹ���*/
void ShowLayer::retBeginLayer()
{
	//Director::getInstance()->replaceScene(SelectLayer::createScene());
	Director::getInstance()->replaceScene(BeginLayer::createScene());
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

/*player��Ծ����*/
void ShowLayer::jumpPlayer()
{
	m_PlayerManager->jumpPlayer();
}

/*����showLayer���߼�*/
void ShowLayer::logic(float dt)
{
	m_PlayerManager->logic(m_Map->getMapSize().width * m_Map->getTileSize().width,
		m_MinLength, m_MaxLength);
	//m_BossManager->logic(Vec2(0, 0));
}

void ShowLayer::Bosslogic(float dt)
{
	//if (m_MonsterManager->getDeadMonsterNum() % 5 == 0
	//   && m_MonsterManager->getDeadMonsterNum() != 0)
	if (m_MonsterManager->getDeadMonsterNum() > 10
		&& m_MonsterManager->getDeadMonsterNum() != 0)
	{
		m_BossManager->scheduleOnce(schedule_selector(BossManager::createBoss), 1.0f);
		this->unschedule(schedule_selector(ShowLayer::Bosslogic));
	}
}

void ShowLayer::Monsterlogic(float dt)
{
	m_PlayerManager->killMonster(m_MonsterManager->getMonsterList());                //����Ƿ����ɱ��Monster
	m_MonsterManager->killPlayer(m_PlayerManager->getzombiePtr());                          //����Ƿ����ɱ��Player
	m_MonsterManager->logic();
}