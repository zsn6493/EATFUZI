#include "Player.h"
#include "PartiscEx.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"

USING_NS_CC;
using namespace CocosDenshion;

Player::Player(void)
{
	m_speed = 10;   //初始化速度为10
	m_startMoveAction = false;
	m_startFightAciton = false;
}

Player::~Player(void)
{
	this->unscheduleAllCallbacks();
}

Player* Player::create(Sprite* sprite)
{
	Player *player = new Player();
	if (player && player->initWithFile(sprite))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);

	return NULL;
}

Player* Player::createFromCsvFileByID(int iHeroID)
{
	Player* player = new Player();
	if (player && player->initFromCsvFileByID(iHeroID))
	{
		player->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(player);
	}
	return player;
}

bool Player::initWithFile(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);          //绑定sprite到成员函数

		initPhysicsBody();          //初始化物理body

		bRet = true;
	} while (0);

	return bRet;
}

//初始化物理体
void Player::initPhysicsBody()
{
	auto playerBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerBody->setRotationEnable(false);
	playerBody->getShape(0)->setDensity(1.0f);
	playerBody->getShape(0)->setMass(50);

	//设置物体是否受重力系数影响
	playerBody->setGravityEnable(true);

	playerBody->setCategoryBitmask(2);
	playerBody->setContactTestBitmask(4);
	playerBody->setCollisionBitmask(4);

	this->setPhysicsBody(playerBody);

	this->schedule(schedule_selector(Player::updateCallBack), 0.05f);
	//设置标志
	this->setTag(1);
}

bool Player::initFromCsvFileByID(int iHeroID)
{
	return false;
}

//player的移动控制
void Player::movePlayer(int flag)
{
	this->setPosition(this->getPositionX() + m_speed * flag, this->getPositionY());
}

void Player::moveZombie(float dt)
{
	if (this->getmoveType() == 1)
	{
		if (this->isDead())
		{
			PartiscEx* pe = PartiscEx::create();
			pe->PlayExplosion(this->getPosition());
			this->getParent()->addChild(pe, 3);
			return;
		}

		auto jb = JumpBy::create(0.5, Vec2(1, 20), 1, 1);
		jb->setTag(5);
		this->runAction(jb);
	}
	else if (this->getmoveType() == 2)
	{
		auto mb = MoveBy::create(0.5, Vec3(10, 0, 0));
		this->runAction(mb);
	}
	else if (this->getmoveType() == 3)
	{
		auto mb = MoveBy::create(2, Vec3(4, 0, 0));
		auto rb = RotateBy::create(0.5, 360);
		auto action = Spawn::create(rb, mb, NULL);
		this->runAction(action);
	}
	else if (this->getmoveType() == 4)
	{
	}
	else
	{
		//auto jb = JumpBy::create(0.7, Vec2(2, 10), 5, 1);
		auto mb = MoveBy::create(0.5, Vec3(10, 0, 0));
		mb->setTag(5);
		this->runAction(mb);
	}
}

void Player::updateCallBack(float dt)
{
}