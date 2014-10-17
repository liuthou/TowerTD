#include "ShareFunc.h"
#include "GameScene.h"
#include "Hero_SwordPlay.h"


ActionInterval * ShareFunc::getAct(std::string fileName, int begin, int count, float time, int loop)
{
	std::string fileNameFirst;
	fileName = fileName.substr(0, fileName.find_last_of(".") - 1);
	Animation * ani = Animation::create();
	for (int i = begin; i <= count; i++)
	{
		fileNameFirst = fileName + std::to_string(i) + ".png";
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileNameFirst);
		ani->addSpriteFrame(spriteFrame);
	}
	ani->setDelayPerUnit(time);
	ani->setLoops(loop);
	return Animate::create(ani);
}

bool ShareFunc::isFileName(std::string fileName){

	std::string fileNameString(fileName);

	if (fileNameString.empty())
	{
		return true;
	}
	return false;
	
}

GameScene* ShareFunc::getGameScene(){
	return dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
}


