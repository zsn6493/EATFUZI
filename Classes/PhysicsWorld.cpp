#include "PhysicsWorld.h"

int ball1Mask = 1 << 0;    //球1
int ball2Mask = 1 << 1;    //球2
int wallMask = 1 << 2;     //地面

PhyscisWorld::PhyscisWorld()
{
}

PhyscisWorld::~PhyscisWorld()
{
}

/*
Sprite* PhyscisWorld::createPhyscis()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
Size visibleSize = Director::getInstance()->getVisibleSize();
Point origin = Director::getInstance()->getVisibleOrigin();

auto edgeSpace = Sprite::create();
PhysicsBody* boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
boundBody->getShape(0)->setFriction(0.0f);
boundBody->getShape(0)->setRestitution(1.0f);

edgeSpace->setPhysicsBody(boundBody);
edgeSpace->setAnchorPoint(Vec2(0.5f, 0.5f));
edgeSpace->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
edgeSpace->setTag(0);

boundBody->setCategoryBitmask(wallMask);
boundBody->setCollisionBitmask(wallMask | ball1Mask | ball2Mask);
boundBody->setContactTestBitmask(wallMask | ball1Mask | ball2Mask);

return edgeSpace;
#endif
}*/

PhyscisWorld* PhyscisWorld::create(TMXTiledMap* map)
{
	PhyscisWorld *cLayer = new PhyscisWorld();
	if (cLayer && cLayer->init(map))
	{
		cLayer->autorelease();
		return cLayer;
	}
	CC_SAFE_DELETE(cLayer);
	return NULL;
}

bool PhyscisWorld::init(TMXTiledMap* map)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

	/*
	//创建跳板和障碍
	TMXObjectGroup* jobjGoup = map->getObjectGroup("jumpobj");
	Rect mrect[100];
	int currentRectCount;
	ValueMap tm;
	String str;
	for (currentRectCount = 0; currentRectCount < 50; currentRectCount++)
	{
	str = StringUtils::format("t%d", currentRectCount + 1);
	tm = jobjGoup->getObject(str.getCString());
	mrect[currentRectCount] = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

	if (currentRectCount > 38)
	break;
	}

	//创建地面
	TMXObjectGroup* eobjGoup = map->getObjectGroup("up");
	int count = 1;
	for (int i = currentRectCount; i < 50; i++)
	{
	str = StringUtils::format("earth%d", count++);
	ValueMap up = eobjGoup->getObject(str.getCString());
	mrect[i] = Rect(up.at("x").asFloat(), up.at("y").asFloat(), up.at("width").asFloat(), up.at("height").asFloat());

	if (count > 4)
	break;
	}

	initPhyscsObject(mrect, map);*/

	return true;
#endif
}

void PhyscisWorld::initPhyscsObject(Rect* m, TMXTiledMap* map)
{
	for (int i = 0; i < 30; i++)
	{
		Sprite* sp = Sprite::create();
		auto maskLayer = LayerColor::create(Color4B(0, 0, 255, 200));
		maskLayer->setContentSize(m[i].size);
		maskLayer->setAnchorPoint(Vec2(0, 0));
		sp->addChild(maskLayer, 15);

		PhysicsBody* playerBody = PhysicsBody::createBox(m[i].size, PHYSICSBODY_MATERIAL_DEFAULT);

		playerBody->setDynamic(false);

		//设置质量
		playerBody->getShape(0)->setMass(100);

		//设置物体是否受重力系数影响
		playerBody->setGravityEnable(false);

		sp->setContentSize(m[i].size);
		sp->setPosition(Vec2(m[i].getMidX(), m[i].getMidY()));
		sp->setAnchorPoint(Vec2(0.0, 0.0));
		sp->setPhysicsBody(playerBody);

		map->addChild(sp);
	}
}

//New Code 创建物理环境
bool  PhyscisWorld::createWorld(TMXTiledMap* map, int level)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

	if (level == 0)
	{
		TMXObjectGroup* mobjGoup = map->getObjectGroup("earth_obj");
		ValueMap earthPoint = mobjGoup->getObject("earth");

		Rect rect = Rect(earthPoint.at("x").asFloat(), earthPoint.at("y").asFloat(), earthPoint.at("width").asFloat(), earthPoint.at("height").asFloat());

		Sprite* sp = Sprite::create();

		PhysicsBody* playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);

		playerBody->setDynamic(false);

		//设置质量
		playerBody->getShape(0)->setMass(100);

		//设置物体是否受重力系数影响
		playerBody->setGravityEnable(false);

		sp->setContentSize(rect.size);
		sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
		sp->setAnchorPoint(Vec2(0.5, 0.5));
		sp->setPhysicsBody(playerBody);

		map->addChild(sp);
	}
	else if (level == 1)
	{
		//创建跳板和障碍
		TMXObjectGroup* jobjGoup = map->getObjectGroup("jumpobj");
		ValueVector ar = jobjGoup->getObjects();
		for (auto arnum : ar)
		{
			ValueMap tm = arnum.asValueMap();
			Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

			auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
			playerBody->setDynamic(false);
			//设置质量
			playerBody->getShape(0)->setMass(100);
			//设置物体是否受重力系数影响
			playerBody->setGravityEnable(false);

			auto sp = Sprite::create();
			sp->setContentSize(rect.size);
			sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
			sp->setAnchorPoint(Vec2(0.0, 0.0));
			sp->setPhysicsBody(playerBody);

			auto maskLayer = LayerColor::create(Color4B(0, 0, 255, 200));
			maskLayer->setContentSize(rect.size);
			maskLayer->setAnchorPoint(Vec2(0, 0));
			sp->addChild(maskLayer, 15);

			map->addChild(sp);
		}

		TMXObjectGroup* mobjGoup = map->getObjectGroup("up");
		ValueVector er = mobjGoup->getObjects();
		for (auto ernum : er)
		{
			ValueMap   tm = ernum.asValueMap();
			Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

			auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
			playerBody->setDynamic(false);
			//设置质量
			playerBody->getShape(0)->setMass(100);
			//设置物体是否受重力系数影响
			playerBody->setGravityEnable(false);

			auto sp = Sprite::create();
			sp->setContentSize(rect.size);
			sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
			sp->setAnchorPoint(Vec2(0.0, 0.0));
			sp->setPhysicsBody(playerBody);

			auto maskLayer = LayerColor::create(Color4B(0, 0, 255, 200));
			maskLayer->setContentSize(rect.size);
			maskLayer->setAnchorPoint(Vec2(0, 0));
			sp->addChild(maskLayer, 15);

			map->addChild(sp);
		}
	}
	else if (level == 2)
	{
		TMXObjectGroup* mobjGoup = map->getObjectGroup("earth1");
		ValueVector er = mobjGoup->getObjects();
		for (auto ernum : er)
		{
			ValueMap tm = ernum.asValueMap();
			Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

			auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
			playerBody->setDynamic(false);
			//设置质量
			playerBody->getShape(0)->setMass(100);
			//设置物体是否受重力系数影响
			playerBody->setGravityEnable(false);

			auto sp = Sprite::create();
			sp->setContentSize(rect.size);
			sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
			sp->setAnchorPoint(Vec2(0.0, 0.0));
			sp->setPhysicsBody(playerBody);
			map->addChild(sp);
		}
	}
	else if (level == 3)
	{
		TMXObjectGroup* mobjGoup = map->getObjectGroup("earth_obj");
		ValueVector er = mobjGoup->getObjects();
		for (auto ernum : er)
		{
			ValueMap tm = ernum.asValueMap();
			Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

			auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
			playerBody->setDynamic(false);
			//设置质量
			playerBody->getShape(0)->setMass(100);
			//设置物体是否受重力系数影响
			playerBody->setGravityEnable(false);

			auto sp = Sprite::create();
			sp->setContentSize(rect.size);
			sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
			sp->setAnchorPoint(Vec2(0.5, 0.5));
			sp->setPhysicsBody(playerBody);
			map->addChild(sp);
		}
	}
	else if (level == 4)
	{
		TMXObjectGroup* mobjGoup = map->getObjectGroup("earth_obj");
		ValueVector er = mobjGoup->getObjects();
		for (auto ernum : er)
		{
			ValueMap tm = ernum.asValueMap();
			Rect rect = Rect(tm.at("x").asFloat(), tm.at("y").asFloat(), tm.at("width").asFloat(), tm.at("height").asFloat());

			auto playerBody = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
			playerBody->setDynamic(false);
			//设置质量
			playerBody->getShape(0)->setMass(100);
			//设置物体是否受重力系数影响
			playerBody->setGravityEnable(false);

			auto sp = Sprite::create();
			sp->setContentSize(rect.size);
			sp->setPosition(Vec2(rect.getMidX(), rect.getMidY()));
			sp->setAnchorPoint(Vec2(0.0, 0.0));
			sp->setPhysicsBody(playerBody);
			map->addChild(sp);
		}
	}

	return true;
#endif
}