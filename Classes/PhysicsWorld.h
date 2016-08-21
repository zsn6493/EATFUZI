/*
文件名：PhyscisWorld.h
描   述： 管理物理世界
制作人： 周司南
*/
#ifndef _PhyscisWorld_H_
#define _PhyscisWorld_H_

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class PhyscisWorld : public Layer
{
public:
	PhyscisWorld(void);
	~PhyscisWorld(void);

	//创建物理BOX
	static PhyscisWorld* create(TMXTiledMap* map);

	static bool createWorld(TMXTiledMap* map, int level);

	bool init(TMXTiledMap* map);

	static void  initPhyscsObject(Rect* m, TMXTiledMap* map);

	static Sprite* makeBall(Vec2 point, float radius, PhysicsMaterial material);
};
#endif  //_PhyscisWorld_H_