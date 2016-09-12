/*
�ļ�����AnimoTool.h
��   ����������
�����ˣ���˾��
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

	//���Ƕ���
	static Animate* createAnimation();

	//���ﶯ��
	static Animate* createMonsterAnimation();

	//boss����
	static Animate* createBossAnimotion();

	//��������
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