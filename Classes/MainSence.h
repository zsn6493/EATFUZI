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

	static MainSence*  create(int level, ShowLayer* showLayer);

	//��ʼ��
	bool init(int level, ShowLayer* showLayer);

	void OnEnter();

	void update(float dt);

	//���ĺ���GameWin
	void killedMonsterNum(Ref* pData);

	//���ĺ���GameOver
	void recvGameOver(Ref* pData);

	//���ĺ�����������
	void recvChangeBK(Ref* pData);

	//����ɱ����
	void deNum(Ref* pData);

	//�߼�
	void logic(float dt);

	//���ñ�������Ϸ�ӽ�
	void setViewPoint();

	//ɱ����
	CC_SYNTHESIZE(int, m_Num, DeNum);

	//�洢��ǰ����
	CC_SYNTHESIZE(Scene*, m_oriScene, OriScene);

private:
	Layer*  m_BK;                   //������
	int        m_level;                        //����ѡ��
	ShowLayer* m_viewLayer; //��ͼ��
	Layer*         m_moveLayer;        //�ƶ�����
	Label*         m_Label;        //ɱ����Label
};
#endif // ___MAINSENCE_H__