/*
�ļ�����ControlLayer.h
��   ����ControlLayer ���Ʋ� ����UI ������Ļ�źŽ���
�����ˣ���˾��
*/
#ifndef ___CONTROLLAYER_H__
#define ___CONTROLLAYER_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "cocostudio\CocoStudio.h"
#include "Player.h"
#include "Monster.h"
#include "ShowLayer.h"
USING_NS_CC;

using namespace cocostudio;
using namespace cocos2d::ui;

class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer();
	~ControlLayer();

	//��������
	static cocos2d::Scene* createScene();

	//����ͼ��
	static ControlLayer* create(Layer* layer);

	//��ʼ����layer����
	bool init(Layer* layer);

	//������Դ
	void loadConfig();

	//�رհ�ť�Ļص�
	void menuCloseCallback(Ref* sender, TouchEventType type);

	//ð����ʹ�ü��ܻص�
	void userPowerCallback(Ref* sender, TouchEventType type);

	//ð���߻�ȡ���ܻص�
	void eatMonsterCallback(Ref* sender, TouchEventType type);

	//ð������Ծ���ܻص�
	void useJumpCallback(Ref* sender, TouchEventType type);

	//ð����ʹ�ô��лص�
	void userBigPowerCallback(Ref* sender, TouchEventType type);

	//ð�������ƶ��ص�
	void moveToLeft(Ref* sender, TouchEventType type);

	//ð�������ƶ��ص�
	void moveToRight(Ref* sender, TouchEventType type);

	//����ѡ�����ӿ�
	void gameOverCallback(Ref* pSender);

	//ʹ�ü���
	void usePower1(Ref* pSender);

	//touches ��Ӧ����
	void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	//void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	//update function
	void update(float delta);

	//����
	Action* MoveLeft;

	//����
	Action* MoveRight;

	//��������
	void updatelongprogress(float ft);

	//���㴦��
	void updateSingleDelay(float ft);

	//˫������
	void updateDoubleDelay(float ft);

	//��ȡ��ǰ���ʱ�̵�ʱ���
	long long getCurrentTime();

	//������������
	void usePowerUp(Ref* pSender);

	//���＼������
	void usePeoUp(Ref* pSender);
private:
	ShowLayer* m_viewLayer;                	//��Ϸ��ͼ��
	int m_flag;                                            //�ƶ������ʶ
	int m_Num[100];
	int m_Count;
	bool m_longProgress;                           //����״̬��ʶ
	Vec2 m_startPoint;
	Vec2 m_endPoint;
	long long m_startTime;
};

#endif // ___CONTROLLAYER_H__