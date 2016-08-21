/*
�ļ�����PlayerPower.h
��   ���� ���Ǽ���
�����ˣ� ��˾��
*/
#ifndef _PlayerPower_H_
#define _PlayerPower_H_

#include "Power.h"
#include "Player.h"
#include "cocos2d.h"
#include "AnimoTool.h"
USING_NS_CC;
class Monster;
class Boss;
class PlayerPower : public PPower
{
public:
	PlayerPower(void);
	~PlayerPower(void);

	//����player
	static PlayerPower* create(Node* node);

	//csv����player
	static PlayerPower* createFromCsvFileByID(int iHeroID);

	//��ͼƬ��ʼ��
	virtual bool initWithFile(Node* node);

	//��csv��ʼ��
	bool  initFromCsvFileByID(int iHeroID);

	//����
	void useFire(Vec2 vec2);

	//������
	void useIce(Vec2 vec2);

	//boom��Ч��������
	void useboom(Vec2 vec);

	//����ʹ�û���
	void useMonsterFire(Vec2 vec2, int flag);

	bool m_visiable;                          //������Ƿ������

	bool initWithFileSp(Sprite* sp);

	static PlayerPower* createSp(Sprite* sprite);

	void updateCallBack(float dt);

	int killMonster2(Vector<Monster*>* monsterList);

	virtual void update(float dt);

	Vector<Monster*>* monsterList;

	Boss* boss;

	CC_SYNTHESIZE(bool, m_FirePower, FirePower);

	int killBoss(Boss* boss);

private:
	Sprite* m_power;                        //����ͼƬ��Դ
	Animate* boom;                          //��ը��Ч����
	Sprite* m_boom;                         //��ը��Դ
	NodeGrid* m_Nodegrid;
};
#endif