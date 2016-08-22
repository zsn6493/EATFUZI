#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GodArm : public Node
{
public:
	GodArm(void);
	~GodArm(void);

	static GodArm* create(int type);
	bool initWithFile(int type);

	int GodArm::runPower();
};