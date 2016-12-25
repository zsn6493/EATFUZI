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

MonsterManager* MonsterManager::create(ValueVector monsterPoints, int level)
{
	MonsterManager* monster = new MonsterManager();
	if (monster && monster->init(monsterPoints, level))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool MonsterManager::init(ValueVector monsterPoints, int level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	switch (level)
	{
	case 1:
	{
			  for (auto mp : monsterPoints)
			  {
				  ValueMap monsterPoint = mp.asValueMap();

				  //�����ͼ�Ϲ���ĳ�ʼ����
				  float monsterX = monsterPoint.at("x").asFloat();
				  float monsterY = monsterPoint.at("y").asFloat();

				  //��������
				  int random = CCRANDOM_0_1() * 4 - CCRANDOM_0_1() * 4;
				  auto monster = Monster::create(Sprite::create(FIRE_MONSTER), 1);
				  monster->setScale(0.5f);
				  monster->setPosition(Vec2(monsterX + random % 25, monsterY));
				  monster->setOrigin(Vec2(monsterX, monsterY));
				  monster->changeStatus(CharType::t1);
				  this->addChild(monster, 1);

				  auto power = PlayerPower::create(monster);
				  monster->setPower(power);
				  this->addChild(power);

				  //�������＼��
				  m_monsterList.pushBack(monster);
			  }

			  this->schedule(schedule_selector(MonsterManager::controlAction), 0.1f);
			  break;
	}
	case 2:
	{
			  break;
	}
	case 3:
	{
			  m_level = 3;
			  m_monsterPoints = monsterPoints;

			  this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap), 5.0f);

			  this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap2), 5.0f);

			  this->schedule(schedule_selector(MonsterManager::controlAction), 0.1f);
			  break;
	}
	case 4:
	{
			  m_level = 4;
			  m_monsterPoints = monsterPoints;

			  this->schedule(schedule_selector(MonsterManager::callMonsterIntoMap), 5.0f);

			  this->schedule(schedule_selector(MonsterManager::controlAction), 0.1f);
			  break;
	}
	default:
	{
			   break;
	}
	}

	scheduleUpdate();

	return true;
}

//��ʼ������ģ��
void MonsterManager::initPhysicsBody(Monster* monster)
{
	auto monsterBody = PhysicsBody::createBox(monster->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	monsterBody->setRotationEnable(false);
	monsterBody->getShape(0)->setDensity(0.0f);
	monsterBody->getShape(0)->setMass(50);

	monsterBody->setCategoryBitmask(1);
	monsterBody->setContactTestBitmask(2);
	monsterBody->setCollisionBitmask(2);

	//���������Ƿ�������ϵ��Ӱ��
	monsterBody->setGravityEnable(true);

	monster->setPhysicsBody(monsterBody);
}

/*��ȡ����*/
Vector<Monster*>* MonsterManager::getMonsterList()
{
	return &this->m_monsterList;
}

/*���ӹ���*/
void MonsterManager::visiableMonster()
{
}

/*ʹ�ü���*/
void MonsterManager::usePower()
{
}

void MonsterManager::initMonsterProper(Monster* monster,
	int baseAtk,
	int curAtk,
	int hp,
	int defens,
	int speed,
	int curAtkSpeed)
{
	monster->setiBaseAtk(baseAtk);
	monster->setiCurAtk(curAtk);
	monster->setiHP(hp);
	monster->setiDefens(defens);
	monster->setiSpeed(speed);
	monster->setiAtkSpeed(curAtkSpeed);
}

/*��������1*/
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

			//�����ͼ�Ϲ���ĳ�ʼ����
			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			auto monster = Monster::create(Sprite::create(JUMP_MONSTER), CharType::t2);
			monster->setPosition(Vec2(monsterX, monsterY));

			initMonsterProper(monster, 10, 2, 100, 1, 1, 1);
			this->addChild(monster, 1);

			//��ʼ���������
			initPhysicsBody(monster);

			//ִ�ж���
			auto action = AnimoTool::createMonsterAnimationLEVEL3();
			monster->getSprite()->runAction(Sequence::create(DelayTime::create(1.0f), action, NULL));

			//�������＼��
			m_monsterList.pushBack(monster);
		}

		m_MonsterNum++;
	}

	if (m_MonsterNum > 16)
		this->unschedule(schedule_selector(MonsterManager::callMonsterIntoMap));
}

/*��������2�ٻ�*/
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

			//�����ͼ�Ϲ���ĳ�ʼ����
			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			auto monster = Monster::create(Sprite::create("JI/JI (1).png"), CharType::t1);
			monster->setPosition(Vec2(monsterX, monsterY));

			//�趨��������
			initMonsterProper(monster, 20, 5, 100, 1, 1, 1);
			this->addChild(monster, 1);

			//��ʼ���������
			initPhysicsBody(monster);

			//���ﶯ��
			auto action = AnimoTool::createMonsterAnimation3();
			monster->getSprite()->runAction(Sequence::create(DelayTime::create(1.0f),
				action,
				NULL));

			//�������＼��
			m_monsterList.pushBack(monster);
			break;
		}

		m_MonsterNum++;
	}

	if (m_MonsterNum > 16)
		this->unschedule(schedule_selector(MonsterManager::callMonsterIntoMap2));
}

/*��ײ���*/
int MonsterManager::killPlayer(Vector<Player*>* playerList)
{
	for (auto monster : m_monsterList)
	{
		Rect mrect = monster->boundingBox();
		for (auto player : *playerList)
		{
			if (!player->isDead())
			{
				float bzX = player->getContentSize().width / 2 +
					monster->getContentSize().width / 2;
				float bzY = abs(player->getContentSize().height / 2 -
					monster->getContentSize().height / 2);
				float constractDistance = sqrt(bzX * bzX + bzY * bzY);

				float reX = abs(player->getPosition().x - monster->getPosition().x);
				float reY = abs(player->getPosition().y - monster->getPosition().y);
				float currentDistance = sqrt(reX * reX + reY * reY);

				if (currentDistance < constractDistance)
				{
					monster->setmoveStatus(false);

					//�˺�����
					int temp = CCRANDOM_0_1() *
						(player->getiBaseAtk() + player->getiCurAtk() - monster->getiDefens());
					monster->hurtMe(temp);

					//�˺�չʾ
					string boold = StringUtils::format("%d", temp);
					FlowWord* flowWord = FlowWord::create();
					flowWord->showWord(boold.c_str(),
						Vec2(monster->getSprite()->getPosition().x,
						monster->getSprite()->getPosition().y +
						monster->getContentSize().height / 2));
					flowWord->gettextLab()->setColor(Color3B(255, 0, 0));
					monster->addChild(flowWord);
				}
				else
				{
					monster->setmoveStatus(true);
				}
			}
		}

		//һ���߼�bug����������û����״̬
		if (playerList->empty())
		{
			monster->setmoveStatus(true);
		}
	}

	return 0;
}

void MonsterManager::controlAction(float dt)
{
	for (auto monster : m_monsterList)
	{
		if (monster->getmoveStatus())
		{
			monster->scheduleOnce(schedule_selector(Monster::updateCallBack), 0.1f);
			if (monster->getstartMoveAction() == false)
			{
				monster->setstartMoveAction(true);
				monster->setstartFightAciton(false);
			}
		}
		else
		{
			if (monster->getstartFightAciton() == false)
			{
				monster->setstartFightAciton(true);
				monster->setstartMoveAction(false);
			}
		}
	}
}

/*�߼�*/
void MonsterManager::logic()
{
	for (auto monster : m_monsterList)
	{
		if (monster->isDead())
		{
			int charType = monster->getCharType();
			NOTIFY->postNotification("KillMonsterNum", (Ref*)&charType);

			int loseBlood = charType * 10;
			NOTIFY->postNotification("LOSEBLOOD", (Ref*)&loseBlood);

			m_DeadMonsterNum++;
			m_monsterList.eraseObject(monster);
			monster->removeFromParentAndCleanup(true);
			break;
		}
	}
}