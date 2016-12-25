#include "zombie.h"
#include "PartiscEx.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"

USING_NS_CC;
using namespace CocosDenshion;

Zombie::Zombie(void)
{
	m_BattleName = "";
	m_PepLevel = 0;
	m_startMoveAction = false;
	m_startFightAciton = false;
	m_iBaseAtk = 1;
	m_iCurAtk = 1;
	m_iHP = 1;
	m_iCurAtk = 1;
	m_iHP = 1;
	m_iDefens = 1;
	m_iSpeed = 1;
	m_iCurAtkSpeed = 1;
}

Zombie::~Zombie(void)
{
	this->unscheduleAllCallbacks();
}

Zombie* Zombie::create(Sprite* sprite)
{
	Zombie* zombie = new Zombie();
	if (zombie && zombie->init(sprite))
	{
		zombie->autorelease();
		return zombie;
	}

	CC_SAFE_DELETE(zombie);

	return NULL;
}

bool Zombie::init(Sprite* sprite)
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

void Zombie::setSpecialName(std::string battleName)
{
	m_BattleName = battleName;
	auto label = Label::createWithTTF(m_BattleName, "fonts/Marker Felt.ttf", 28);
	label->setPosition(this->getContentSize().width / 2, this->getContentSize().height + 20);
	this->addChild(label);
}

//��ʼ��������
void Zombie::initPhysicsBody()
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

	//���ñ�־
	this->setTag(1);
}

void Zombie::moveZombie(float dt)
{
	int moveType = this->getmoveType();
	switch (moveType)
	{
	case 1:
	{
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
	{
			   //auto jb = JumpBy::create(0.7, Vec2(2, 10), 5, 1);
			   auto mb = MoveBy::create(0.5, Vec3(15, 0, 0));
			   mb->setTag(5);
			   this->runAction(mb);
			   break;
	}
	}
}

void Zombie::updateCallBack(float dt)
{
}