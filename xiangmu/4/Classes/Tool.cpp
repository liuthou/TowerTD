#include "Tool.h"
#include "ShareFunc.h"
bool Tool::initWithSpriteFrameName(std::string fileName, Vec2 position) {
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	vSize = Director::getInstance()->getVisibleSize();
	this->setFileName(fileName);
	this->setPosition(position);
	this->isDie = false;
	Vec2 v1(CCRANDOM_0_1()*(vSize.width-this->getContentSize().width)+this->getContentSize().width/2,CCRANDOM_0_1()*(vSize.height-this->getContentSize().height)+this->getContentSize().height/2);
	vector.push_back(v1);
	Vec2 v2(CCRANDOM_0_1()*(vSize.width-this->getContentSize().width)+this->getContentSize().width/2,CCRANDOM_0_1()*(vSize.height-this->getContentSize().height)+this->getContentSize().height/2);
	vector.push_back(v2);
	Vec2 v3(CCRANDOM_0_1()*(vSize.width-this->getContentSize().width)+this->getContentSize().width/2,CCRANDOM_0_1()*(vSize.height-this->getContentSize().height)+this->getContentSize().height/2);
	vector.push_back(v3);
	Vec2 v4(CCRANDOM_0_1()*(vSize.width-this->getContentSize().width)+this->getContentSize().width/2,CCRANDOM_0_1()*(vSize.height-this->getContentSize().height)+this->getContentSize().height/2);
	vector.push_back(v4);
	Vec2 v5(CCRANDOM_0_1()*(vSize.width-this->getContentSize().width)+this->getContentSize().width/2,CCRANDOM_0_1()*(vSize.height-this->getContentSize().height)+this->getContentSize().height/2);
	vector.push_back(v5);
	
	return true;
}

void Tool::onEnter(){

	Sprite::onEnter();

	toolFly();

	runAnimation();


}

void Tool::runAnimation() {

	auto moveto = MoveTo::create((this->getPosition()).distance(vector.at(0))/TOOLMOVESPEED,vector.at(0));
	auto moveto2 = MoveTo::create((vector.at(0)).distance(vector.at(1))/TOOLMOVESPEED,vector.at(1));
	auto moveto3 = MoveTo::create((vector.at(1)).distance(vector.at(2))/TOOLMOVESPEED,vector.at(2));
	auto moveto4 = MoveTo::create((vector.at(2)).distance(vector.at(3))/TOOLMOVESPEED,vector.at(3));
	auto moveto5 = MoveTo::create((vector.at(3)).distance(vector.at(4))/TOOLMOVESPEED,vector.at(4));
	auto cf = CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(moveto,moveto2,moveto3,moveto4,moveto5,cf,NULL));
}

void Tool::removeTools() {
	this->setDie(true);
	this->removeFromParentAndCleanup(true);
}

