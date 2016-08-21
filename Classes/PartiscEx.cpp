#include "PartiscEx.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

#define EXPLOSION_TIME 0.6f

PartiscEx* PartiscEx::create()
{
	PartiscEx *partiscEx = new PartiscEx();
	if (partiscEx && partiscEx->init())
	{
		partiscEx->autorelease();
		return partiscEx;
	}
	CC_SAFE_DELETE(partiscEx);

	return NULL;
}

bool PartiscEx::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		SimpleAudioEngine::sharedEngine()->preloadEffect("Explosion.wav");

		m_pTextureFrame = CCTextureCache::sharedTextureCache()->addImage("ExplosionFrame.png");

		for (int i = 0; i < NUM_HOLE_MAX; i++)
		{
			m_pHole[i] = CCSprite::create("Hole.png");
			m_pHole[i]->setPosition(ccp(size.width / 2, size.height / 2));
			m_pHole[i]->setVisible(false);
			this->addChild(m_pHole[i], 0);
		}
		m_nHoleIndex = 0;

		m_Smoke = CCParticleSystemQuad::create("Smoke.plist");
		m_Smoke->setBlendAdditive(true);
		m_Smoke->stopSystem();
		this->addChild(m_Smoke, 3);

		m_pLight = CCSprite::create("Light.png");
		m_pLight->setPosition(ccp(size.width / 2, size.height / 2));
		m_pLight->setVisible(false);
		m_pLight->setOpacity(180);
		this->addChild(m_pLight, 1);

		m_pExplosion = CCSprite::createWithTexture(m_pTextureFrame, CCRectMake(0, 0, 1, 1));
		m_pExplosion->setScale(3.0f);
		m_pExplosion->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(m_pExplosion, 2);

		m_SmallParticle = CCParticleSystemQuad::create("SmallParticle.plist");
		m_SmallParticle->setBlendAdditive(true);
		m_SmallParticle->stopSystem();
		this->addChild(m_SmallParticle, 3);

		m_SmallParticle2 = CCParticleSystemQuad::create("SmallParticle2.plist");
		m_SmallParticle2->setBlendAdditive(true);
		m_SmallParticle2->stopSystem();
		this->addChild(m_SmallParticle2, 3);

		bRet = true;

		this->scheduleOnce(schedule_selector(PartiscEx::updateCallBack), 0.7f);
	} while (0);

	return bRet;
}

void PartiscEx::PlayExplosion(CCPoint vPos)
{
	m_SmallParticle->setPosition(vPos);
	m_SmallParticle2->setPosition(vPos);
	m_Smoke->setPosition(vPos);
	m_pExplosion->setPosition(vPos);
	m_pLight->setPosition(vPos);

	m_pExplosion->setVisible(true);
	m_pLight->setVisible(false);

	//CCActionInterval* pShake = Shaky3D::create(EXPLOSION_TIME, Size(15, 15), true, 10);
	//this->runAction(pShake);

	m_pExplosion->setScale(3.0f + 3.0f* CCRANDOM_0_1());
	m_pExplosion->setRotation(360.0f*CCRANDOM_0_1());

	m_SmallParticle->resetSystem();
	m_SmallParticle2->resetSystem();
	m_Smoke->resetSystem();

	CCAnimation* animation = CCAnimation::create();
	for (int i = 0; i < 16; i++)
	{
		int row = i / 4;
		int col = i % 4;
		CCRect rect = CCRectMake(col * 64, row * 64, 64, 64);
		animation->addSpriteFrameWithTexture(m_pTextureFrame, rect);
	}
	// should last EXPLOSION_TIME seconds. And there are 16 frames.
	animation->setDelayPerUnit(EXPLOSION_TIME / 16.0f);
	animation->setRestoreOriginalFrame(true);

	CCAnimate* explosionAnimation = CCAnimate::create(animation);
	m_pExplosion->runAction(explosionAnimation);

	float fScaleStart = 1.0f;
	float fScaleEnd = 1.2f;

	m_pLight->setScale(fScaleStart);
	CCActionInterval* pScaleTo1 = CCScaleTo::create(EXPLOSION_TIME / 2, fScaleEnd, fScaleEnd);
	CCActionInterval* pScaleTo2 = CCScaleTo::create(EXPLOSION_TIME / 2, fScaleStart, fScaleStart);
	CCFiniteTimeAction* seq = CCSequence::create(pScaleTo1, pScaleTo2, NULL);
	m_pLight->runAction((CCActionInterval*)seq);

	m_pHole[m_nHoleIndex]->setVisible(true);
	m_pHole[m_nHoleIndex]->setPosition(vPos);
	m_pHole[m_nHoleIndex]->setRotation(CCRANDOM_0_1() * 360);

	float fHoleScale = 0.4f + 0.4f* CCRANDOM_0_1();
	m_pHole[m_nHoleIndex]->setScale(fHoleScale);
	CCActionInterval* pHoleScale = CCScaleTo::create(EXPLOSION_TIME / 2, fHoleScale + 0.2f, fHoleScale + 0.2f);
	CCActionInterval* pEaseHoleScale = CCEaseSineOut::create(pHoleScale);
	m_pHole[m_nHoleIndex]->runAction(pEaseHoleScale);

	m_nHoleIndex = (m_nHoleIndex + 1) % NUM_HOLE_MAX;

	// play sound
	//SimpleAudioEngine::sharedEngine()->playEffect("Explosion.wav");

	CCActionInterval* pDelay = CCDelayTime::create(EXPLOSION_TIME);
	CCActionInstant* pPostExplosion = CCCallFunc::create(this, callfunc_selector(PartiscEx::PostExplosion));

	CCFiniteTimeAction* seq2 = CCSequence::create(pDelay, pPostExplosion, NULL);
	this->runAction(seq2);
}

void PartiscEx::PostExplosion()
{
	m_pExplosion->setVisible(false);
	m_pLight->setVisible(false);
}

void PartiscEx::updateCallBack(float dt)
{
	this->removeFromParentAndCleanup(true);
}