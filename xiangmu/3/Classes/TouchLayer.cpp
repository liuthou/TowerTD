#include "TouchLayer.h"
#include "MapLayer.h"
#include "MainScene.h"
#include "EntityManager.h"
#include "FormatUtil.h"
#include "TowerAttribute.h"
#include "TowerAttributeConfType.h"
#include "PowerfulTower.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool TouchLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void TouchLayer::onEnter(){
	Layer::onEnter();
	initTowerButton();
}

bool TouchLayer::onTouchBegan(Touch *touch, Event *unused_event){
	Vec2 tmptouchposition = towerbuttonlayer->convertToNodeSpace(touch->getLocation());
	for (auto it = towerbutton.begin();it<towerbutton.end();it++)
	{
		Sprite* tmpsprite = *it;
		if (tmpsprite->getBoundingBox().containsPoint(tmptouchposition))
		{
			//得到一个用于拖动的临时精灵并贴到touchlayer上
			tmpsp = Sprite::createWithSpriteFrame(tmpsprite->getSpriteFrame());
			tmpsp->setPosition(touch->getLocation());
			//通过临时精灵传递塔的id
			tmpsp->setTag(tmpsprite->getTag());
			this->addChild(tmpsp);
			return true;
		}
	}
	//格式化工具按钮
	if (formatbutton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		tmpsp = Sprite::createWithSpriteFrame(formatbutton->getSpriteFrame());
		tmpsp->setPosition(touch->getLocation());
		//通过临时精灵传递塔的id
		tmpsp->setName("formatdata");
		this->addChild(tmpsp);
		return true;
	}

	return false;
}
void TouchLayer::onTouchMoved(Touch *touch, Event *unused_event){
	if (tmpsp)
	{
		tmpsp->setPosition(tmpsp->getPosition()+touch->getDelta());
	}
}
void TouchLayer::onTouchEnded(Touch *touch, Event *unused_event){
	//转换坐标并创建塔
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = mScene->getMapLayer();
	auto gamelayer = mScene->getGameLayer();
	Vec2 positiononmap = mapLayer->convertVisiblePositionToTilesPosition(touch->getPreviousLocation());
	Vec2 towerposition = mapLayer->convertTilesPositionToVisiblePosition(positiononmap);


	if (tmpsp)
	{
		int towerid = tmpsp->getTag();
		if (towerid>0)
		{
			Tower* tower;
			//4号塔是超级塔
			if (towerid == 4)
			{
				tower = PowerfulTower::create(towerid);
			}else
			{
				tower = Tower::create(towerid);
			}
			//如果不能放塔,直接返回
			tower->setPosition(towerposition.x+tower->getContentSize().width/2,towerposition.y-tower->getContentSize().height/2);
			//如果这个位置没有塔,没有怪,并且扣分成功,才能放塔.
			if (mapLayer->hasTower(tower->getPosition())&&!EntityManager::getInstance()->checkhasEntity(tower)&&spendMoney(tower->getPrice()))
			{
				gamelayer->addChild(tower);
				EntityManager::getInstance()->TowerVector.pushBack(tower);
				mapLayer->changeGID(tower->getPosition());
			}
		}
		//放格式化工具
		std::string tmpstring = tmpsp->getName();
		if (tmpstring=="formatdata")
		{
			auto formatdata = FormatUtil::create();
			//绑定爆炸回调函数
			auto instance = EntityManager::getInstance();
			formatdata->setExplodeFunc(CC_CALLBACK_1(EntityManager::formatData,instance));
			formatdata->setPosition(towerposition.x+formatdata->getContentSize().width/2,towerposition.y-formatdata->getContentSize().height/2-2);
			if (mapLayer->hasTower(formatdata->getPosition())&&spendMoney(formatdata->getPrice()))
			{
				////爆炸音效//////////////////////////////////////////////////////////////////////
				SimpleAudioEngine::getInstance()->playEffect("Boom.wav");
				gamelayer->addChild(formatdata);
			}
		}
		tmpsp->removeFromParent();
		tmpsp=nullptr;
	}
}

void TouchLayer::setPstate(){
	Pstate = true;
}

bool TouchLayer::spendMoney(int money){
	return cutscore(money);
}

void TouchLayer::initTowerButton(){
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 size = Director::getInstance()->getVisibleSize();
	std::string tmp_price;
	//添加到放按钮的层
	towerbuttonlayer = Layer::create();
	this->addChild(towerbuttonlayer);
	//设置放塔按钮的层的位置
	towerbuttonlayer->setPosition(origin.x+14,origin.y+size.y*(1.0f/8.0f));
	towerbuttonlayer->setContentSize(Size(64,size.y*(3.0f/4.0f)));
	//添加炸弹按钮
	formatbutton = Sprite::create("bomb.png");
	//炸弹价格标签
	tmp_price = StringUtils::format("%dkb/s",FORMATUTILPRICE);
	TTFConfig priceconfig("FZZHYFW.TTF",35);
	priceconfig.distanceFieldEnabled = true;
	auto formatprice = Label::createWithTTF(priceconfig,tmp_price);
	formatprice->enableGlow(Color4B::GREEN);
	formatprice->setTextColor(Color4B::BLUE);

	Vec2 towerbuttonlayerorigin = towerbuttonlayer->getPosition();
	Size towerbuttonlayersize = towerbuttonlayer->getContentSize();
	formatbutton->setPosition(towerbuttonlayerorigin.x+towerbuttonlayersize.width/2,towerbuttonlayerorigin.y+towerbuttonlayersize.height+10);
	formatprice->setAnchorPoint(Vec2(0.5,0.5));
	formatprice->setPosition(formatbutton->getPosition().x,formatbutton->getPosition().y-formatbutton->getContentSize().height/2-formatprice->getContentSize().height/2-5);
	this->addChild(formatbutton);
	this->addChild(formatprice);
	//应该修改TowerAttribute,在getInstance()中不能传id.....不过至少有一个塔吧
	int towercount = TowerAttribute::getInstance(1)->getTowersCount();

	for (int i = 0;i<towercount;i++)
	{
		std::string tmp_picname = StringUtils::format("towe%d.png",i+1);
		//添加放塔按钮
		Sprite* tower = Sprite::create(tmp_picname);
		//tag就是塔在xml中的id
		tower->setTag(i+1);
		towerbutton.pushBack(tower);
	}
	//计算两个按钮之间的间距
	float buttonspace = size.y*(3.0f/4.0f)/(towerbutton.size()+1);
	//向towerbuttonlayer层中添加button
	for (int i=0;i<towerbutton.size();i++)
	{
		Sprite* tmpsprite = towerbutton.at(i);
		Size tmpsize = tmpsprite->getContentSize();
		tmpsprite->setScale(1.2);
//		tmpsprite->setContentSize(tmpsprite->getContentSize()*1.2);
		tmpsprite->setPosition(tmpsize.width/2,towerbuttonlayer->getContentSize().height-buttonspace*(i+1));
		tmp_price = StringUtils::format("%dkb/s",TowerAttribute::getInstance(tmpsprite->getTag())->getIntAttribute(Tower_Price,0));
		TTFConfig priceconfig("FZZHYFW.TTF",35);
		priceconfig.distanceFieldEnabled = true;
		auto towerprice = Label::createWithTTF(priceconfig,tmp_price);
		towerprice->enableGlow(Color4B::GREEN);
		towerprice->setTextColor(Color4B::BLUE);
		towerprice->setAnchorPoint(Vec2(0.5,0.5));
		towerprice->setPosition(tmpsprite->getPosition().x,tmpsprite->getPosition().y-tmpsprite->getContentSize().height/2-tmpsprite->getContentSize().height/2-5);
		towerbuttonlayer->addChild(towerprice);
		towerbuttonlayer->addChild(tmpsprite);
	}
}
////////////////////////////////////////////////////////////////////////////////////////
 void TouchLayer::setTouchStop(bool isStop){
	 if (isStop==true) {
		 Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
	 }
	 if(isStop==false){
		 Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
	 }
 }

void TouchLayer::setCutScore(std::function<bool(int)> cutscore){
	this->cutscore=cutscore;
}