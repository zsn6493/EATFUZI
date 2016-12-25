#include "cocos2d.h"
#include "bossInterface.h"
#include "monsterInterface.h"
USING_NS_CC;

class powerInterface : public Node
{
public:
	virtual ~powerInterface() = 0 {};

	virtual bool getFirePower() = 0;
	virtual void setFirePower(bool firePower) = 0;

	virtual int getBload() = 0;
	virtual void setBload(int bload) = 0;

	virtual int singlePowerkillMonster(Vector<monsterInterface*>* monsterList) = 0;

	virtual int singlePowerkillBoss(bossInterface* boss) = 0;

	virtual int longPowerkillMonster(Vector<monsterInterface*>* monsterList) = 0;

	virtual void singleUpdate(float dt) = 0;

	virtual void longUpdate(float dt) = 0;

	virtual  void simpleAI(Vec2 pPos) = 0;
};
