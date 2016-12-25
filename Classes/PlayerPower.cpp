#include "PlayerPower.h"
#include "Monster.h"
#include "PartiscEx.h"
#include "FlowWord.h"
#include "Boss.h"
#include <string>

USING_NS_CC;
#define NOTIFY cocos2d::NotificationCenter::getInstance()

PlayerPower::PlayerPower(void)
{
	m_power = NULL;
	m_boom = NULL;
	m_FirePower = false;
	m_Bload = 1;
}

PlayerPower::~PlayerPower(void)
{
}

PlayerPower* PlayerPower::create(Node* node)
{
	PlayerPower *playerPower = new PlayerPower();
	if (playerPower && playerPower->initWithFile(node))
	{
		playerPower->autorelease();
		return playerPower;
	}
	CC_SAFE_DELETE(playerPower);

	return NULL;
}

PlayerPower* PlayerPower::createSp(Sprite* sprite, int powerNum, int bloodValue)
{
	PlayerPower *playerPower = new PlayerPower();
	if (playerPower && playerPower->initWithFileSp(sprite, powerNum, bloodValue))
	{
		playerPower->autorelease();
		return playerPower;
	}
	CC_SAFE_DELETE(playerPower);

	return NULL;
}

bool PlayerPower::initWithFileSp(Sprite* sprite, int powerNum, int bloodValue)
{
	bool bRet = false;
	m_Bload = bloodValue;
	do
	{
		CC_BREAK_IF(!sprite);

		bindSprite(sprite);    //绑定sprite到成员函数

		if (powerNum == 0)
		{
			this->schedule(schedule_selector(PlayerPower::singleUpdate), 0.05f);
			this->scheduleOnce(schedule_selector(PlayerPower::updateCallBack), 0.7f);
		}
		else if (powerNum == 1)
		{
			this->schedule(schedule_selector(PlayerPower::longUpdate), 0.2f);
			this->scheduleOnce(schedule_selector(PlayerPower::updateCallBack), 0.5f);
		}

		bRet = true;
	} while (0);

	scheduleUpdate();

	return bRet;
}

bool PlayerPower::initWithFile(Node* node)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!node);
		this->setPosition(node->getPosition());
		//bindSprite(sprite);    //绑定sprite到成员函数
		bRet = true;
	} while (0);

	return bRet;
}

void PlayerPower::updateCallBack(float dt)
{
	if (m_FirePower)
	{
		PartiscEx* pe = PartiscEx::create();
		pe->PlayExplosion(this->getPosition());
		this->getParent()->addChild(pe, 3);
	}
	this->removeFromParentAndCleanup(true);
}

int PlayerPower::singlePowerkillMonster(Vector<Monster* >* monsterList)
{
	Rect mrect = this->boundingBox();
	for (auto ms : *monsterList)
	{
		CCLOG("point: x: %2.2f, y: %2.2f\n", this->getPositionX(), this->getPositionY());
		CCLOG("ms: x: %2.2f, y: %2.2f\n", ms->getPositionX(), ms->getPositionY());

		float contractX = abs(this->getContentSize().width / 2
			+ ms->getContentSize().width / 2);
		float contractY = abs(this->getContentSize().height / 2
			+ ms->getContentSize().height / 2);
		float contractDistance = sqrt(contractX * contractX + contractY * contractY);

		float currentX = abs(this->getPosition().x - ms->getPosition().x);
		float currentY = abs(this->getPosition().y - ms->getPosition().y);
		float currentDistance = sqrt(currentX * currentX + currentY * currentY);

		if (currentDistance < contractDistance)
		{
			ms->hurtMe(getBload());

			std::string boold = StringUtils::format("%d", getBload());

			FlowWord* fw = FlowWord::create();
			ms->addChild(fw, 20);
			fw->gettextLab()->setColor(Color3B(255, 0, 0));
			fw->showWord(boold.c_str(), Vec2(ms->getSprite()->getPosition().x,
				ms->getSprite()->getPosition().y +
				ms->getContentSize().height / 2));
		}
	}

	return 0;
}

int PlayerPower::longPowerkillMonster(Vector<Monster* >* monsterList)
{
	Rect mrect = this->boundingBox();
	for (auto ms : *monsterList)
	{
		Rect rect = ms->boundingBox();
		if (rect.containsPoint(this->getPosition())
			|| rect.containsPoint(Vec2(this->getPosition().x + this->getContentSize().width / 2, this->getPosition().y))
			|| rect.containsPoint(Vec2(this->getPosition().x - this->getContentSize().width / 2, this->getPosition().y))
			|| mrect.containsPoint(ms->getPosition()))
		{
			//伤害处理
			int msType = ms->getCharType();
			ms->hurtMe(getBload());
			NOTIFY->postNotification("ACMonster", (Ref*)&msType);

			//伤害显示
			std::string boold = StringUtils::format("%d", getBload());
			FlowWord* fw = FlowWord::create();
			ms->addChild(fw);
			fw->showWord(boold.c_str(), Vec2(ms->getSprite()->getPosition().x, ms->getSprite()->getPosition().y + ms->getContentSize().height / 2));
			fw->gettextLab()->setColor(Color3B(255, 0, 0));
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("music/m%d.wav", i % 6).c_str(), false);
		}
	}

	return 0;
}

int PlayerPower::singlePowerkillBoss(Boss* boss)
{
	if (boss == nullptr || boss->isDead())
	{
		return 0;
	}

	Rect mrect = this->boundingBox();
	Rect rect = boss->boundingBox();
	if (rect.containsPoint(this->getPosition())
		|| rect.containsPoint(Vec2(this->getPosition().x + this->getContentSize().width / 2, this->getPosition().y))
		|| rect.containsPoint(Vec2(this->getPosition().x - this->getContentSize().width / 2, this->getPosition().y))
		|| mrect.containsPoint(boss->getPosition()))
	{
		// 创建一个 Waved3D 动作
		//CCActionInterval* waves = CCWaves::create(18, Size(50, 50), 10, 20, true, true);
		//m_Nodegrid->runAction(waves);

		boss->hurtMe(1);
		FlowWord* fw = FlowWord::create();
		boss->addChild(fw);
		fw->showWord("-1", Vec2(boss->getSprite()->getPosition().x, boss->getSprite()->getPosition().y + boss->getContentSize().height / 2));
		fw->gettextLab()->setColor(Color3B(205, 0, 0));

		if (m_FirePower)
		{
			PartiscEx* pe = PartiscEx::create();
			pe->PlayExplosion(this->getPosition());
			this->getParent()->addChild(pe, 3);
		}
		this->removeFromParentAndCleanup(true);
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("music/m%d.wav", i % 6).c_str(), false);
	}

	return 0;
}

void PlayerPower::singleUpdate(float dt)
{
	singlePowerkillMonster(monsterList);

	singlePowerkillBoss(boss);
}

void PlayerPower::longUpdate(float dt)
{
	longPowerkillMonster(monsterList);
}