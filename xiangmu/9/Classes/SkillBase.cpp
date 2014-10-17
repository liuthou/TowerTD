#include "SkillBase.h"
#include "GameMainScene.h"
#include "HeroLayer.h"

bool SkillBase::init(std::string name, Vec2 skillPoint)
{
	if(!Sprite::initWithSpriteFrameName(name)){
	     return false;
	}
	//设置技能的位置
	this->setPosition(skillPoint);
	//获得正在运行的场景
	GameMainScene * gameMainScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	//获得场景中猪脚的层
	HeroLayer * heroLayer = dynamic_cast<HeroLayer *>(gameMainScene->getHeroLayer());
	//将本身贴到猪脚层上
	heroLayer->addChild(this);
	return true;
}
