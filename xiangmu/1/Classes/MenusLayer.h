//
//  MenusLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-20.
//
//

#ifndef __CarrotFantasy__MenusLayer__
#define __CarrotFantasy__MenusLayer__

#include "PublicDefine.h"

class MenusLayer:public Layer
{
public:
    
    CREATE_FUNC(MenusLayer);
    
protected:
    
    virtual bool init();
    
    virtual void createMenuItems();
};

#endif /* defined(__CarrotFantasy__MenusLayer__) */
