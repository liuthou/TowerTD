//
//  BroadcastLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-23.
//
//

#ifndef __heroJump__BroadcastLayer__
#define __heroJump__BroadcastLayer__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;
class BroadcastLayer :public Layer{
private:
    /**
     *  检测用户使用的道具和主角碰撞
     */
    void checkUseTools(float ft);

    /**
     *  检测场景中的道具和主角碰撞
     */
    void checkTools(float ft);

	/**
	 *  检测道具与猪脚的碰撞
	 */
	void checkToolsChangeRoleState(float ft);
public:
    virtual bool init();
    CREATE_FUNC(BroadcastLayer);
    virtual void update(float ft);
    
};
#endif /* defined(__heroJump__BroadcastLayer__) */
