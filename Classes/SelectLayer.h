/*
�ļ�����BeginLayer.h
��   ���� ���ȳ���
�����ˣ� ��˾��
*/

#ifndef ___SelectLayer_H__
#define ___SelectLayer_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class SelectLayer : public Layer
{
public:
	//��ʼ��
	virtual bool init();

	//�ҵĳ�ʼ��
	void loadConfig();

	static Scene* createScene();

	//����create()����
	CREATE_FUNC(SelectLayer);

	//����ѡ�ذ�ť
	void moveToLeft(Ref* sender, TouchEventType type);
	void moveToRight(Ref* sender, TouchEventType type);

	//��ťAB ���ܴ���
	void useAButton(Ref* sender, TouchEventType type);
	void useBButton(Ref* sender, TouchEventType type);

	//����Ϸ����
	void callGameScene(Ref* pSender);

	//����������
	void callAeranaScene(Ref* pSender, TouchEventType type);

	//��ȡ���⼼�ܳ���
	void callHomeScene(Ref* pSender, TouchEventType type);

	//���Գ���
	void callPlayScene(Ref* pSender, TouchEventType type);

	//����ϵͳ
	void callFriendsScene(Ref* pSender, TouchEventType type);

	//��������
	void callBagScene(Ref* pSender, TouchEventType type);

	//���ð�ť
	void callSettingScene(Ref* pSender, TouchEventType type);

private:
	Sprite* m_earth;       //����;
	Sprite* m_sp;
};

#endif