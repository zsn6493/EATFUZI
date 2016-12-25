/*
�ļ�����MainSence.h
��   ����������Ϸ����
�����ˣ���˾��
*/

#ifndef ___MAINSENCE_H__
#define ___MAINSENCE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ShowLayer.h"
USING_NS_CC;

class MainSence : public Layer
{
public:
	MainSence();
	~MainSence();

	//��������
	static cocos2d::Scene* createScene(int level);

	static MainSence*  create(int level);

	//��ʼ��
	bool init(int level);

	void OnEnter();

	void update(float dt);

	//���ĺ���GameOver
	void recvGameOver(Ref* pData);

	//���ĺ�����������
	void recvChangeBK(Ref* pData);

	//���ĵĵ���
	void deNum(Ref* pData);

	//��õĵ���
	void increNum(Ref* pData);

	//ɱ����
	CC_SYNTHESIZE(int, m_KillMonsterNum, KillMonsterNum);

	//�洢��ǰ����
	CC_SYNTHESIZE(Scene*, m_oriScene, OriScene);

private:
	int        m_level;                        //����ѡ��ѡ��
	Label*  m_Label;                       //ɱ����Label
	Layer*  m_BackGrandLayer;    //������
};
#endif // ___MAINSENCE_H__