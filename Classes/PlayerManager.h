/*
文件名：PlayerManager.h
描   述： 管理player创建，功能
制作人： 周司南
*/
#ifndef _PlayerManager_H_
#define _PlayerManager_H_

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "PlayerPower.h"
USING_NS_CC;

class Monster;
class PlayerManager : public Node
{
public:
	PlayerManager();
	~PlayerManager();

	//创建create()
	static PlayerManager* createWithLevel(Vec2 pt, int level);

	//初始化
	bool init(Vec2 pt, int level);

	//获取player
	Player* getPlayer();

	//主角移动
	void movePlayer(int flag);

	//设置当前技能类型
	void changeStatus(CharType ct);

	//使用技能
	void usePower();

	//跳跃
	void jumpPlayer();

	//判断怪物是否能吃
	int findMonster(Vector<Monster*> monsterList, int flag);

	//碰撞检测
	int killMonster(Vector<Monster*>* monsterList);

	//游戏逻辑
	void logic(float dt);

	void runPlayerDeadPower(Player* zombie);

	void startPlayerMoveAction();

	void stopPlayerAction();

	void useSinglePower(Vec2 pt, Vector<Monster*>* monsterList, Boss* boss, bool firePower);

	void useLongPower(Vec2 pt, Vector<Monster*>* monsterList, Boss* boss);

	void useZombie(Vec2 pt, int level);

	void controlAction(float dt);

	void setZombieColor(int index, Player* zombie);

	BezierTo* bezierAction(Vec2 first, Vec2 last, int radian);

	void initPlayerPic(CharType charType);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);
	CC_SYNTHESIZE(int, m_HurtValue, HurtValue);
	CC_SYNTHESIZE(Vec2, m_Origin, OriginPoint);

private:
	Player*                  m_Player;                //冒险家
	PlayerPower*        m_Power;                 //技能
	CharType               m_CharType;                       //技能类型
	std::string              m_FileName;           //创建冒险家的初始图片资源
	Rect                       m_Rect;                  //图片资源的显示区域
	Vector<Player*> m_zombieVector;
	int m_level;
};

#endif