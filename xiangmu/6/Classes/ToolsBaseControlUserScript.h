//
//  ToolsBaseControlUserScript.h
//  heroJump
//
//  Created by mazhai on 14-9-26.
//
//

#ifndef __heroJump__ToolsBaseControlUserScript__
#define __heroJump__ToolsBaseControlUserScript__
/**
 *  control user speed
 */
#include <iostream>
#include <cocos2d.h>
#include "ToolsBaseScript.h"
#include "ConfigUtil.h"
USING_NS_CC;

class ToolsBaseControlUserScript:public ToolsBaseScript{
public:
    virtual bool init();
    virtual Direction_ROLE collitionDirection() = 0;
    virtual int controleRoleSpeed() = 0;
    virtual void die();
    virtual int attack();
    virtual std::string sendCast();
};

#endif /* defined(__heroJump__ToolsBaseControlUserScript__) */
