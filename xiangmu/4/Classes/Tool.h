#ifndef __TOOLS__
#define __TOOLS__

#include "cocos2d.h"
using namespace cocos2d;
//道具移动速度
#define TOOLMOVESPEED 50

class Tool : public cocos2d::Sprite
{
protected:
	std::vector<Vec2>vector;

	Size vSize;

	virtual void toolFly() = 0;

public:
	//删除该节点设置死亡标记
	virtual void removeTools();

	CC_SYNTHESIZE(bool,isDie,Die);

	virtual void runAnimation();

	CC_SYNTHESIZE(std::string,fileName,FileName);

	virtual void onEnter();

	virtual bool initWithSpriteFrameName(std::string fileName, Vec2 position);

};

#endif // __HELLOWORLD_SCENE_H__