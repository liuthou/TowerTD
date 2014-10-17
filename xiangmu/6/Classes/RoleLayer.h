//
//  RoleLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#ifndef __heroJump__RoleLayer__
#define __heroJump__RoleLayer__

#include <iostream>
#include "cocos2d.h"
#include "RoleSprite.h"
#include "SystemMarcoUtil.h"
USING_NS_CC;
#define FIX_POS(_pos, _min, _max) \
if (_pos <= _min)        \
_pos = _min;        \
else if (_pos >= _max)   \
_pos = _max;
/**
 *  主角层
 */
class RoleLayer:public Layer {
private:
    RoleSprite *role;
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onAccelerationForRole(Acceleration* acc, Event* event);
    /**
     *  加速度计是否打开
     */
    bool accelerationFlag;
    CREATE_FUNC(RoleLayer)

};
#endif /* defined(__heroJump__RoleLayer__) */
