#pragma once

#include "Psoul.h"
#include "cocos2d.h"
USING_NS_CC;

class Envir : public PSoul
{
public:
	Envir(void);
	~Envir(void);

	//创建player
	static Envir* create(Sprite* sprite);

	//csv创建player
	static Envir* createFromCsvFileByID(int iHeroID);

	//以图片初始化
	virtual bool initWithFile(Sprite* sprite);

	//以csv初始化
	bool  initFromCsvFileByID(int iHeroID);
};