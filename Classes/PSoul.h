/*
文件名：PSoul.h
描   述： 任务和怪物的基类
制作人： 周司南
*/
#ifndef _PSoul_H_
#define _PSoul_H_

#include "cocos2d.h"
USING_NS_CC;

class PSoul : public Node
{
public:
	PSoul();
	~PSoul();

	//绑定Sprite到成员m_sprite
	void bindSprite(Sprite* sprite);

	//获取Sprite
	Sprite* getSprite();

	//被攻击
	void hurtMe(int iHurtValue);

	//是否死亡
	bool isDead();

	//清理Sprite
	void cleanSprite();

protected:
	virtual void onDead();		                                        //实体死亡时调用
	virtual void onBindSprite();                                      // 绑定精灵对象时调用
	virtual void onHurt(int iHurtValue);                            //受伤害时调用

private:
	Sprite* m_sprite;                                                    //保存sprite
	bool m_isDead;                                                     //标记是否死亡

	CC_SYNTHESIZE(int, m_ID, ID);	                        //实体ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);	    //模型ID（资源ID）
	CC_SYNTHESIZE(std::string, m_sName, sName);	//名字
	CC_SYNTHESIZE(int, m_iHP, iHP);			                //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);	        //防御
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);		        //移动速度
	CC_SYNTHESIZE(int, m_iLevel, iLevel);	            	//等级
};

#endif