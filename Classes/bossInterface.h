#include "cocos2d.h"
#include "PowerEnum.h"
USING_NS_CC;

class bossInterface : public Node
{
public:
	virtual ~bossInterface() = 0 {};

	virtual CharType getCharType() = 0;
	virtual void setCharType(CharType charType) = 0;

	virtual Vec2 getOrigin() = 0;
	virtual void setOrigin(Vec2 vec2) = 0;

	virtual  void simpleAI(Vec2 pPos) = 0;
};