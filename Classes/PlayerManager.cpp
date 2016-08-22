#include "PlayerManager.h"
#include "MonsterManager.h"
#include "PowerEnum.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include "PartiscEx.h"

PlayerManager::PlayerManager()
{
	m_Ps = PowerEnumStatus::useNone;
	m_Power = NULL;
	m_Destflag = 1;
	m_PlayerTimes = 1;
	m_IsFighting = false;
	m_Deadcount = 0;
	m_BigPower = false;
	m_HurtValue = 1;
}

PlayerManager::~PlayerManager()
{
}

/*创建英雄*/
PlayerManager* PlayerManager::createWithLevel(Vec2 pt, int level)
{
	PlayerManager* heroMgr = new PlayerManager();
	if (heroMgr && heroMgr->initWithLevel(pt, level))
	{
		heroMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(heroMgr);
	}

	return heroMgr;
}

/*初始化*/
bool PlayerManager::initWithLevel(Vec2 pt, int level)
{
	m_Origin = pt;
	m_level = level;

	//模拟默认类型
	m_Ps = PowerEnumStatus::useNone;

	//判断人物类型 关联不同资源
	switch (m_Ps)
	{
	case useNone:
		m_FileName = NEWTYPE_ONE;
		m_Rect = NEWTYPE_ONE_RECT;
		break;
	case useFire:
		m_FileName = FIRE_MONSTER;
		m_Rect = FIRE_MONSTER_RECT;
		break;
	case useIce:
		m_FileName = JUMP_MONSTER;
		m_Rect = JUMP_MONSTER_RECT;
		break;
	case useNewTypeOne:
		m_FileName = NEWTYPE_TWO;
		m_Rect = NEWTYPE_TWO_RECT;
		break;
	case useNewTypeTwo:
		m_FileName = NEWTYPE_ONE;
		m_Rect = NEWTYPE_ONE_RECT;
		break;
	}

	//创建player
	m_Player = Player::create(Sprite::create(m_FileName, m_Rect));
	m_Player->setAnchorPoint(Vec2(0.5, 0.5));
	m_Player->setPosition(Vec2(pt.x + m_Player->getContentSize().width / 2, pt.y + m_Player->getContentSize().height / 2));
	this->addChild(m_Player, 5);

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
	if (m_Ps == PowerEnumStatus::useNone)
	{
		auto right = AnimoTool::newTypeOneRightMoveAnimotion();
		m_Player->getSprite()->runAction(right);
	}
	else if (m_Ps == useNewTypeTwo)
	{
	}
}

void PlayerManager::stopPlayerAction()
{
	if (m_Ps == PowerEnumStatus::useNone)
	{
		m_Player->getSprite()->stopAllActions();
		m_Player->bindSprite(Sprite::create(m_FileName, m_Rect));
	}
}

/*移动player*/
void PlayerManager::movePlayer(int flag)
{
	if (m_Player->getPositionX() - m_Player->getContentSize().width / 2 <= 0 && flag == -1)
	{
		m_Player->setPositionX(m_Player->getContentSize().width / 2);
	}
	else  if (m_Player->getPositionX() + m_Player->getContentSize().width / 2 >= 1600 && flag == 1)
	{
		m_Player->setPositionX(1600 - m_Player->getContentSize().width / 2);
	}
	else
	{
		if (m_Destflag != flag && flag != 0)
		{
			if (flag < 0)
				m_Player->setRotationY(-180);
			else
				m_Player->setRotationY(0);
		}

		if (flag != 0)
			this->m_Destflag = flag;

		m_Player->movePlayer(flag);
	}

	return;
}

/*获取英雄*/
Player* PlayerManager::getPlayer()
{
	return this->m_Player;
}

void PlayerManager::useFZ(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss, bool firePower)
{
	auto power = PlayerPower::createSp(Sprite::create("Arm4.png"));
	auto winSize = Director::getInstance()->getWinSize();

	power->setFirePower(firePower);
	power->setAnchorPoint(Vec2(0.5f, 0.5f));

	Vec2 playerPt = getPlayer()->getPosition();

	power->setPosition(Vec2(playerPt.x, playerPt.y - 50));
	//auto Pmb = MoveBy::create(0.2f, Vec2(0, winSize.height - playerPt.y + 100));
	auto rb = RotateBy::create(0.5f, 360 * 2);
	//auto rb2 = RotateBy::create(0.2f, 360 * 2 + 270);
	//auto Pmb2 = MoveBy::create(0.2f, Vec2(pt.x - playerPt.x, 0));
	//auto mb = MoveBy::create(0.2f, Vec2(0, -winSize.height + 70));

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

	//power->runAction(Sequence::create(Spawn::create(Pmb, rb, NULL), Spawn::create(Pmb2, rb, NULL), Spawn::create(mb, rb2, NULL), NULL));
	power->runAction(Spawn::create(bezierTo, rb, NULL));
	power->monsterList = monsterList;

	power->boss = boss;

	this->addChild(power);
}

void PlayerManager::useZombie(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss, int level)
{
	auto zombie = Player::create(Sprite::create(m_FileName, m_Rect));
	auto winSize = Director::getInstance()->getWinSize();

	zombie->setAnchorPoint(Vec2(0.5f, 0.5f));
	Vec2 playerPt = getPlayer()->getPosition();
	zombie->setPosition(playerPt);
	int r = rand() % level;
	if (r == 1)
	{
		zombie->getSprite()->setColor(Color3B(0, 255, 255)); //0,255,255 255,215,0 218,165,32
	}
	else if (r == 2)
	{
		zombie->getSprite()->setColor(Color3B(75, 0, 130));
		zombie->setScale(2.0f);
	}
	else if (r == 3)
	{
		zombie->getSprite()->setColor(Color3B(255, 215, 0));
	}
	else if (r == 4)
	{
		zombie->getSprite()->setColor(Color3B(218, 165, 32));
	}
	else if (r == 5)
	{
		zombie->getSprite()->setColor(Color3B(255, 0, 0));
	}

	zombie->setmoveType(r);

	zombie->setiHP(100);

	this->addChild(zombie);

	m_zombieVector.pushBack(zombie);
}

/*改变技能类型*/
void PlayerManager::changeStatus(PowerEnumStatus ps)
{
	this->m_Ps = ps;
	this->m_Power->cleanSprite();
}

/*碰撞检测*/
int PlayerManager::killMonster(Vector<Monster*>* monsterList)
{
	for (auto py : m_zombieVector)
	{
		Rect mrect = py->boundingBox();
		for (auto ms : *monsterList)
		{
			//float h = sqrt((py->getPosition().x - ms->getPosition().x)*(py->getPosition().x - ms->getPosition().x) + (py->getPosition().y - ms->getPosition().y)*(py->getPosition().y - ms->getPosition().y));
			//float bz = sqrt((py->getContentSize().width / 2 + ms->getContentSize().width / 2) * (py->getContentSize().width / 2 + ms->getContentSize().width / 2) + (py->getContentSize().height / 2 + ms->getContentSize().height / 2) * (py->getContentSize().height / 2 + ms->getContentSize().height / 2));

			float bzX = py->getContentSize().width / 2 + ms->getContentSize().width / 2;
			float bzY = py->getContentSize().height / 2 + ms->getContentSize().height / 2;

			float bz = sqrt(bzX * bzX + bzY * bzY);

			float reX = py->getPosition().x - ms->getPosition().x;
			float reY = py->getPosition().y - ms->getPosition().y;

			float h = sqrt(reX * reX + reY * reY);

			if (h < bz)
			{
				py->setmoveStatus(false);
				ms->setAcceptBlood(CCRANDOM_0_1() * this->getHurtValue());
			}
			else
			{
				py->setmoveStatus(true);
			}
			/*
			Rect rect = ms->boundingBox();
			if (rect.containsPoint(py->getPosition())
			|| rect.containsPoint(Vec2(py->getPosition().x + py->getContentSize().width / 2, py->getPosition().y)))
			{
			// 创建一个 Waved3D 动作
			//CCActionInterval* waves = CCWaves::create(18, Size(50, 50), 10, 20, true, true);
			//m_Nodegrid->runAction(waves);
			//ms->hurtMe(1);
			//py->hurtMe(1);
			//FlowWord* fw = FlowWord::create();
			//ms->addChild(fw);
			//fw->showWord("-12400", Vec2(ms->getSprite()->getPosition().x, ms->getSprite()->getPosition().y + ms->getContentSize().height / 2));
			//fw->gettextLab()->setColor(Color3B(255, 0, 0));
			//ms->getPhysicsBody()->setVelocity(Vect(100, 0));

			//FlowWord* fw2 = FlowWord::create();
			//fw2->showWord("-1", Vec2(py->getSprite()->getPosition().x, py->getSprite()->getPosition().y + py->getContentSize().height / 2));
			//fw2->gettextLab()->setColor(Color3B(255, 0, 0));
			//py->getPhysicsBody()->setVelocity(Vect(-100, 0));
			py->setmoveStatus(false);

			//py->addChild(fw2);

			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("music/m%d.wav", i % 6).c_str(), false);
			}
			else
			{
			py->setmoveStatus(true);
			}*/
		}
	}

	return 0;
}

void PlayerManager::controlAction(float dt)
{
	for (auto py : m_zombieVector)
	{
		if (py->getmoveStatus())
		{
			py->scheduleOnce(schedule_selector(Player::moveZombie), 0.2f);

			if (py->getstartMoveAction() == false)
			{
				py->setstartMoveAction(true);
				py->setstartFightAciton(false);
				py->getSprite()->stopActionByTag(101);
				auto action = AnimoTool::newTypeOneRightMoveAnimotion();
				action->setTag(100);
				py->getSprite()->runAction(action);
			}
		}
		else
		{
			if (py->getstartFightAciton() == false)
			{
				py->setstartFightAciton(true);
				py->setstartMoveAction(false);
				py->getSprite()->stopActionByTag(100);
				auto action = AnimoTool::newTypeOneAttactAnimotion();
				action->setTag(101);
				py->getSprite()->runAction(action);
			}

			py->hurtMe(1);
			FlowWord* fw2 = FlowWord::create();
			fw2->showWord("-1", Vec2(py->getSprite()->getPosition().x, py->getSprite()->getPosition().y + py->getContentSize().height / 2));
			fw2->gettextLab()->setColor(Color3B(255, 0, 0));
			//py->getPhysicsBody()->setVelocity(Vect(-100, 0));
			py->setmoveStatus(false);

			py->addChild(fw2);
		}
	}
}

/*玩家跳跃能力*/
void PlayerManager::jumpPlayer()
{
	//设置跳跃
	m_Player->getPhysicsBody()->setVelocity(Vect(150 * m_Destflag, 500));
}

/*英雄逻辑*/
void PlayerManager::logic(int  mapLength, int MinLength, int MaxLength)
{
	for (auto py : m_zombieVector)
	{
		auto winSize = Director::getInstance()->getWinSize();
		if (py->getPositionX() > winSize.width)
		{
			py->hurtMe(1000);
		}

		if (py->isDead())
		{
			if (py->getmoveType() == 1)
			{
				PartiscEx* pe = PartiscEx::create();
				pe->PlayExplosion(py->getPosition());
				this->getParent()->addChild(pe, 3);
			}

			py->removeFromParentAndCleanup(true);
			m_zombieVector.eraseObject(py);
			break;
		}
	}
}