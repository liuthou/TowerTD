#ifndef __TOOL_H
#define __TOOL_H
#include "cocos2d.h"
using namespace cocos2d;
class Tool:public Sprite{
protected:
	void cleanfrom(float t);
public:
	CC_SYNTHESIZE_READONLY(int, type, Type);
	//type = 1 表示加血 type = 2表示炸弹
	virtual bool init(int type);
	static Tool * create(int type);

};
#endif