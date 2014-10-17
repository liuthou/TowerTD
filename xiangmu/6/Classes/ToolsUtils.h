//
//  ToolsUtils.h
//  heroJump
//
//  Created by mazhai on 14-10-3.
//
//

#ifndef __heroJump__ToolsUtils__
#define __heroJump__ToolsUtils__

#include <iostream>
#include <cocos2d.h>
#define alone_a 1
#define segementLines 180 / alone_a
USING_NS_CC;
class ToolsUtils{
public:
    static void drawRubberband(Vec2 p1,Vec2 p2,const Mat4 &transform);
    static void drawRubberband(Vec2 p1,Vec2 p2,float degrees,const Mat4 &transform,bool isUp);
    static std::vector<Vec2> getArcPosition(Vec2 p1,Vec2 p2,float der,bool isUp);
};
#endif /* defined(__heroJump__ToolsUtils__) */
