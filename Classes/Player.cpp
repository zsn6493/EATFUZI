#include "Player.h"
#include "PartiscEx.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"

USING_NS_CC;
using namespace CocosDenshion;

Player::Player(void)
{
	m_BattleName = "";
	m_PepLevel = 0;
}

Player::~Player(void)
{
	this->unscheduleAllCallbacks();
}

Player* Player::create(Sprite* sprite)
{
	Player *player = new Player();
	if (player && player->init(sprite))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);

	return NULL;
}

bool Player::init(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);

		//��sprite����Ա����
		bindSprite(sprite);

		//��ʼ������body
		initPhysicsBody();

		bRet = true;
	} while (0);

	return bRet;
}

void Player::setSpecialName(std::string battleName)
{
	m_BattleName = battleName;
	auto label = Label::createWithTTF(m_BattleName, "fonts/Marker Felt.ttf", 28);
	label->setPosition(this->getContentSize().width / 2, this->getContentSize().height + 20);
	this->addChild(label);
}

//��ʼ��������
void Player::initPhysicsBody()
{
	auto playerBody = PhysicsBody::createBox(this->getContentSize(),
		PHYSICSBODY_MATERIAL_DEFAULT);
	playerBody->setRotationEnable(false);
	playerBody->getShape(0)->setDensity(1.0f);
	playerBody->getShape(0)->setMass(50);

	//���������Ƿ�������ϵ��Ӱ��
	playerBody->setGravityEnable(true);

	playerBody->setCategoryBitmask(2);
	playerBody->setContactTestBitmask(4);
	playerBody->setCollisionBitmask(4);

	this->setPhysicsBody(playerBody);

	this->schedule(schedule_selector(Player::updateCallBack), 0.05f);
	//���ñ�־
	this->setTag(1);
}

//player���ƶ�����
void Player::movePlayer(int flag)
{
	this->setPosition(this->getPositionX() + m_speed * flag, this->getPositionY());
}

void Player::moveZombie(float dt)
{
	int moveType = this->getmoveType();
	switch (moveType)
	{
	case 1:
	{
			  if (this->isDead())
			  {
				  PartiscEx* pe = PartiscEx::create();
				  pe->PlayExplosion(this->getPosition());
				  this->getParent()->addChild(pe, 3);
				  return;
			  }

			  auto jumpBy = JumpBy::create(0.5, Vec2(1, 20), 1, 1);
			  jumpBy->setTag(5);
			  this->runAction(jumpBy);
			  break;
	}
	case 2:
	{
			  auto mb = MoveBy::create(0.5, Vec3(10, 0, 0));
			  this->runAction(mb);
			  break;
	}
	case 3:
	{
			  auto mb = MoveBy::create(2, Vec3(4, 0, 0));
			  auto rb = RotateBy::create(0.5, 360);
			  auto action = Spawn::create(rb, mb, NULL);
			  this->runAction(action);
			  break;
	}
	case 4:
	{
			  break;
	}
	default:
	{		  //auto jb = JumpBy::create(0.7, Vec2(2, 10), 5, 1);
			   auto mb = MoveBy::create(0.5, Vec3(10, 0, 0));
			   mb->setTag(5);
			   this->runAction(mb);
			   break;
	}
	}
}

void Player::updateCallBack(float dt)
{
}