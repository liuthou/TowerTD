#ifndef _DYNAMICBLOCK_H_
#define _DYNAMICBLOCK_H_
#include "cocos2d.h"
#include "BaseBlock.h"
USING_NS_CC;

class DynamicBlock : public BaseBlock
{
protected:
	virtual bool init(std::string fileNameStr, int pictureNum, float attack, float delayPerUnit, int loops, std::string m_name, Vec2 blockPos);
public:
	static DynamicBlock * create(std::string fileNameStr, int pictureNum, float attack, float delayPerUnit, int loops, std::string m_name, Vec2 blockPos);
};

#endif // !_DYNAMICBLOCK_H_
