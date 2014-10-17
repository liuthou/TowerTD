//
//  RubberbandSprite.h
//  heroJump
//
//  Created by mazhai on 14-10-2.
//
//

#ifndef __heroJump__RubberbandSprite__
#define __heroJump__RubberbandSprite__

#include <iostream>
#include <cocos2d.h>
#include "UseToolsBaseSprite.h"
#include "ConfigUtil.h"
#include "SystemMarcoUtil.h"
#define RUNBBERBAND_SPEED 10.4
#define WOOD_REDINS 90
USING_NS_CC;

class RubberbandSprite : public UseToolsBaseSprite{
private:
    std::vector<Rect> rubberbandPoints;
    /**
     *  回收前动画
     */
    bool isRubber;
    /**
     *  抖动的次数
     */
    int shakeCount;
    /**
     *  皮套是否向上弯曲
     */
    bool isUp;
    /**
     *  主角是否踩到了皮套上面
     */
    bool isStepOn;
public:
    virtual bool init();
    virtual void changeRoleState();
    virtual void onEnter();
    virtual std::vector<Rect> getRects();
    CREATE_FUNC(RubberbandSprite);
    virtual std::string sendCast();
    virtual void shake(float ft);
    virtual void collisionRole();
    virtual void setStepOn(){
        isStepOn = true;
    }
    void startShake();
    /**
     *  弹起的速度
     *
     *  @return 弹起的速度
     */
    virtual float getRoleSpeedTime();
//    virtual void die();
    /**
     *  弹起的角度
     *
     *  @return 弹起的角度
     */
    virtual float getRedians();
    
    CC_SYNTHESIZE(Vec2, p1, P1);
    CC_SYNTHESIZE(Vec2, p2, P2);
    
    /**
     *  当前皮筋儿的角度
     */
    CC_SYNTHESIZE(float, rubberAngle, RubberAngle);
    //重载draw方法
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
protected:
    //自定义draw实现
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
    cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__heroJump__RubberbandSprite__) */
