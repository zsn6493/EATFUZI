#include "PlayerManager.h"
#include "MonsterManager.h"
#include "PowerEnum.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include "PartiscEx.h"

PlayerManager::PlayerManager()
{
	m_Power = NULL;
	m_HurtValue = 1;
	m_BigPower = false;
	m_CharType = CharType::Origin;
}

PlayerManager::~PlayerManager()
{
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

	//判断人物类型 关联不同资源
	switch (m_CharType)
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

	//创建player
	m_Player = Player::create(Sprite::create(m_FileName, m_Rect));
	m_Player->setAnchorPoint(Vec2(0.5, 0.5));
	m_Player->setPosition(Vec2(pt.x + m_Player->getContentSize().width / 2, pt.y + m_Player->getContentSize().height / 2));
	this->addChild(m_Player, 1);

	m_Player->setSpecialName("MHunter");

	this->setzombiePtr(&m_zombieVector);

	struct timeval now;
	gettimeofday(&now, NULL);

	//初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //都转化为毫秒
	srand(rand_seed);

	this->schedule(schedule_selector(PlayerManager::controlAction), 0.5f);

	return true;
}

void PlayerManager::startPlayerMoveAction()
{
	if (CharType::Origin == m_CharType)
	{
		auto right = AnimoTool::newTypeOneRightMoveAnimotion();
		m_Player->getSprite()->runAction(right);
	}
	else if (m_CharType == t2)
	{
	}
}

void PlayerManager::stopPlayerAction()
{
	if (m_CharType == CharType::Origin)
	{
		m_Player->getSprite()->stopAllActions();
		m_Player->bindSprite(Sprite::create(m_FileName, m_Rect));
	}
}

/*移动player*/
void PlayerManager::movePlayer(int flag)
{
	//if (m_Player->getPositionX() - m_Player->getContentSize().width / 2 <= 0 && flag == -1)
	//{
	//	m_Player->setPositionX(m_Player->getContentSize().width / 2);
	//}
	//else  if (m_Player->getPositionX() + m_Player->getContentSize().width / 2 >= 1600 && flag == 1)
	//{
	//	m_Player->setPositionX(1600 - m_Player->getContentSize().width / 2);
	//}
	//else
	//{
	//	if (m_Destflag != flag && flag != 0)
	//	{
	//		if (flag < 0)
	//			m_Player->setRotationY(-180);
	//		else
	//			m_Player->setRotationY(0);
	//	}

	//	if (flag != 0)
	//		this->m_Destflag = flag;

	//	m_Player->movePlayer(flag);
	//}

	return;
}

/*获取英雄*/
Player* PlayerManager::getPlayer()
{
	return this->m_Player;
}

void PlayerManager::useSinglePower(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss, bool firePower)
{
	auto power = PlayerPower::createSp(Sprite::create("Arm4.png"), 0, CCRANDOM_0_1() * this->getHurtValue());
	auto winSize = Director::getInstance()->getWinSize();

	power->setFirePower(firePower);
	power->setAnchorPoint(Vec2(0.5f, 0.5f));

	Vec2 playerPt = getPlayer()->getPosition();

	power->setPosition(Vec2(playerPt.x, playerPt.y - 50));
	auto rb = RotateBy::create(0.5f, 360 * 2);

	float radian = 30 * 3.14159 / 180.0;
	// 第一个控制点为抛物线左半弧的中点
	float q1x = playerPt.x + (pt.x - playerPt.x) / 4.0;
	Point q1 = ccp(q1x, 100 + playerPt.y + cos(radian)*q1x);

	// 第二个控制点为整个抛物线的中点
	float q2x = playerPt.x + (pt.x - playerPt.x) / 2.0;
	Point q2 = ccp(q2x, 100 + playerPt.y + cos(radian)*q2x);

	ccBezierConfig bezier;
	bezier.controlPoint_1 = q1;
	bezier.controlPoint_2 = q2;
	bezier.endPosition.y = 100;
	bezier.endPosition.x = pt.x + pt.y - 100;

	//创建BezierTo动作对象
	auto bezierTo = BezierTo::create(0.5f, bezier);
	power->runAction(Spawn::create(bezierTo, rb, NULL));
	power->monsterList = monsterList;

	power->boss = boss;

	this->addChild(power);
}

void PlayerManager::useLongPower(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss)
{
	auto power = PlayerPower::createSp(Sprite::create("Arm1.png"), 1, 1000);

	Vec2 playerPt = getPlayer()->getPosition();
	power->setPosition(playerPt);

	auto mb = MoveTo::create(0.4, pt);
	CCEaseBackIn* backIn = CCEaseBackIn::create(dynamic_cast<CCActionInterval *>(mb));
	power->runAction(backIn);

	power->setAnchorPoint(Vec2(0.5f, 0.5f));

	power->monsterList = monsterList;
	power->boss = boss;

	this->addChild(power);
}

void PlayerManager::useZombie(Vec2 pt, int level)
{
	auto zombie = Player::create(Sprite::create(m_FileName, m_Rect));
	zombie->setAnchorPoint(Vec2(0.5f, 0.5f));
	zombie->setPosition(getPlayer()->getPosition());

	int r = rand() % level;
	switch (r)
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
		break;
	}

	zombie->setmoveType(r);
	zombie->setiHP(100);
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
			float contractY = zombie->getContentSize().height / 2 + monster->getContentSize().height / 2;
			float contractDistance = sqrt(contractX * contractX + contractY * contractY);

			float currentX = abs(zombie->getPosition().x - monster->getPosition().x);
			float currentY = abs(zombie->getPosition().y - monster->getPosition().y);
			float currentDistance = sqrt(currentX * currentX + currentY * currentY);

			if (currentDistance <= contractDistance / 2)
			{
				zombie->setmoveStatus(false);
				monster->setAcceptBlood(CCRANDOM_0_1() * this->getHurtValue());
			}
			else
			{
				zombie->setmoveStatus(true);
			}
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
			zombie->scheduleOnce(schedule_selector(Player::moveZombie), 0.2f);

			if (zombie->getstartMoveAction() == false)
			{
				zombie->setstartMoveAction(true);
				zombie->setstartFightAciton(false);
				zombie->getSprite()->stopActionByTag(101);
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
				auto action = AnimoTool::newTypeOneAttactAnimotion();
				action->setTag(101);
				zombie->getSprite()->runAction(action);
			}

			zombie->hurtMe(1);
			FlowWord* flowWord = FlowWord::create();
			flowWord->showWord("-1", Vec2(zombie->getSprite()->getPosition().x, zombie->getSprite()->getPosition().y + zombie->getContentSize().height / 2));
			flowWord->gettextLab()->setColor(Color3B(255, 0, 0));
			zombie->setmoveStatus(false);
			zombie->addChild(flowWord);
		}
	}
}

/*玩家跳跃能力*/
void PlayerManager::jumpPlayer()
{
	//设置跳跃
	m_Player->getPhysicsBody()->setVelocity(Vect(150, 500));
}

/*英雄逻辑*/
void PlayerManager::logic()
{
	for (auto zombie : m_zombieVector)
	{
		auto winSize = Director::getInstance()->getWinSize();
		if (zombie->getPositionX() > winSize.width)
		{
			zombie->hurtMe(1000);
		}

		if (zombie->isDead())
		{
			if (zombie->getmoveType() == 1)
			{
				PartiscEx* pe = PartiscEx::create();
				pe->PlayExplosion(zombie->getPosition());
				this->getParent()->addChild(pe, 3);
			}

			zombie->removeFromParentAndCleanup(true);
			m_zombieVector.eraseObject(zombie);
			break;
		}
	}
}