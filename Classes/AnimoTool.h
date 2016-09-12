/*
文件名：AnimoTool.h
描   述：动画类
制作人：周司南
*/

#ifndef _ANIMOTOOL_H_
#define _ANIMOTOOL_H_

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class AnimoTool
{
public:
	AnimoTool(void);
	~AnimoTool(void);

	//主角动画
	static Animate* createAnimation();

	//怪物动画
	static Animate* createMonsterAnimation();

	//boss动画
	static Animate* createBossAnimotion();

	//开场动画
	static Animate* createBeginAnimotion();

	static Animate* newTypeOneAttactAnimotion();
	static Animate* newTypeOneLeftMoveAnimotion();
	static Animate* newTypeOneRightMoveAnimotion();

	static Animate* playerAllAttactAnimotion(std::string str, Rect rect, int iFrameNum);

	static Animate* createMonsterAnimationLEVEL3();

	static Animate* createBoss2Animotion();

	static Animate* createBoss3Animotion();

	static Animate* createMonsterAnimation3();

	static Sequence* clickEffects(Vec2 pt, Size size);
};
#endif