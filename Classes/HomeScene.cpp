#include "HomeScene.h"
#include "SelectLayer.h"
#include "GamePause.h"
#include "AnimoTool.h"
//#include "ScrollBarTest.h"
#include "ScrollBar.h"
HomeScene::HomeScene()
{
	m_num = 5;
	m_tableView = NULL;
	m_Creating = false;
}

HomeScene::~HomeScene()
{

}

Scene* HomeScene::createScene()
{
	auto scene = Scene::create();

	auto  pLayer = new HomeScene();
	auto pLayer2 = new HomeScene();
	if (pLayer && pLayer->init() && pLayer2 && pLayer2->init2(pLayer2))
	{
		pLayer->autorelease();
		scene->addChild(pLayer, 1);

		pLayer2->autorelease();
		scene->addChild(pLayer, 2);

		return scene;
	}
	else
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}

	return scene;
}

HomeScene* HomeScene::create()
{
	return NULL;
}

bool HomeScene::init()
{
	if (!Layer::init()){
		return false;
	}

	scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sp = Sprite::create("treebk.png");
	       sp->setAnchorPoint(Vec2(0.5, 0.5));
	       sp->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		       origin.y + visibleSize.height / 2));
	this->addChild(sp, 1);

	//添加选择按钮
	auto closeItem2 = MenuItemImage::create(
		   "closenormal.png",
		   "closeselected.png",
		   CC_CALLBACK_1(HomeScene::retMainSence, this));
	       closeItem2->setAnchorPoint(Vec2(0.5, 0.5));
		   closeItem2->setPosition(Vec2(visibleSize.width - closeItem2->getContentSize().width,
		       visibleSize.height / 2));

	auto menu2 = Menu::create(closeItem2, NULL);
	       menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 4);

	auto map = CCTMXTiledMap::create("plante.tmx");
	this->addChild(map, 2);

	//获取地图上player的坐标
	TMXObjectGroup* objGoup = map->getObjectGroup("treeOnes");
	ValueMap playerPointMap = objGoup->getObject("treeOne");

	float treeX = playerPointMap.at("x").asFloat();
	float treeY = playerPointMap.at("y").asFloat();

	auto closeItem = MenuItemImage::create(
		"tree2.png",
		"tree2.png",
		CC_CALLBACK_1(HomeScene::backToTollgateSelectScene, this));
	closeItem->setAnchorPoint(Vec2(0.5, 0.5));
	closeItem->setPosition(Vec2(treeX, treeY + 16));

	treeOnePoint = Vec2(Vec2(treeX, treeY));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	map->addChild(menu, 4);

	m_pBg = Sprite::create("scrollbar/bg_big.png");
	m_pBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
	this->addChild(m_pBg, 2);

	m_pView = Sprite::create("scrollbar/bg_small.png");
	m_pView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
	this->addChild(m_pView, 2);

	auto BoxSize = m_pView->getContentSize();
	auto viewSize = Size(BoxSize.width, BoxSize.height * 0.85);
	//添加标题
	auto plabel = Label::createWithTTF("Call A Hero", "fonts/Marker Felt.ttf", 30);
	plabel->setPosition(Vec2(BoxSize.width / 2, BoxSize.height * 0.9));
	m_pView->addChild(plabel);

	m_tableView = cocos2d::extension::TableView::create(this, viewSize);
	m_tableView->ignoreAnchorPointForPosition(false);
	m_tableView->setAnchorPoint(Vec2(0.5, 0.5));
	m_tableView->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));
	m_tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	m_tableView->reloadData();
	m_pView->addChild(m_tableView, 5);

	auto scrollBar_vr = ScrollBar::create("scrollbar/vr_slider_bg.png", "scrollbar/vr_slider.png", m_tableView, DIR_VERTICAL);
	scrollBar_vr->setPosition(Vec2(viewSize.width, viewSize.height / 2));
	m_pView->addChild(scrollBar_vr, 3);

	auto addBtn = MenuItemFont::create("Add Content", CC_CALLBACK_1(HomeScene::onBtnCallback, this));
	addBtn->setTag(5);
	addBtn->setPosition(Vec2(viewSize.width / 4, viewSize.height + 80));
	addBtn->setScale(0.5);
	addBtn->setColor(Color3B(255, 0, 0));
	auto subBtn = MenuItemFont::create("Sub Content", CC_CALLBACK_1(HomeScene::onBtnCallback, this));
	subBtn->setTag(10);
	subBtn->setPosition(Vec2(viewSize.width / 4 * 3, viewSize.height + 80));
	subBtn->setScale(0.5);
	subBtn->setColor(Color3B(255, 0, 0));
	auto pMenu = Menu::create();
	pMenu->setPosition(Vec2::ZERO);
	m_pView->addChild(pMenu);
	pMenu->addChild(addBtn);
	pMenu->addChild(subBtn);

	m_pView->setVisible(false);
	m_pBg->setVisible(false);
	return true;
}



bool HomeScene::init2(HomeScene* pL)
{
	if (!Layer::init()){
		return false;
	}

	scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sp = Sprite::create("treebk.png");
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	sp->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(sp, 1);

	//添加选择按钮
	auto closeItem2 = MenuItemImage::create(
		"closenormal.png",
		"closeselected.png",
		CC_CALLBACK_1(HomeScene::retMainSence, this));
	closeItem2->setAnchorPoint(Vec2(0.5, 0.5));
	closeItem2->setPosition(Vec2(visibleSize.width - closeItem2->getContentSize().width,
		visibleSize.height / 2));

	auto menu2 = Menu::create(closeItem2, NULL);
	menu2->setPosition(Vec2::ZERO);
	pL->addChild(menu2, 4);

	auto map = CCTMXTiledMap::create("plante.tmx");
	pL->addChild(map, 2);

	//获取地图上player的坐标
	TMXObjectGroup* objGoup = map->getObjectGroup("treeOnes");
	ValueMap playerPointMap = objGoup->getObject("treeOne");

	float treeX = playerPointMap.at("x").asFloat();
	float treeY = playerPointMap.at("y").asFloat();

	auto closeItem = MenuItemImage::create(
		"tree2.png",
		"tree2.png",
		CC_CALLBACK_1(HomeScene::backToTollgateSelectScene, this));
	closeItem->setAnchorPoint(Vec2(0.5, 0.5));
	closeItem->setPosition(Vec2(treeX, treeY + 16));

	treeOnePoint = Vec2(Vec2(treeX, treeY));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	map->addChild(menu, 4);

	m_pBg = Sprite::create("scrollbar/bg_big.png");
	m_pBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
	pL->addChild(m_pBg, 2);

	m_pView = Sprite::create("scrollbar/bg_small.png");
	m_pView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
	pL->addChild(m_pView, 2);

	auto BoxSize = m_pView->getContentSize();
	auto viewSize = Size(BoxSize.width, BoxSize.height * 0.85);
	//添加标题
	auto plabel = Label::createWithTTF("Call A Hero", "fonts/Marker Felt.ttf", 30);
	plabel->setPosition(Vec2(BoxSize.width / 2, BoxSize.height * 0.9));
	m_pView->addChild(plabel);

	m_tableView = cocos2d::extension::TableView::create(pL, viewSize);
	m_tableView->ignoreAnchorPointForPosition(false);
	m_tableView->setAnchorPoint(Vec2(0.5, 0.5));
	m_tableView->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));
	m_tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	m_tableView->reloadData();
	m_pView->addChild(m_tableView, 5);

	auto scrollBar_vr = ScrollBar::create("scrollbar/vr_slider_bg.png", "scrollbar/vr_slider.png", m_tableView, DIR_VERTICAL);
	scrollBar_vr->setPosition(Vec2(viewSize.width, viewSize.height / 2));
	m_pView->addChild(scrollBar_vr, 3);

	auto addBtn = MenuItemFont::create("Add Content", CC_CALLBACK_1(HomeScene::onBtnCallback, this));
	addBtn->setTag(5);
	addBtn->setPosition(Vec2(viewSize.width / 4, viewSize.height + 80));
	addBtn->setScale(0.5);
	addBtn->setColor(Color3B(255, 0, 0));
	auto subBtn = MenuItemFont::create("Sub Content", CC_CALLBACK_1(HomeScene::onBtnCallback, this));
	subBtn->setTag(10);
	subBtn->setPosition(Vec2(viewSize.width / 4 * 3, viewSize.height + 80));
	subBtn->setScale(0.5);
	subBtn->setColor(Color3B(255, 0, 0));
	auto pMenu = Menu::create();
	pMenu->setPosition(Vec2::ZERO);
	m_pView->addChild(pMenu);
	pMenu->addChild(addBtn);
	pMenu->addChild(subBtn);

	m_pView->setVisible(false);
	m_pBg->setVisible(false);
	return true;
}

void HomeScene::backToTollgateSelectScene(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (m_pView->isVisible())
	{
		m_pView->setVisible(false);
		m_pBg->setVisible(false);
	}
	else
	{
		m_pView->setVisible(true);
		m_pBg->setVisible(true);
	}

	/* 3秒后返回关卡选择场景 */
	//this->schedule(schedule_selector(HomeScene::callBackTime), 3.0f);
}

void HomeScene::retMainSence(Ref* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void HomeScene::callBackTime(float dt)
{
	this->unschedule(schedule_selector(HomeScene::callBackTime));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (m_timer)
        m_timer->removeFromParentAndCleanup(true);

	//auto sp = Sprite::create("YIN2/YIN (8).png", Rect(m_TouchIDx % 5 * 90, 0, 90, 90));
	  //     sp->setPosition(treeOnePoint.x, treeOnePoint.y - 16);
	auto sp = Sprite::create(StringUtils::format("Arm%d.png", (m_TouchIDx + 1) % 6));

	sp->setPosition(treeOnePoint.x, treeOnePoint.y - 16);
		   //sp->runAction(AnimoTool::createPlayerLeftMove());
	       this->addChild(sp, 3);
	m_sp.pushBack(sp);
	
	//遍历Game类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	//auto renderTexture = RenderTexture::create(1200, 640);
	     //  renderTexture->begin();
	     //  this->getParent()->visit();
	    //   renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	//CCDirector::sharedDirector()->pushScene(GamePause::createScene(renderTexture, 1));
	//CCDirector::sharedDirector()->pushScene(ScrollBarTest::create());
	m_Creating = false;
}

void HomeScene::update(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (auto sp : m_sp)
	{
		sp->setPositionX(sp->getPosition().x + 1);

		if (sp->getPositionX() > origin.x + visibleSize.width)
		{
			sp->setVisible(false);
		}
	}

	for (auto sp : m_sp)
	{
		if (!sp->isVisible())
		{ 
			m_sp.eraseObject(sp);
			sp->removeFromParentAndCleanup(true);
			break;
		}
	}
}

Size HomeScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(260, 60);
}

TableViewCell* HomeScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	auto cellSize = this->tableCellSizeForIndex(table, idx);
	auto number = __String::createWithFormat("%d", idx + 1);
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}

	//auto pNum = (Label *)cell->getChildByTag(100);
	//pNum->setString(number->getCString());
	cell->removeAllChildrenWithCleanup(true);
	auto pCellBg = Sprite::create("scrollbar/cell.png");
	pCellBg->setPosition(Vec2(cellSize.width / 2, cellSize.height / 2));
	cell->addChild(pCellBg);

	//auto pIcon = Sprite::create("scrollbar/setting.png");
	//auto pIcon = Sprite::create("YIN2/YIN (8).png", Rect(idx % 5 * 90, 0, 90, 90));
	auto pIcon = Sprite::create(StringUtils::format("Arm%d.png", (idx + 1) % 6));
	pIcon->setPosition(Vec2(cellSize.width * 0.85, cellSize.height / 2));
	pIcon->setScale(0.4);
	cell->addChild(pIcon);

	auto pNum = Label::createWithTTF(number->getCString(), "fonts/Marker Felt.ttf", 20);
	pNum->setColor(Color3B(255, 0, 0));
	pNum->setPosition(Vec2(cellSize.width * 0.1, cellSize.height / 2));
	pNum->setTag(100);
	cell->addChild(pNum);

	return cell;
}

ssize_t HomeScene::numberOfCellsInTableView(TableView *table1)
{
	return m_num;
}

void HomeScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	if (m_Creating == false)
	{
		m_TouchIDx = cell->getIdx();
		m_Creating = true;
		m_timer = GameTimer::createTimer(3);
		m_timer->setPosition(Vec2(treeOnePoint.x, treeOnePoint.y + 86));
		this->addChild(m_timer, 15);

		this->schedule(schedule_selector(HomeScene::callBackTime), 3.0f);
	}
}

void HomeScene::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{

}
void HomeScene::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{

}

void HomeScene::onBtnCallback(Ref * obj)
{
	int tag = ((Node *)obj)->getTag();
	if (tag == 5)
	{
		if (m_num < 100)
		{
			m_num++;
			m_tableView->reloadData();
		}
	}
	else
	{
		if (m_num > 2)
		{
			m_num--;
			m_tableView->reloadData();
		}
	}
}