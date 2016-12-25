/*
	文件名：MonsterManager.h
	描   述：管理怪物创建和逻辑
	制作人：周司南
	*/

#ifndef _MonsterManager_H_
#define _MonsterManager_H_

#include "cocos2d.h"
#include "PlayerPower.h"
#include "Boss.h"
USING_NS_CC;

class Monster;
class MonsterManager : public Node
{
public:
	MonsterManager();
	~MonsterManager();

	static MonsterManager* create(ValueVector monsterPoints, int level);

	//初始化函数
	bool init(ValueVector monsterPoints, int level);

	//逻辑函数
	void logic();

	//保存player
	Vector<Monster*>* getMonsterList();

	//将隐藏的怪物vivsiable
	void visiableMonster();

	//使用技能
	void usePower();

	//判定玩家
	int killPlayer(Player* player);

	int killPlayer(Vector<Player*>* playerList);

	//初始化monster 物理刚体 临时测试
	void initPhysicsBody(Monster* monster);

	void MonsterManager::initMonsterProper(Monster* monster,
		int baseAtk,
		int curAtk,
		int hp,
		int defens,
		int speed,
		int curAtkSpeed);

	void callMonsterIntoMap(float dt);
	void callMonsterIntoMap2(float dt);

	CC_SYNTHESIZE(int, m_MonsterNum, MonsterNum);
	CC_SYNTHESIZE(int, m_DeadMonsterNum, DeadMonsterNum);

	void updateCallback(float dt);

	void MonsterManager::controlAction(float dt);

private:
	ValueVector                 m_monsterPoints;
	Vector<Monster*>        m_monsterList;                  //怪物列表
	Boss*                           m_boss;
	int                                m_level;
};
#endif