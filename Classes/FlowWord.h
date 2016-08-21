/*
	�ļ�����    FlowWord.h
	�衡����    ����Ʈ��Ч��
	�����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
	*/

#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node {
public:
	CREATE_FUNC(FlowWord);
	virtual bool init();

public:
	void showWord(const char* text, Point pos);
	CC_SYNTHESIZE(Label*, m_textLab, textLab);
};

#endif