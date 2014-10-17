#include "DynamicBlock.h"
#include "ActionsFactory.h"
#include "GameData.h"

bool DynamicBlock::init(std::string fileNameStr, int pictureNum, float attack, float delayPerUnit, int loops, std::string m_name, Vec2 blockPos){
	std::string m_fileName = StringUtils::format("%s_%02d", fileNameStr.c_str(), 1);
	if (!BaseBlock::init(m_fileName, attack, m_name, blockPos))
	{
		return false;
	}
	this->runAction(ActionsFactory::createAction(fileNameStr,pictureNum,delayPerUnit,loops));
	return true;
}

DynamicBlock * DynamicBlock::create(std::string fileNameStr, int pictureNum, float attack, float delayPerUnit, int loops, std::string m_name, Vec2 blockPos){
	DynamicBlock * dBlock = new DynamicBlock();
	if (dBlock && dBlock->init(fileNameStr, pictureNum, attack, delayPerUnit, loops, m_name, blockPos))
	{
		dBlock->autorelease();
		return dBlock;
	}
	CC_SAFE_DELETE(dBlock);
	return nullptr;
}