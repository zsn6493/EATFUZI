#pragma once

#include "Psoul.h"
#include "cocos2d.h"
USING_NS_CC;

class Envir : public PSoul
{
public:
	Envir(void);
	~Envir(void);

	//����player
	static Envir* create(Sprite* sprite);

	//csv����player
	static Envir* createFromCsvFileByID(int iHeroID);

	//��ͼƬ��ʼ��
	virtual bool initWithFile(Sprite* sprite);

	//��csv��ʼ��
	bool  initFromCsvFileByID(int iHeroID);
};