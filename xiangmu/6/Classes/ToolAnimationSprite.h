#ifndef __TOOLANIMATIONSPRITE_H_
#define __TOOLANIMATIONSPRITE_H_
#include "cocos2d.h"
#include "ToolsBaseScript.h"
#define FAZHEN1 1
#define FAZHEN2 2
#define FAZHEN3 3
#define FAZHEN4 4
#define FAZHEN5 5
#define FAZHEN6 6
#define BINDBOOM 7
using namespace cocos2d;
class ToolAnimationSprite:public Sprite{
protected:
	int m_id;
public:
	virtual bool init(std::string fileName,int t_id);
	static ToolAnimationSprite * create(std::string fileName,int t_id);
	void onEnter();
    void changeRoleState1();
};
#endif