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
	void changeStatus(CharType ct);

	//ʹ�ü���
	void usePower();

	//��Ծ
	void jumpPlayer();

	//�жϹ����Ƿ��ܳ�
	int findMonster(Vector<Monster*> monsterList, int flag);

	//��ײ���
	int killMonster(Vector<Monster*>* monsterList);

	//��Ϸ�߼�
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
	Player*                  m_Player;                //ð�ռ�
	PlayerPower*        m_Power;                 //����
	CharType               m_CharType;                       //��������
	std::string              m_FileName;           //����ð�ռҵĳ�ʼͼƬ��Դ
	Rect                       m_Rect;                  //ͼƬ��Դ����ʾ����
	Vector<Player*> m_zombieVector;
	int m_level;
};

#endif