#ifndef __PartiscEx_H__
#define __PartiscEx_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;

#define NUM_HOLE_MAX	2

class PartiscEx : public Node
{
public:
	virtual bool init();
	//CREATE_FUNC(PartiscEx);

	static PartiscEx* create();

	void PostExplosion();

	void PlayExplosion(CCPoint vPos);

	void updateCallBack(float dt);

protected:
	CCSprite* m_pBg;
	CCSprite* m_pExplosion;
	CCSprite* m_pLight;

	CCSprite* m_pHole[NUM_HOLE_MAX];
	int m_nHoleIndex;

	CCTexture2D* m_pTextureFrame;

	CCParticleSystem* m_SmallParticle;
	CCParticleSystem* m_SmallParticle2;
	CCParticleSystem* m_Smoke;
};

#endif