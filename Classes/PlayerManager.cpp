#include "PlayerManager.h"
#include "MonsterManager.h"
#include "PowerEnum.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include "PartiscEx.h"
#include "common.h"

PlayerManager::PlayerManager()
{
	m_Power = NULL;
	m_HurtValue = 1;
	m_BigPower = false;
	m_CharType = CharType::Origin;
}

PlayerManager::~PlayerManager()
{
	this->unscheduleAllSelectors();
}

/*创建英雄*/
PlayerManager* PlayerManager::createWithLevel(Vec2 pt, int level)
{
	PlayerManager* playerManager = new PlayerManager();
	if (playerManager && playerManager->init(pt, level))
	{
		playerManager->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(playerManager);
	}

	return playerManager;
}

/*初始化*/
bool PlayerManager::init(Vec2 pt, int level)
{
	m_Origin = pt;
	m_level = level;

	//模拟默认类型
	m_CharType = CharType::Origin;

	//初始化人物图片的资源
	initPlayerPic(CharType::Origin);

	//创建player
	m_Player = Player::create(Sprite::create(m_FileName, m_Rect));
	m_Player->setAnchorPoint(Vec2(0.5, 0.5));
	m_Player->setPosition(Vec2(pt.x + m_Player->getContentSize().width / 2, pt.y + m_Player->getContentSize().height / 2));
	this->addChild(m_Player, 1);

	//设置player称号
	m_Player->setSpecialName("MHunter");

	//保存zombie容器指针
	this->setzombiePtr(&m_zombieVector);

	//初始化随机种子
	initRandSeed();

	//zombie的移动逻辑控制
	this->schedule(schedule_selector(PlayerManager::controlAction), 0.1f);

	return true;
}

void PlayerManager::initPlayerPic(CharType charType)
{
	//判断人物类型 关联不同资源
	switch (charType)
	{
	case Origin:
		m_FileName = NEWTYPE_ONE;
		m_Rect = NEWTYPE_ONE_RECT;
		break;
	case t1:
		m_FileName = FIRE_MONSTER;
		m_Rect = FIRE_MONSTER_RECT;
		break;
	case t2:
		m_FileName = JUMP_MONSTER;
		m_Rect = JUMP_MONSTER_RECT;
		break;
	case t3:
		m_FileName = NEWTYPE_TWO;
		m_Rect = NEWTYPE_TWO_RECT;
		break;
	case t4:
		m_FileName = NEWTYPE_ONE;
		m_Rect = NEWTYPE_ONE_RECT;
		break;
	}
}

void PlayerManager::startPlayerMoveAction()
{
	//if (CharType::Origin == m_CharType)
	//{
	//	auto right = AnimoTool::newTypeOneRightMoveAnimotion();
	//	m_Player->getSprite()->runAction(right);
	//}
	//else if (m_CharType == t2)
	//{
	//}
}

void PlayerManager::stopPlayerAction()
{
	//if (m_CharType == CharType::Origin)
	//{
	//	m_Player->getSprite()->stopAllActions();
	//	m_Player->bindSprite(Sprite::create(m_FileName, m_Rect));
	//}
}

/*移动player*/
void PlayerManager::movePlayer(int flag)
{
	return;
}

/*获取英雄*/
Player* PlayerManager::getPlayer()
{
	return this->m_Player;
}

BezierTo* PlayerManager::bezierAction(Vec2 first, Vec2 last, int radian)
{
	float r = radian * 3.14159 / 180.0;
	// 第一个控制点为抛物线左半弧的中点
	float q1x = first.x + (last.x - first.x) / 4.0;
	Point q1 = ccp(q1x, 100 + first.y + cos(r)*q1x);

	float q2x = first.x + (last.x - first.x) / 2.0;
	Point q2 = ccp(q2x, 100 + first.y + cos(r)*q2x);

	ccBezierConfig bezier;
	bezier.controlPoint_1 = q1;
	bezier.controlPoint_2 = q2;
	bezier.endPosition.y = 100;
	bezier.endPosition.x = last.x + last.y - 100;
	//bezier.endPosition.y = pt.y;
	//bezier.endPosition.x = pt.x;
	//创建BezierTo动作对象
	auto bezierTo = BezierTo::create(0.5f, bezier);

	return 	bezierTo;
}

void PlayerManager::useSinglePower(Vec2 pt, Vector<Monster*>* monsterList,
	Boss* boss,
	bool firePower)
{
	//创建武器
	auto power = PlayerPower::createSp(Sprite::create("Arm4.png"), 0, CCRANDOM_0_1() * this->getHurtValue());
	auto winSize = Director::getInstance()->getWinSize();

	/* 武器动作模式*/
	Vec2 playerPt = getPlayer()->getPosition();
	power->setFirePower(firePower);
	power->setAnchorPoint(Vec2(0.5f, 0.5f));
	power->setPosition(Vec2(playerPt.x, playerPt.y - 50));

	//武器弧度
	auto bezierTo = bezierAction(playerPt, pt, 30);

	//武器旋转
	auto rb = RotateBy::create(0.5f, 360 * 2);
	power->runAction(Spawn::create(bezierTo, rb, NULL));

	/*需改进To do*/
	power->monsterList = monsterList;
	power->boss = boss;

	//CCLOG("power %2.2f, %2.2f\n", power->getPosition().x, power->getPosition().y);
	this->addChild(power);
}

void PlayerManager::useLongPower(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss)
{
	//创建武器
	Vec2 playerPt = getPlayer()->getPosition();
	auto power = PlayerPower::createSp(Sprite::create("Arm1.png"), 1, 1000);
	power->setAnchorPoint(Vec2(0.5f, 0.5f));
	power->setPosition(playerPt);

	//执行动作模式
	auto mb = MoveTo::create(0.4, pt);
	CCEaseBackIn* backIn = CCEaseBackIn::create(dynamic_cast<CCActionInterval *>(mb));
	power->runAction(backIn);

	/*需改进To do*/
	power->monsterList = monsterList;
	power->boss = boss;

	this->addChild(power);
}

void PlayerManager::setZombieColor(int index, Player* zombie)
{
	switch (index)
	{
	case 1:
	{
			  zombie->getSprite()->setColor(Color3B(0, 255, 255));
			  break;
	}
	case 2:
	{
			  zombie->getSprite()->setColor(Color3B(75, 0, 130));
			  zombie->setScale(2.0f);
			  break;
	}
	case 3:
	{
			  zombie->getSprite()->setColor(Color3B(255, 215, 0));
			  break;
	}
	case 4:
	{
			  zombie->getSprite()->setColor(Color3B(218, 165, 32));
			  break;
	}
	case 5:
	{
			  zombie->getSprite()->setColor(Color3B(255, 0, 0));
			  break;
	}
	default:
	{
			   break;
	}
	}
}

void PlayerManager::useZombie(Vec2 pt, int level)
{
	auto zombie = Player::create(Sprite::create(m_FileName, m_Rect));
	zombie->setAnchorPoint(Vec2(0.5f, 0.5f));
	zombie->setPosition(getPlayer()->getPosition());

	//随机值zomRandIndex代表zombie类型（种类）
	int zomRandIndex = rand() % level;

	//设置zombie的外表颜色
	setZombieColor(zomRandIndex, zombie);

	//设置zombie的移动方式
	zombie->setmoveType(zomRandIndex);

	//设置zombie的血量
	zombie->setiHP(1000);
	this->addChild(zombie);

	m_zombieVector.pushBack(zombie);
}

/*改变技能类型*/
void PlayerManager::changeStatus(CharType ct)
{
	this->m_CharType = ct;
	this->m_Power->cleanSprite();
}

/*碰撞检测*/
int PlayerManager::killMonster(Vector<Monster*>* monsterList)
{
	for (auto zombie : m_zombieVector)
	{
		Rect mrect = zombie->boundingBox();
		for (auto monster : *monsterList)
		{
			float contractX = zombie->getContentSize().width / 2 + monster->getContentSize().width / 2;
			float contractY = abs(zombie->getContentSize().height / 2 - monster->getContentSize().height / 2);
			float contractDistance = sqrt(contractX * contractX + contractY * contractY);

			float currentX = abs(zombie->getPosition().x - monster->getPosition().x);
			float currentY = abs(zombie->getPosition().y - monster->getPosition().y);
			float currentDistance = sqrt(currentX * currentX + currentY * currentY);

			if (currentDistance <= contractDistance)
			{
				zombie->setmoveStatus(false);

				if (zombie->gethurtedStatus() == false)
				{
					zombie->sethurtedStatus(true);
					zombie->sethurtedValue(monster->getiBaseAtk() + monster->getiCurAtk() - zombie->getiDefens());
					zombie->scheduleOnce(schedule_selector(Player::fightSpeedZombie), 1.0f);
				}

				//int temp = (monster->getiBaseAtk() + monster->getiCurAtk() - zombie->getiDefens());
				//zombie->hurtMe(temp);

				//std::string blood = StringUtils::format("%d", temp);
				//FlowWord* flowWord = FlowWord::create();
				//flowWord->showWord(blood.c_str(), Vec2(zombie->getSprite()->getPosition().x, zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
				//flowWord->gettextLab()->setColor(Color3B(255, 0, 0));
				//zombie->addChild(flowWord);

				//monster->setAcceptBlood(CCRANDOM_0_1() * zombie->getiCurAtk());
			}
			else
			{
				zombie->setmoveStatus(true);
			}
		}

		if (monsterList->empty())
		{
			zombie->setmoveStatus(true);
		}
	}

	return 0;
}

void PlayerManager::controlAction(float dt)
{
	for (auto zombie : m_zombieVector)
	{
		if (zombie->getmoveStatus())
		{
			zombie->scheduleOnce(schedule_selector(Player::moveZombie), 0.1f);

			if (zombie->getstartMoveAction() == false)
			{
				zombie->setstartMoveAction(true);
				zombie->setstartFightAciton(false);
				zombie->getSprite()->stopActionByTag(101);

				//zombie运动动画
				auto action = AnimoTool::newTypeOneRightMoveAnimotion();
				action->setTag(100);
				zombie->getSprite()->runAction(action);
			}
		}
		else
		{
			if (zombie->getstartFightAciton() == false)
			{
				zombie->setstartFightAciton(true);
				zombie->setstartMoveAction(false);
				zombie->getSprite()->stopActionByTag(100);

				//zombie运动动画
				auto action = AnimoTool::newTypeOneAttactAnimotion();
				action->setTag(101);
				zombie->getSprite()->runAction(action);
			}
		}
	}
}

/*玩家跳跃能力*/
void PlayerManager::jumpPlayer()
{
	//设置跳跃
	m_Player->getPhysicsBody()->setVelocity(Vect(150, 500));
}

/*死亡后的效果*/
void PlayerManager::runPlayerDeadPower(Player* zombie)
{
	if (zombie->getmoveType() == 1)
	{
		PartiscEx* pe = PartiscEx::create();
		pe->PlayExplosion(zombie->getPosition());
		this->getParent()->addChild(pe, 3);
	}

	if (zombie->getmoveType() == 0)
	{
		//攻击力加成
		int hurtValue = this->getHurtValue();
		setHurtValue(++hurtValue);
		for (auto zombie : m_zombieVector)
		{
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("+1", Vec2(zombie->getSprite()->getPosition().x, zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(Color3B(0, 255, 0));
			zombie->addChild(flowWord);
			int count = zombie->getiCurAtk();
			zombie->setiCurAtk(++count);
		}
	}
	else if (zombie->getmoveType() == 1)
	{
		//防御力加成
		Color3B color3b = zombie->getSprite()->getColor();
		for (auto zombie : m_zombieVector)
		{
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("+1", Vec2(zombie->getSprite()->getPosition().x, zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(color3b);
			zombie->addChild(flowWord);

			int count = zombie->getiDefens();
			zombie->setiDefens(++count);
		}
	}
	else if (zombie->getmoveType() == 2)
	{
		//HP加成
		Color3B color3b = zombie->getSprite()->getColor();
		for (auto zombie : m_zombieVector)
		{
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("+1", Vec2(zombie->getSprite()->getPosition().x,
				zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(color3b);
			zombie->addChild(flowWord);

			int count = zombie->getiHP();
			zombie->setiHP(++count);
		}
	}
	else if (zombie->getmoveType() == 3)
	{
		//速度加成
		Color3B color3b = zombie->getSprite()->getColor();
		for (auto zombie : m_zombieVector)
		{
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("+1", Vec2(zombie->getSprite()->getPosition().x,
				zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(color3b);
			zombie->addChild(flowWord);

			int count = zombie->getiSpeed();
			zombie->setiSpeed(++count);
		}
	}
	else if (zombie->getmoveType() == 4)
	{
		//攻击速度加成
		Color3B color3b = zombie->getSprite()->getColor();
		for (auto zombie : m_zombieVector)
		{
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("+1", Vec2(zombie->getSprite()->getPosition().x,
				zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(color3b);
			zombie->addChild(flowWord);

			int count = zombie->getiAtkSpeed();
			zombie->setiAtkSpeed(++count);
		}
	}
}

/*zombie死亡释放处理*/
void PlayerManager::logic()
{
	for (auto zombie : m_zombieVector)
	{
		switch (zombie->getZombieStatus())
		{
		case MoveStatus:
			break;
		case FigthStatus:
			break;
		case DieStatus:
			break;
		default:
			break;
		}

		auto winSize = Director::getInstance()->getWinSize();
		if (zombie->getPositionX() > winSize.width)
		{
			zombie->hurtMe(1000);
		}

		if (zombie->isDead())
		{
			runPlayerDeadPower(zombie);
			zombie->removeFromParentAndCleanup(true);
			m_zombieVector.eraseObject(zombie);
			break;
		}
	}
}