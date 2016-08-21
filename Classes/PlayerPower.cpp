#include "PlayerPower.h"
#include "Monster.h"
#include "PartiscEx.h"
#include "FlowWord.h"
#include "Boss.h"
USING_NS_CC;

PlayerPower::PlayerPower(void)
{
	m_power = NULL;
	m_visiable = false;
	m_boom = NULL;
	m_FirePower = false;
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

PlayerPower* PlayerPower::createSp(Sprite* sprite)
{
	PlayerPower *playerPower = new PlayerPower();
	if (playerPower && playerPower->initWithFileSp(sprite))
	{
		playerPower->autorelease();
		return playerPower;
	}
	CC_SAFE_DELETE(playerPower);

	return NULL;
}

bool PlayerPower::initWithFileSp(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		//this->setPosition(sp->getPosition());
		bindSprite(sprite);    //绑定sprite到成员函数
		bRet = true;

		//auto sp = Sprite::create("Arm.png");
		m_Nodegrid = NodeGrid::create();

		this->addChild(m_Nodegrid, 1);
		//this->schedule(schedule_selector(PlayerPower::updateCallBack), 3.0f);

		this->scheduleOnce(schedule_selector(PlayerPower::updateCallBack), 0.7f);
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

bool PlayerPower::initFromCsvFileByID(int iHeroID)
{
	return false;
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

//使用火焰技能
void PlayerPower::useFire(Vec2 vec2)
{
	if (m_visiable == false)
	{
		if (getSprite() == NULL)
		{
			bindSprite(Sprite::create("Fire.png"));
		}
		else
		{
			getSprite()->setVisible(true);
			m_visiable = true;
		}

		this->setAnchorPoint(Vec2(1.0f, 0.5f));
		this->setPosition(Vec2(vec2.x + 20, vec2.y));

		auto Func = [&]()
		{
			getSprite()->setVisible(false);
			m_visiable = false;
		};

		auto mb = MoveBy::create(1.0f, Vec3(800, 0, 0));
		auto callback = CallFunc::create(Func);
		this->runAction(Sequence::create(mb, callback, NULL));
	}
}

//使用怪物技能
void PlayerPower::useMonsterFire(Vec2 vec2, int flag)
{
	if (m_visiable == false)
	{
		bindSprite(Sprite::create("Fire.png"));
		if (flag < 0)
		{
			this->getSprite()->setRotationY(-180.0f);
		}
		else
		{
			this->getSprite()->setRotationY(0.0f);
		}

		getSprite()->setVisible(true);
		m_visiable = true;

		this->setPosition(Vec2(vec2.x + 20 * flag, vec2.y));

		auto Func = [&]()
		{
			getSprite()->setVisible(false);
			m_visiable = false;
		};

		auto mb = MoveBy::create(0.5f, Vec3(400, 0, 0));
		auto callback = CallFunc::create(Func);

		if (flag < 0)
			this->runAction(Sequence::create(mb->reverse(), callback, NULL));
		else
			this->runAction(Sequence::create(mb, callback, NULL));
	}
}

//使用冰冻技能
void PlayerPower::useIce(Vec2 vec2)
{
	if (m_power == NULL)
	{
		m_power = Sprite::create("Fire.png");
		this->addChild(m_power);
		this->setPosition(Vec2(vec2.x + 20, vec2.y));

		auto Func = [&]()
		{
			m_power->removeFromParentAndCleanup(true);
			m_power = NULL;
		};

		auto mb = MoveBy::create(1.0f, Vec3(800, 0, 0));
		auto callback = CallFunc::create(Func);
		m_power->runAction(Sequence::create(mb, callback, NULL));
	}
}

void PlayerPower::useboom(Vec2 vec)
{
	if (m_boom == NULL)
	{
		m_boom = Sprite::create();
		m_boom->setPosition(vec);
		getParent()->addChild(m_boom);

		auto Func1 = [&]()
		{
			m_boom->removeAllChildrenWithCleanup(true);
			m_boom = NULL;
		};

		auto callback = CallFunc::create(Func1);
		m_boom->runAction(Sequence::create(boom, callback, NULL));
	}
}

int PlayerPower::killMonster2(Vector<Monster* >* monsterList)
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
			// 创建一个 Waved3D 动作
			//CCActionInterval* waves = CCWaves::create(18, Size(50, 50), 10, 20, true, true);
			//m_Nodegrid->runAction(waves);
			ms->hurtMe(1);
			FlowWord* fw = FlowWord::create();
			ms->addChild(fw);
			fw->showWord("-12400", Vec2(ms->getSprite()->getPosition().x, ms->getSprite()->getPosition().y + ms->getContentSize().height / 2));
			fw->gettextLab()->setColor(Color3B(255, 0, 0));
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("music/m%d.wav", i % 6).c_str(), false);
		}
	}

	return 0;
}

int PlayerPower::killBoss(Boss* boss)
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

void PlayerPower::update(float dt)
{
	killMonster2(monsterList);

	killBoss(boss);
}