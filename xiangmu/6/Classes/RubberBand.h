//
//  RubberBand.h
//  herojump
//
//  Created by lanou3g on 14-9-24.
//
//

#ifndef __herojump__RubberBand__
#define __herojump__RubberBand__
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class RubberBand:public Layer{
protected:
    float beginDrawRubberBand;
    float endDrawRubberBand;
    Vec2 firstTouchPosition;
    Vec2 endTouchPosition;
    std::vector<Vec2 >v;
public:
    virtual bool init();
    CREATE_FUNC(RubberBand);
    static Scene* createScene();
};

#endif /* defined(__herojump__RubberBand__) */
