//
//  PokerAnimation.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-29.
//
//

#ifndef __TexasPoker__PokerAnimation__
#define __TexasPoker__PokerAnimation__

#include <iostream>
#include <cocos2d.h>
#include "Global.h"
USING_NS_CC;

#include "ProcessControl.h"
class PokerAnimation : public Layer{
public:
    virtual bool init(ProcessControl *processControl);
    static PokerAnimation* create(ProcessControl *processControl);
        
public:
    virtual void End();
    void setEndFunc(std::function<void ()> endFunc);
    
protected:
    
    ProcessControl *processControl;
    std::function<void ()> endFunc;
    
    virtual void initUI(){};
};

#endif /* defined(__TexasPoker__PokerAnimation__) */
