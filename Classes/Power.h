/*
	文件名：Power.h
	描   述： 技能基类
	制作人： 周司南
	*/
#ifndef _PPower_H_
#define _PPower_H_

#include "cocos2d.h"
USING_NS_CC;

class PPower : public Node
{
public:
	PPower();
	~PPower();

	//绑定Sprite到成员m_sprite
	void bindSprite(Sprite* sprite);

	//获取Sprite
	Sprite* getSprite();

	//被攻击
	void hurtMe(int iHurtValue);

	//清理m_sprite
	void cleanSprite();

private:
	Sprite* m_sprite;                                                    //保存sprite
};

#endif