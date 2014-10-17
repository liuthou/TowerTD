//
//  PauseLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-21.
//
//

#ifndef __CarrotFantasy__PauseLayer__
#define __CarrotFantasy__PauseLayer__

#include "PublicDefine.h"

class PauseLayer:public Layer
{
public:
    
    CREATE_FUNC(PauseLayer);
    
    virtual void setFuncFlagPauseLayerIsClose(const std::function<void ()> & rFuncFlagPauseLayerIsClose);
    
protected:
    
    virtual bool init();
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
    virtual void createMenu();
    
    virtual void createSharedMenu();
    
    virtual void closeTouchEvent();
    
    std::function<void ()> _funcFlagPauseLayerIsClose;
};

#endif /* defined(__CarrotFantasy__PauseLayer__) */
