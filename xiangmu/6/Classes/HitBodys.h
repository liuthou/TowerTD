#ifndef __heroJump__HitBodys__
#define __heroJump__HitBodys__

/**
 *  add by mabs
 *  all can collision body
 */

#include <iostream>
#include "cocos2d.h"
#include "ToolsBaseScript.h"
#include "UseToolsBaseSprite.h"
#include "ToolsBaseControlUserScript.h"
USING_NS_CC;
class HitBodys {
private:
    HitBodys(){}
    HitBodys(const HitBodys &b){}
    HitBodys operator=(const HitBodys& b){return b;}
    static HitBodys* instance;
public:
    static HitBodys* getInstance();
    void addToolsScrpit(ToolsBaseScript *t);
    void deleteToolsScrpit(ToolsBaseScript *t);
    void addUseToolsBaseSprite(UseToolsBaseSprite* t);
    void deleteToolsBaseSprite(UseToolsBaseSprite *t);
    void addToolsBaseControlUserScript(ToolsBaseControlUserScript* t);
    void deltetToolsBaseControlUserScript(ToolsBaseControlUserScript* t);
    void clearToolsBaseSprite();
    void clearUseToolsBaseSprite();
    CC_SYNTHESIZE_PASS_BY_REF(Vector<ToolsBaseScript*>, toolsScripts, ToolsScripts);
    CC_SYNTHESIZE_PASS_BY_REF(Vector<UseToolsBaseSprite*>, useToolsBaseSprites, UseToolsBaseSprite);
    CC_SYNTHESIZE_PASS_BY_REF(Vector<ToolsBaseControlUserScript*>, toolsBaseControlUserScripts, ToolsBaseControlUserScript);
};

#endif /* defined(__heroJump__HitBodys__) */
