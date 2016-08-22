#include "GodArm.h"

GodArm::GodArm(void)
{
}

GodArm::~GodArm(void)
{
}

GodArm* GodArm::create(int type)
{
	GodArm *godArm = new GodArm();
	if (godArm && godArm->initWithFile(type))
	{
		godArm->autorelease();
		return godArm;
	}
	CC_SAFE_DELETE(godArm);

	return NULL;
}

bool GodArm::initWithFile(int type)
{
	return true;
}

int GodArm::runPower()
{
	return 20;
}