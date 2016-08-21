#include "envir.h"

Envir::Envir(void)
{
}

Envir::~Envir(void)
{
	this->unscheduleAllCallbacks();
}

Envir* Envir::create(Sprite* sprite)
{
	Envir *envir = new Envir();
	if (envir && envir->initWithFile(sprite))
	{
		envir->autorelease();
		return envir;
	}
	CC_SAFE_DELETE(envir);

	return NULL;
}

Envir* Envir::createFromCsvFileByID(int iHeroID)
{
	Envir* envir = new Envir();
	if (envir && envir->initFromCsvFileByID(iHeroID))
	{
		envir->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(envir);
	}
	return envir;
}

bool Envir::initWithFile(Sprite* sprite)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);          //绑定sprite到成员函数

		bRet = true;
	} while (0);

	return bRet;
}

bool Envir::initFromCsvFileByID(int iHeroID)
{
	return false;
}