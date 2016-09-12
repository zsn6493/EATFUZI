/*
	�ļ�����ShowSence.h
	��   ���� ����Ϸ����
	�����ˣ� ��˾��
	*/
#ifndef ___ShowSence_H__
#define ___ShowSence_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "BossManager.h"
#include "GodArmManager.h"
#include "Boss.h"

USING_NS_CC;

class ShowLayer : public Layer
{
public:
	ShowLayer();
	~ShowLayer();

	virtual void onEnter() override;

	bool init(int level);

	//�ҵĳ�ʼ��
	void loadConfig(int level);

	//��ʼ���������
	void initPhyscsObject(Rect* m);

	//�˳��ص�
	void menuCloseCallback(cocos2d::Ref* pSender);

	//������playerΪ����
	Point setViewPoint();

	//�ƶ�player
	void movePlayer(int flag);

	static ShowLayer* create(int level);

	//ʹ�ü���
	void usePlayerPower();

	//ʹ�ô���
	void usePlayerBigPower();

	//��ȡ����ļ���
	void parseMonsterPower(int flag);

	//��������
	void retBeginLayer();

	//��Ծ
	void jumpPlayer();

	//�߼�
	void logic(float dt);

	//Boss�߼�
	void Bosslogic(float dt);

	//�����߼�
	void Monsterlogic(float dt);

	//�����ƶ�����
	void movePlayerAnimotion();

	//ֹͣ���ﶯ��
	void stopPlayerAnimotion();

	//ʹ�ü���
	void useFZPower(Vec2 pt);

	//ʹ��zombie
	void useZombie(int level);

	CC_SYNTHESIZE(bool, m_FirePower, FirePower);
	CC_SYNTHESIZE(int, m_Rand, Rand);
	CC_SYNTHESIZE(PhysicsWorld*, m_World, World);
	//void removeJoint();

private:
	PlayerManager*       m_PlayerManager;     //���
	MonsterManager*    m_MonsterManager;  // ����
	BossManager*         m_BossManager;       //Boss
	GodArmManager*    m_GodArmManager;     //���
	TMXTiledMap*         m_Map;         //��ͼ
	Rect m_Rect;
	Boss* m_Boss;                           //Boss
	int m_MaxLength;                      //��ͼ���ֵ
	int m_MinLength;                       //��ͼ������Сֵ
	int m_Level;                               //��ͼlevel
	//PhysicsJointDistance* m_Joint; ������
};
#endif