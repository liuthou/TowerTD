#include "ActionsFactory.h"

Animate * ActionsFactory::createAction(std::string fileNameStr, int pictureNum, float delayPerUnit, int loops) {

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	Animation * animation = Animation::create();
	for (int i = 1; i <= pictureNum; i++)
	{
		std::string fileName = StringUtils::format("%s_%02d.png",fileNameStr.c_str(),i);
		auto spriteFrame = spriteFrameCache->getSpriteFrameByName(fileName);
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(delayPerUnit);
	animation->setLoops(loops);
	Animate * animate = Animate::create(animation);

	return animate;
}