#include "Player.h"
#include "PartiscEx.h"
#include "SimpleAudioEngine.h"
#include "AnimoTool.h"
#include "FlowWord.h"
#include "PowerEnum.h"

USING_NS_CC;
using namespace CocosDenshion;

Player::Player(void)
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
	m_iHurtedStatus = false;
	m_ZombieStatus = MonsterStatus::MoveStatus;
	m_DeltaTime = 0.0f;
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

		//绑定sprite到成员函数
		bindSprite(sprite);

		//初始化物理body
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

//初始化物理体
void Player::initPhysicsBody()
{
	auto playerBody = PhysicsBody::createBox(this->getContentSize(),
		PHYSICSBODY_MATERIAL_DEFAULT);
	playerBody->setRotationEnable(false);
	playerBody->getShape(0)->setDensity(1.0f);
	playerBody->getShape(0)->setMass(50);

	//设置物体是否受重力系数影响
	playerBody->setGravityEnable(true);

	playerBody->setCategoryBitmask(2);
	playerBody->setContactTestBitmask(4);
	playerBody->setCollisionBitmask(4);

	this->setPhysicsBody(playerBody);

	//设置标志
	this->setTag(1);
}

//player的移动控制
void Player::movePlayer(int flag)
{
	this->setPosition(this->getPositionX() + m_iSpeed * flag, this->getPositionY());
}

void Player::moveZombie(float dt)
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
			   //zombie运动动画
			   /*	   auto action = AnimoTool::newTypeOneRightMoveAnimotion();
					  action->setTag(100);
					  this->getSprite()->runAction(action);*/

			   //auto jb = JumpBy::create(0.7, Vec2(2, 10), 5, 1);
			   auto mb = MoveBy::create(0.5, Vec3(15, 0, 0));
			   mb->setTag(5);
			   this->runAction(mb);
			   break;
	}
	}
}

void Player::fightSpeedZombie(float dt)
{
	m_DeltaTime += dt;

	if (m_DeltaTime >= 3.0f)
	{
		this->hurtMe(this->gethurtedValue());

		std::string blood = StringUtils::format("%d", this->gethurtedValue());
		FlowWord* flowWord = FlowWord::create();
		flowWord->showWord(blood.c_str(), Vec2(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y + this->getContentSize().height / 2));
		flowWord->gettextLab()->setColor(Color3B(255, 0, 0));
		this->addChild(flowWord);

		m_iHurtedStatus = false;
		m_DeltaTime = 0.0f;
	}

	/*auto callbackFunc = [=]()
	{
	this->getSprite()->stopActionByTag(101);
	};

	CallFunc* callFunc = CallFunc::create(callbackFunc);
	auto action = AnimoTool::newTypeOneAttactAnimotion();
	action->setTag(101);
	this->getSprite()->runAction(Sequence::create(action, callFunc, NULL));*/
}

void Player::updateCallBack(float dt)
{
	switch (getZombieStatus())
	{
	case MoveStatus:
		moveZombie(dt);
		break;
	case FigthStatus:
		this->stopAllActions();
		fightSpeedZombie(dt);
		break;
	case DieStatus:
		break;
	default:
		break;
	}
}