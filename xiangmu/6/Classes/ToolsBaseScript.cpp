//
//  ToolsBaseScript.cpp
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#include "ToolsBaseScript.h"
#include "HitBodys.h"
bool ToolsBaseScript::init(){
    if (!BodyAbstract::init()) {
        return false;
    }
    isDie = false;
    return true;
}

void ToolsBaseScript::collisionRole(){
	changeRoleState();
}

void ToolsBaseScript::die(){
    isDie = true;
    this -> removeFromParentAndCleanup(true);
    HitBodys::getInstance() -> deleteToolsScrpit(this);
}



