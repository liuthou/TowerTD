//
//  SharedMenu.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-30.
//
//

#ifndef __CarrotFantasy__SharedMenu__
#define __CarrotFantasy__SharedMenu__

#include "cocos2d.h"
using namespace cocos2d;

class SharedMenu: public Node
{
public:
    
    CREATE_FUNC(SharedMenu);
    
protected:
    
    virtual bool init();
    
    virtual void createMenu();
};

#endif /* defined(__CarrotFantasy__SharedMenu__) */
