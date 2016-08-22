#include "Monster.h"
#include "MonsterManager.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include <string>
using namespace std;

#define NOTIFY cocos2d::NotificationCenter::getInstance()

MonsterManager::MonsterManager()
{
	m_MonsterNum = 2;
	m_DeadMonsterNum = 0;
}

MonsterManager::~MonsterManager()
{
	this->unscheduleAllSelectors();
}

MonsterManager* MonsterManager::createWithLevel(ValueVector monsterPoints)
{
	MonsterManager* monster = new MonsterManager();
	if (monster && monster->initWithLevel(monsterPoints))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool MonsterManager::initWithLevel(ValueVector monsterPoints)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (auto mp : monsterPoints)
	{
		ValueMap monsterPoint = mp.asValueMap();

		//保存地图上怪物的初始坐标
		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		//创建怪物
		int random = CCRANDOM_0_1() * 4 - CCRANDOM_0_1() * 4;
		auto monster = Monster::create(Sprite::create("FireMonster.png"), 1);
		monster->setScale(0.5f);
		monster->setPosition(Vec2(monsterX + random % 25, monsterY));
		monster->setOrigin(Vec2(monsterX, monsterY));
		monster->changeStatus(PowerEnumStatus::useFire);
		this->addChild(monster, 1);

		auto power = PlayerPower::create(monster);
		monster->setPower(power);
		this->addChild(power);

		//创建怪物技能
		m_monsterList.pushBack(monster);
	}

	scheduleUpdate();
	return true;
}

MonsterManager* MonsterManager::createWithLevel(ValueVector monsterPoints, int level)
{
	MonsterManager* monster = new MonsterManager();
	if (monster && monster->initWithLevel(monsterPoints, level))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool MonsterManager::initWithLevel(ValueVector monsterPoints, int level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (level == 1)
	{
		for (auto mp : monsterPoints)
		{
			ValueMap monsterPoint = mp.asValueMap();

			//保存地图上怪物的初始坐标
			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			//创建怪物
			int random = CCRANDOM_0_1() * 4 - CCRANDOM_0_1() * 4;
			auto monster = Monster::create(Sprite::create(FIRE_MONSTER), 1);
			monster->setScale(0.5f);
			monster->setPosition(Vec2(monsterX + random % 25, monsterY));
			monster->setOrigin(Vec2(monsterX, monsterY));
			monster->changeStatus(PowerEnumStatus::useFire);
			this->addChild(monster, 1);

			auto power = PlayerPower::create(monster);
			monster->setPower(power);
			this->addChild(power);

			//创建怪物技能
			m_monsterList.pushBack(monster);
		}

		this->schedule(schedule_selector(MonsterManager::controlAction), 0.5f);
	}
	else if (level == 3)
	{
		m_level = 3;
		m_monsterPoints = monsterPoints;

		this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap), 5.0f);

		this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap2), 5.0f);

		this->schedule(schedule_selector(MonsterManager::controlAction), 0.5f);
	}
	else if (level == 4)
	{
		m_level = 4;
		m_monsterPoints = monsterPoints;

		this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap), 5.0f);

		this->schedule(schedule_selector(MonsterManager::controlAction), 0.5f);
	}

	scheduleUpdate();

	return true;
}

void MonsterManager::initPhysicsBody(Monster* monster)
{
	auto monsterBody = PhysicsBody::createBox(monster->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	monsterBody->setRotationEnable(false);
	monsterBody->getShape(0)->setDensity(0.0f);
	monsterBody->getShape(0)->setMass(50);

	monsterBody->setCategoryBitmask(1);
	monsterBody->setContactTestBitmask(2);
	monsterBody->setCollisionBitmask(2);

	//设置物体是否受重力系数影响
	monsterBody->setGravityEnable(true);

	monster->setPhysicsBody(monsterBody);
}

/*获取怪物*/
Vector<Monster*>* MonsterManager::getMonsterList()
{
	return &this->m_monsterList;
}

/*可视怪物*/
void MonsterManager::visiableMonster()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//monster->setVisible(true);
	//monster->setPosition(Vec2(visibleSize.width, 16 * 9 + monster->getContentSize().width / 2));
}

/*使用技能*/
void MonsterManager::usePower()
{
	/*
	switch (monster->getPowerStatus())
	{
	case useFire:
	m_power->useFire(monster->getPosition());
	break;
	case useIce:
	m_power->useIce(monster->getPosition());
	break;
	}*/
}

void MonsterManager::nextMap(CCTMXTiledMap* map, int maxLength)
{
	auto winSize = Director::getInstance()->getWinSize();

	//this->unschedule(schedule_selector(ShowLayer::Monsterlogic));
	m_monsterList.clear();

	TMXObjectGroup* eobjGoup = map->getObjectGroup(StringUtils::format("earth%d", (maxLength + 3200) / 3200).c_str());
	ValueVector er = eobjGoup->getObjects();
	for (auto ernum : er)
	{
		ValueMap tm = ernum.asValueMap();
		Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(),
			tm.at("width").asFloat(), tm.at("height").asFloat());

		auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
		playerBody->setDynamic(false);
		//设置质量
		playerBody->getShape(0)->setMass(100);
		//设置物体是否受重力系数影响
		playerBody->setGravityEnable(false);

		auto sp = Sprite::create();
		sp->setContentSize(rect.size);
		sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
		sp->setAnchorPoint(Vec2(0.0, 0.0));
		sp->setPhysicsBody(playerBody);

		map->addChild(sp);
	}

	TMXObjectGroup* mobjGoup = map->getObjectGroup(StringUtils::format("monster%d", (maxLength + 3200) / 3200).c_str());
	ValueVector monsterPoints = mobjGoup->getObjects();
	for (auto mp : monsterPoints)
	{
		ValueMap monsterPoint = mp.asValueMap();
		//保存地图上怪物的初始坐标

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		int random = CCRANDOM_0_1() * 4 - CCRANDOM_0_1() * 4;
		//创建怪物
		auto monster = Monster::create(Sprite::create(FIRE_MONSTER), useFire);
		monster->setScale(1.0f);
		monster->setPosition(Vec2(monsterX + random % 25, monsterY));
		monster->setOrigin(Vec2(monsterX, monsterY));
		monster->changeStatus(PowerEnumStatus::useFire);
		this->addChild(monster, 1);

		//创建怪物技能
		auto power = PlayerPower::create(monster);
		monster->setPower(power);
		this->addChild(power);
		m_monsterList.pushBack(monster);
	}
}

void MonsterManager::callMonsterIntoMap(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int m = m_monsterList.size();
	if (m_monsterList.size() == 0)
	{
		for (auto mp : m_monsterPoints)
		{
			ValueMap monsterPoint = mp.asValueMap();

			//保存地图上怪物的初始坐标
			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			auto monster = Monster::create(Sprite::create(JUMP_MONSTER), useIce);
			//monster->setPosition(Vec2(monsterX, visibleSize.height - monsterY));
			monster->setPosition(Vec2(monsterX, monsterY));
			monster->setiHP(m_MonsterNum + 2);
			//monster->setScale(0.5f);
			this->addChild(monster, 1);

			//初始化物理刚体
			initPhysicsBody(monster);

			auto action = AnimoTool::createMonsterAnimationLEVEL3();
			monster->getSprite()->runAction(Sequence::create(DelayTime::create(1.0f), action, NULL));

			//创建怪物技能
			m_monsterList.pushBack(monster);
		}

		m_MonsterNum++;
	}

	if (m_MonsterNum > 16)
		this->unschedule(schedule_selector(MonsterManager::callMonsterIntoMap));
}

void MonsterManager::callMonsterIntoMap2(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int m = m_monsterList.size();
	if (m_MonsterNum % 3 == 0)
	{
		for (auto mp : m_monsterPoints)
		{
			ValueMap monsterPoint = mp.asValueMap();

			//保存地图上怪物的初始坐标
			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			auto monster = Monster::create(Sprite::create("JI/JI (1).png"), useFire);
			//monster->setPosition(Vec2(monsterX, visibleSize.height - monsterY));
			monster->setPosition(Vec2(monsterX, monsterY));
			monster->setiHP(100);
			//monster->setScale(0.5f);
			this->addChild(monster, 1);

			//初始化物理刚体
			initPhysicsBody(monster);

			auto action = AnimoTool::createMonsterAnimation3();
			monster->getSprite()->runAction(Sequence::create(DelayTime::create(1.0f), action, NULL));

			//创建怪物技能
			m_monsterList.pushBack(monster);
			break;
		}

		m_MonsterNum++;
	}

	if (m_MonsterNum > 16)
		this->unschedule(schedule_selector(MonsterManager::callMonsterIntoMap2));
}

/*碰撞检测*/
int MonsterManager::killPlayer(Vector<Player*>* playerList)
{
	for (auto ms : m_monsterList)
	{
		Rect mrect = ms->boundingBox();
		for (auto py : *playerList)
		{
			float bzX = py->getContentSize().width / 2 + ms->getContentSize().width / 2;
			float bzY = py->getContentSize().height / 2 + ms->getContentSize().height / 2;

			float bz = sqrt(bzX * bzX + bzY * bzY);

			float reX = py->getPosition().x - ms->getPosition().x;
			float reY = py->getPosition().y - ms->getPosition().y;

			float h = sqrt(reX * reX + reY * reY);

			if (h < bz)
			{
				ms->setmoveStatus(false);
			}
			else
			{
				ms->setmoveStatus(true);
			}
		}
	}

	return 0;
}

void MonsterManager::controlAction(float dt)
{
	for (auto ms : m_monsterList)
	{
		if (ms->getmoveStatus())
		{
			ms->scheduleOnce(schedule_selector(Monster::updateCallBack), 0.2f);
			if (ms->getstartMoveAction() == false)
			{
				ms->setstartMoveAction(true);
				ms->setstartFightAciton(false);
			}
		}
		else
		{
			if (ms->getstartFightAciton() == false)
			{
				ms->setstartFightAciton(true);
				ms->setstartMoveAction(false);
			}

			ms->hurtMe(ms->getAcceptBlood());

			string boold = StringUtils::format("%d", ms->getAcceptBlood());
			//py->hurtMe(1);
			FlowWord* fw = FlowWord::create();
			ms->addChild(fw);
			fw->showWord(boold.c_str(), Vec2(ms->getSprite()->getPosition().x, ms->getSprite()->getPosition().y + ms->getContentSize().height / 2));
			fw->gettextLab()->setColor(Color3B(255, 0, 0));
		}
	}
}

/*逻辑*/
void MonsterManager::logic()
{
	for (auto sp : m_monsterList)
	{
		if (sp->isDead())
		{
			NOTIFY->postNotification("KillMonsterNum");
			m_DeadMonsterNum++;
			m_monsterList.eraseObject(sp);
			sp->removeFromParentAndCleanup(true);
			break;
		}
	}

	for (auto ms : m_monsterList)
	{
		//ms->simpleAI(ms->getPosition());
	}
}