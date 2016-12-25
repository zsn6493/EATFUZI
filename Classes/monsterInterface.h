#include "cocos2d.h"
USING_NS_CC;

class monsterInterface
{
public:
	virtual ~monsterInterface() = 0 {};

	virtual  void simpleAI(Vec2 pPos) = 0;
};
