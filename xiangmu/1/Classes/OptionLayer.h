//
//  OptionLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__OptionLayer__
#define __CarrotFantasy__OptionLayer__

#include "cocos2d.h"
using namespace cocos2d;

class OptionLayer:public Layer
{
    
public:
    
    CREATE_FUNC(OptionLayer);
    
protected:
    
    virtual bool init();
    
    virtual void loadSource();
};

#endif /* defined(__CarrotFantasy__OptionLayer__) */
