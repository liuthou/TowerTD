//
//  ToolsBaseControlUserScript.cpp
//  heroJump
//
//  Created by mazhai on 14-9-26.
//
//

#include "ToolsBaseControlUserScript.h"
#include "HitBodys.h"
bool ToolsBaseControlUserScript::init(){
    if (!ToolsBaseScript::init()) {
        return false;
    }
    return true;
}

void ToolsBaseControlUserScript::die(){
    this -> setDie(true);
    this -> removeFromParentAndCleanup(true);
    HitBodys::getInstance() -> deltetToolsBaseControlUserScript(this);
    
}

/**
 *  默认攻击力
 */
int ToolsBaseControlUserScript::attack(){
    return 0;
}
std::string ToolsBaseControlUserScript::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}