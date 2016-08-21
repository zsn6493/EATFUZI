#include "AnimoTool.h"
#include "PowerEnum.h"

AnimoTool::AnimoTool()
{
}
AnimoTool::~AnimoTool()
{
}

Animate* AnimoTool::createAnimation()
{
	int iFrameNum = 10;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("sucai2/hao_%d.png", i), Rect(0, 0, 100, 100));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;

	/*
	CCAnimation *animation = CCAnimation::create();
	//从本地文件系统中加载图片文件到CCSpriteFrame中区，然后添加到CCAnimation中
	for (int i = 1; i < 11; i++)
	{
	char szImageFileName[128] = { 0 };
	sprintf(szImageFileName, "hao_%d.png", i);
	animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(1.4f / 14.0f); // 这个动画包含14帧，将会持续2.8秒.
	animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧

	Animate *action = Animate::create(animation);
	return action;*/
}

Animate* AnimoTool::createMonsterAnimation()
{
	int iFrameNum = 8;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("good_%d.png", i), Rect(0, 0, 200, 200));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;

	/*
	CCAnimation *animation = CCAnimation::create();
	//从本地文件系统中加载图片文件到CCSpriteFrame中区，然后添加到CCAnimation中
	for (int i = 1; i < 11; i++)
	{
	char szImageFileName[128] = { 0 };
	sprintf(szImageFileName, "hao_%d.png", i);
	animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(1.4f / 14.0f); // 这个动画包含14帧，将会持续2.8秒.
	animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧

	Animate *action = Animate::create(animation);
	return action;*/
}

//Boss动画
Animate* AnimoTool::createBossAnimotion()
{
	int iFrameNum = 20;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = iFrameNum; i >= 1; i--)
	{
		frame = SpriteFrame::create(StringUtils::format("boss_ (%d).png", i), Rect(0, 0, 571, 331));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

//Boss动画
Animate* AnimoTool::createBoss2Animotion()
{
	int iFrameNum = 114;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = iFrameNum; i >= 1; i--)
	{
		frame = SpriteFrame::create(StringUtils::format("Boss/Boss_SP (%d).png", i), Rect(0, 0, 220, 300));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::createBoss3Animotion()
{
	int iFrameNum = 26;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = iFrameNum; i >= 1; i--)
	{
		frame = SpriteFrame::create(StringUtils::format("Boss2/Boss_SP2 (%d).png", i), Rect(0, 0, 571, 331));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::createBeginAnimotion()
{
	int iFrameNum = 158;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = iFrameNum; i >= 1; i--)
	{
		frame = SpriteFrame::create(StringUtils::format("one/one (%d).png", i), Rect(0, 0, 1200, 800));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::newTypeOneAttactAnimotion()
{
	int iFrameNum = 5;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create("YIN2/YIN (8).png", Rect(90 * i, 0, 90, 90));
		frameVec.pushBack(frame);
	}
	frame = SpriteFrame::create("YIN2/YIN (7).png", Rect(0, 0, 57, 68));
	frameVec.pushBack(frame);

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::newTypeOneLeftMoveAnimotion()
{
	int iFrameNum = 5;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(NEWTYPE_ONE_LEFT, Rect(66 * i, 0, 66, 74));
		frameVec.pushBack(frame);
	}
	frame = SpriteFrame::create(NEWTYPE_ONE, Rect(0, 0, 57, 68));
	frameVec.pushBack(frame);

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::newTypeOneRightMoveAnimotion()
{
	int iFrameNum = 5;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(NEWTYPE_ONE_RIGHT, Rect(66 * i, 0, 66, 74));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::playerAllAttactAnimotion(std::string str, Rect rect, int iFrameNum)
{
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(str, Rect(rect.size.width * i, 0, rect.size.width, rect.size.height));
		frameVec.pushBack(frame);
	}
	frame = SpriteFrame::create(NEWTYPE_TWO, Rect(0, 0, 45, 57));
	frameVec.pushBack(frame);

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::createMonsterAnimationLEVEL3()
{
	int iFrameNum = 6;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("mj (%d).png", i), Rect(0, 0, 118, 120));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

	auto action = Animate::create(animation);

	return action;
}

Animate* AnimoTool::createMonsterAnimation3()
{
	int iFrameNum = 14;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("JI/JI (%d).png", i), Rect(0, 0, 75, 185));
		frameVec.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

	auto action = Animate::create(animation);

	return action;
}