//
//  ToolsBaseScript.h
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#ifndef __heroJump__ToolsBaseScript__
#define __heroJump__ToolsBaseScript__

#include <iostream>
#include "cocos2d.h"
#include "BodyAbstract.h"
USING_NS_CC;
/**
 *  add by mabs
 *  This is support role's Tools
 *  And have basic motion
 */
class ToolsBaseScript : public BodyAbstract{
protected:
    /**
     *  The concrete realization
     */
    virtual void changeRoleState()=0;

    
public:
    virtual bool init();
    CC_SYNTHESIZE(bool, isDie, Die);
    /**
     *  die
     */
    virtual void die();
    /**
     *  when role collision it
     */
    virtual void collisionRole();
};


#endif /* defined(__heroJump__ToolsBaseScript__) */
