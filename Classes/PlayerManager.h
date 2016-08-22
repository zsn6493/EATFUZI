/*
�ļ�����PlayerManager.h
��   ���� ����player����������
�����ˣ� ��˾��
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

	//����create()
	static PlayerManager* createWithLevel(Vec2 pt);

	//��ʼ��
	bool initWithLevel(Vec2 pt);

	//����create()
	static PlayerManager* createWithLevel(Vec2 pt, int level);

	//��ʼ��
	bool initWithLevel(Vec2 pt, int level);

	//��ȡplayer
	Player* getPlayer();

	//�����ƶ�
	void movePlayer(int flag);

	//���õ�ǰ��������
	void changeStatus(PowerEnumStatus ps);

	//�Թ���
	int eatMonster();

	//ʹ�ü���
	void usePower();

	//ʹ�û��漼��
	void useFirePower();

	//��Ծ
	void jumpPlayer();

	//�жϹ����Ƿ��ܳ�
	int findMonster(Vector<Monster*> monsterList, int flag);

	//��ײ���
	int killMonster(Vector<Monster*>* monsterList);

	//��Ϸ�߼�
	void logic(int mapLength, int MinLength, int MaxLength);

	void startPlayerMoveAction();

	void stopPlayerAction();

	void useBasePower();

	bool m_IsFighting;

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);
	CC_SYNTHESIZE(int, m_HurtValue, HurtValue);

	void useBigPower(Vector<Monster*>* monsterList, int level);

	void useBigPowerCallBack(float dt);

	void useFZ(Vec2 pt, Vector<Monster*>* monsterList, Boss* boss, bool firePower);

	void useZombie(Vec2 pt, Vector<Monster* >* monsterList, Boss* boss, int level);

	void PlayerManager::controlAction(float dt);

private:
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	Monster*               m_FindMonster;        //̽�⵽�Ĺ���
	PowerEnumStatus m_Ps;                       //��������
	Vec2                      m_Origin;                 //��ҳ�ʼ��
	int                          m_Destflag;             //ð�ռ�֮ǰ�ķ���
	int                          m_PlayerTimes;       //�����������ʱ��
	std::string               m_FileName;           //����ð�ռҵĳ�ʼͼƬ��Դ
	Rect                       m_Rect;                  //ͼƬ��Դ����ʾ����
	int                          m_Deadcount;
	Vector<Player*> m_zombieVector;
	int m_level;
};

#endif