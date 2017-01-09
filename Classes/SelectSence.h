/*
�ļ�����SelectSence.h
��   �����ؿ�ѡ��
�����ˣ���˾��
*/

#ifndef ___SelectSence_H__
#define ___SelectSence_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

class SelectSence : public Layer
{
public:
	SelectSence();
	~SelectSence();
	//��ʼ��
	virtual bool init();

	//�ҵĳ�ʼ��
	void loadConfig();

	//��������
	static Scene* createScene();

	//����create()����
	CREATE_FUNC(SelectSence);

	//touches ��Ӧ����
	void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	Vec2 setViewPoint();

	//update function
	void update(float delta);

	//����ѡ�񳡾�
	void nextSceneCallback(Ref* pSender);

private:
	Sprite* m_Sp;
	int speed;
	Menu* m_menu;
	Layer* m_ColorLayer;
	int DirX;
	int DirY;
	bool m_Touch;
	float delta;
};
#endif