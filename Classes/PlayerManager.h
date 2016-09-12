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
	static PlayerManager* createWithLevel(Vec2 pt, int level);

	//��ʼ��
	bool init(Vec2 pt, int level);

	//��ȡplayer
	Player* getPlayer();

	//�����ƶ�
	void movePlayer(int flag);

	//���õ�ǰ��������
	void changeStatus(PowerEnumStatus ps);

	//ʹ�ü���
	void usePower();

	//��Ծ
	void jumpPlayer();

	//�жϹ����Ƿ��ܳ�
	int findMonster(Vector<Monster*> monsterList, int flag);

	//��ײ���
	int killMonster(Vector<Monster*>* monsterList);

	//��Ϸ�߼�
	void logic();

	void startPlayerMoveAction();

	void stopPlayerAction();

	void useFZ(Vec2 pt, Vector<Monster*>* monsterList, Boss* boss, bool firePower);

	void useZombie(Vec2 pt, int level);

	void controlAction(float dt);

	CC_SYNTHESIZE(bool, m_BigPower, BigPowerStatus);
	CC_SYNTHESIZE(Vector<Player*>*, m_zombiePtr, zombiePtr);
	CC_SYNTHESIZE(int, m_HurtValue, HurtValue);

private:
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	PowerEnumStatus m_Ps;                       //��������
	Vec2                      m_Origin;                 //��ҳ�ʼ��
	std::string               m_FileName;           //����ð�ռҵĳ�ʼͼƬ��Դ
	Rect                       m_Rect;                  //ͼƬ��Դ����ʾ����
	Vector<Player*> m_zombieVector;
	int m_level;
};

#endif