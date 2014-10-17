#include "ScoreLayer.h"
#include "BaseEnemy.h"
USING_NS_CC;
//积分显示
void ScoreLayer::viewScore(Ref *sender){
	auto enemy = static_cast<BaseEnemy *>(sender);
	_isScore += enemy->getScore();
	label->setString(StringUtils::format("%d",getnowScore()));
}
//创建暂停按钮
void ScoreLayer::createPause(){
	
}

void ScoreLayer::deleteProps(Ref *){
	int i = nowTools.size();
	auto sp = nowTools.at(i-1);
	sp->removeFromParentAndCleanup(true);
	nowTools.pop_back();
}

//道具显示
void ScoreLayer::viewprops(Ref *){
	if (nowTools.size() > 4)
	{
		return;
	}
	int i = nowTools.size();
	if (i == 0)
	{
		Sprite * sp = Sprite::createWithSpriteFrameName("Bomb.png");
		nowTools.push_back(sp);
		sp->setPosition(50,550);
		this->addChild(sp);
	}
	else
	{
		auto sprite = nowTools.at(i - 1);
		Sprite * sp = Sprite::createWithSpriteFrameName("Bomb.png");
		nowTools.push_back(sp);
		sp->setPosition(sprite->getPositionX() + 50, sprite->getPositionY());
		this->addChild(sp);

	}
	
	
}

bool ScoreLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	_isScore = 0;
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this,callfuncO_selector(ScoreLayer::viewScore),"EnemyDie",nullptr);
	center->addObserver(this,callfuncO_selector(ScoreLayer::viewprops),"ToolsPeng",nullptr);
	center->addObserver(this,callfuncO_selector(ScoreLayer::deleteProps),"ToolsDelete",nullptr);
	this->setnowScore(0);
	return true;
}
void ScoreLayer::onEnter(){
	Layer::onEnter();
	label = Label::createWithTTF("00","fonts/Marker Felt.ttf",30);
	label->setPosition(100,600);
	this->addChild(label);
	for (int i = 1;i <= 2;i ++)
	{
		Sprite *sp = Sprite::createWithSpriteFrameName("Bomb.png");
		sp->setPosition(50*i ,550);
		this->addChild(sp);
		nowTools.push_back(sp);
	}
	
}
int ScoreLayer::getvectornumber(){
	return nowTools.size();
}
ScoreLayer::~ScoreLayer()
{
	__NotificationCenter::getInstance()->removeAllObservers(this);
}