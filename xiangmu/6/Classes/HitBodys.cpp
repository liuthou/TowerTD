//
//  HitBodys.cpp
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//
/**
 *  碰撞的集合
 */
#include "HitBodys.h"
//hits body container
HitBodys *HitBodys::instance = nullptr;

HitBodys* HitBodys::getInstance(){
    if (!instance) {
        instance = new HitBodys();
    }
    return instance;
}

void HitBodys::addToolsScrpit(ToolsBaseScript *t){
    toolsScripts.pushBack(t);
}

void HitBodys::deleteToolsScrpit(ToolsBaseScript *t){
    toolsScripts.eraseObject(t);
}

void HitBodys::addUseToolsBaseSprite(UseToolsBaseSprite* t){
    useToolsBaseSprites.pushBack(t);
}
void HitBodys::deleteToolsBaseSprite(UseToolsBaseSprite *t){
    useToolsBaseSprites.eraseObject(t);
}

void HitBodys::addToolsBaseControlUserScript(ToolsBaseControlUserScript* t){
    toolsBaseControlUserScripts.pushBack(t);
}
void HitBodys::deltetToolsBaseControlUserScript(ToolsBaseControlUserScript* t){
    toolsBaseControlUserScripts.eraseObject(t);
}

void HitBodys::clearToolsBaseSprite(){
	for (auto ite = toolsBaseControlUserScripts.begin(); ite != toolsBaseControlUserScripts.end();) {
		(*ite) -> die();
	}
}

void HitBodys::clearUseToolsBaseSprite(){
	for (auto ite = useToolsBaseSprites.begin(); ite != useToolsBaseSprites.end();) {
		(*ite) -> die();
	}
}
