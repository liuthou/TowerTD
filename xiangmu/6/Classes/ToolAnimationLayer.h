#ifndef __TOOLANIMATIONLAYER_H_
#define __TOOLANIMATIONLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class ToolAnimationLayer:public Layer{
protected:
	int touchNumber;
public:
	virtual bool init();
	CREATE_FUNC(ToolAnimationLayer);
	void onEnter();
    /**
     *  主角碰撞到小鬼
     */
    void roleHitGost(Ref *sender);
    /**
     *  主角碰到云
     *
     */
    void roleHitColoud(Ref *sender);
    /**
     *  主角碰到石头
     *
     */
    void roleHitBinder(Ref *sender);
    /**
     *  主角碰到大便
     */
    void roleHitShit(Ref *sender);
    /**
     *  主角碰到逗比
     */
    void roleHitdou(Ref *sender);
};
#endif