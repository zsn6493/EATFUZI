#include "ShowLayer.h"
#include "PhysicsWorld.h"
#include "SimpleAudioEngine.h"
#include "BeginLayer.h"
#include "AnimoTool.h"
#include "common.h"

const int PhysicBodyNum = 26;

ShowLayer::ShowLayer()
{
	m_PlayerManager = NULL;
	m_MonsterManager = NULL;
	m_BossManager = NULL;

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/dls.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/dls1.wav");

	//for (int i = 1; i <= 6; i++)
	//	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(StringUtils::format("music/m%d.wav", i).c_str());

	m_FirePower = false;
	m_CharType = (int)CharType::t1;
}

ShowLayer::~ShowLayer()
{
}

ShowLayer* ShowLayer::create(int level)
{
	ShowLayer* showLayer = new ShowLayer();
	if (showLayer && showLayer->init(level))
	{
		showLayer->autorelease();
		return showLayer;
	}
	CC_SAFE_DELETE(showLayer);
	return NULL;
}

bool ShowLayer::init(int level)
{
	if (!Layer::init())
	{
		return false;
	}

	//加载资源，创建manager
	loadConfig(level);

	//可用update
	scheduleUpdate();

	return true;
}

void  ShowLayer::onEnter()
{
	Layer::onEnter();
}

/*加载资源*/
void ShowLayer::loadConfig(int level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Level = level;

	//初始化随机种子
	initRandSeed();

	switch (level)
	{
	case 1:
	case 2:
	case 3:
	{
			  int rand = CCRANDOM_0_1() * 5;

			  //加载地图资源
			  m_Map = CCTMXTiledMap::create("LastMap2.tmx");

			  m_MaxLength = 1600;
			  m_MinLength = 0;

			  //获取地图上player的坐标
			  TMXObjectGroup* objGoup = m_Map->getObjectGroup("playerPoint");
			  ValueMap playerPointMap = objGoup->getObject("Player");

			  float playerX = playerPointMap.at("x").asFloat();
			  float playerY = playerPointMap.at("y").asFloat();

			  //创建playerManager
			  m_PlayerManager = PlayerManager::createWithLevel(Vec2(playerX, playerY + 24), level);
			  m_PlayerManager->setAnchorPoint(Vec2(0, 0));
			  m_PlayerManager->setPosition(Vec2(0, 0));
			  m_Map->addChild(m_PlayerManager, 3);

			  //获取地图上怪物坐标
			  TMXObjectGroup* mobjGoup = m_Map->getObjectGroup("monsterPoint");
			  ValueVector monsterPoints = mobjGoup->getObjects();

			  //创建物理环境
			  PhyscisWorld::createWorld(m_Map, level);

			  //创建monsterManager
			  m_MonsterManager = MonsterManager::create(monsterPoints, level);    //change
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

			  m_GodArmManager = GodArmManager::createWithLevel(GodArmType::Godt1, m_PlayerManager, m_MonsterManager, m_BossManager);
			  m_GodArmManager->setPosition(Vec2(0, 0));
			  m_Map->addChild(m_GodArmManager, 4);

			  m_GodArmManager->runPower();

			  this->schedule(schedule_selector(ShowLayer::Monsterlogic), 1 / 20.0f);
			  this->schedule(schedule_selector(ShowLayer::killPlayerlogic), 0.2f);
			  this->schedule(schedule_selector(ShowLayer::killMonsterlogic), 0.2f);
			  this->schedule(schedule_selector(ShowLayer::logic), 1 / 20.0f);
			  this->schedule(schedule_selector(ShowLayer::Bosslogic), 1.0f);
			  //认领地图
			  this->addChild(m_Map, 0, 1);
			  //CCLOG("PlayerManager %2.2f, %2.2f\n", m_PlayerManager->getPosition().x, m_PlayerManager->getPosition().y);
	}
		break;
	default:
		break;
	}
}

void ShowLayer::initPhyscsObject(Rect* m)
{
	for (int i = 0; i < PhysicBodyNum; i++)
	{
		Sprite* sp = Sprite::create();
		auto maskLayer = LayerColor::create(Color4B(0, 0, 255, 200));
		maskLayer->setContentSize(m[i].size);
		maskLayer->setAnchorPoint(Vec2(0, 0));
		sp->addChild(maskLayer, 15);

		PhysicsBody* playerBody = PhysicsBody::createBox(m[i].size,
			PHYSICSBODY_MATERIAL_DEFAULT);

		playerBody->setDynamic(false);

		//设置质量
		playerBody->getShape(0)->setMass(100);

		//设置物体是否受重力系数影响
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

/*关闭按钮的回调函数*/
void ShowLayer::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->replaceScene(SelectLayer::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

/*设置player为中心*/
Point ShowLayer::setViewPoint()
{
	//屏幕宽度
	auto winSize = Director::getInstance()->getWinSize();

	int y = MAX(m_PlayerManager->getPlayer()->getPosition().y, winSize.height / 2);
	y = MIN(y, (m_Map->getMapSize().height * m_Map->getTileSize().height) - winSize.height / 2);

	//auto actualPosition = Point(x, y);
	auto actualPosition = Point(winSize.width / 2, y);
	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;

	return viewPoint;
	//return Vec2(0, 0);
}

void ShowLayer::useZombie(int level)
{
	m_CharType = level;
	m_PlayerManager->useZombie(Vec2(0, 0), m_CharType);
}

void ShowLayer::useSinglePower(Vec2 pt)
{
	//点击粒子特效
	CCParticleSystemQuad *mParticle = CCParticleSystemQuad::create("showClick.plist");
	mParticle->setScale(0.5f);
	mParticle->setPosition(pt);

	//如果不设置,粒子播放后内存不释放
	mParticle->setAutoRemoveOnFinish(true);
	this->addChild(mParticle);

	//震屏
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto action = AnimoTool::clickEffects(pt, visibleSize);
	this->m_Map->runAction(action);

	//使用人物技能
	m_PlayerManager->useSinglePower(pt,
		m_MonsterManager->getMonsterList(),
		m_BossManager->getboss(),
		m_FirePower);
}

void ShowLayer::useLongPower(Vec2 pt)
{
	//使用人物技能
	m_PlayerManager->useLongPower(pt,
		m_MonsterManager->getMonsterList(),
		m_BossManager->getboss());
}

/*创建测试使用的怪物*/
void ShowLayer::retBeginLayer()
{
	//Director::getInstance()->replaceScene(SelectLayer::createScene());
	Director::getInstance()->replaceScene(BeginLayer::createScene());
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

/*player跳跃函数*/
void ShowLayer::jumpPlayer()
{
	m_PlayerManager->jumpPlayer();
}

/*调用showLayer的逻辑*/
void ShowLayer::logic(float dt)
{
	m_PlayerManager->logic();
}

void ShowLayer::Bosslogic(float dt)
{
	if (m_MonsterManager->getDeadMonsterNum() > 10
		&& m_MonsterManager->getDeadMonsterNum() != 0)
	{
		m_BossManager->scheduleOnce(schedule_selector(BossManager::createBoss), 1.0f);
		this->unschedule(schedule_selector(ShowLayer::Bosslogic));
	}
}

void ShowLayer::Monsterlogic(float dt)
{
	m_MonsterManager->logic();
}

void ShowLayer::killPlayerlogic(float dt)
{
	m_MonsterManager->killPlayer(m_PlayerManager->getzombiePtr());  //检测是否可以杀死Player
}

void ShowLayer::killMonsterlogic(float dt)
{
	m_PlayerManager->killMonster(m_MonsterManager->getMonsterList());  //检测是否可以杀死Monster
}