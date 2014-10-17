//
//  DataCollectLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__DataCollectLayer__
#define __CarrotFantasy__DataCollectLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DataCollectLayer: public Layer
{
public:
    
    CREATE_FUNC(DataCollectLayer);
    
protected:
    
    virtual bool init();
    
    virtual void loadSource();
    
};

#endif /* defined(__CarrotFantasy__DataCollectLayer__) */
