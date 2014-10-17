//
//  ToolsLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#ifndef __heroJump__ToolsLayer__
#define __heroJump__ToolsLayer__

#include <iostream>
#include "cocos2d.h"
#include "UseToolsBaseSprite.h"
#include "WoodSprite.h"
#include "ActionHelper.h"
USING_NS_CC;
class ToolsLayer:public Layer {
private:
    Vec2 p1;
    Vec2 p2;
    
public:
    virtual bool init();
    virtual void onEnter();
    /**
     *  add toos to Menu
     */
    virtual void addTools();
    virtual bool touchBegan(Touch* t, Event* e);
    virtual void touchMoved(Touch* t, Event* e);
    virtual void touchEnded(Touch* t, Event* e);
    /**
     *  当前用户使用道具
     */
    CC_SYNTHESIZE(int, nowType, NowType);
    CREATE_FUNC(ToolsLayer);
    //重载draw方法
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    void setNowUseType(NOW_USE_TYPE nType);
protected:
    //自定义draw实现
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
    cocos2d::CustomCommand _customCommand;
};
#endif /* defined(__heroJump__ToolsLayer__) */
