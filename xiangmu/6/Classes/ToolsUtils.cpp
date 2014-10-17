//
//  ToolsUtils.cpp
//  heroJump
//
//  Created by mazhai on 14-10-3.
//
//

#include "ToolsUtils.h"
void ToolsUtils::drawRubberband(Vec2 p1,Vec2 p2,const Mat4 &transform){
    Director *director = Director::getInstance();
    //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    //    CHECK_GL_ERROR_DEBUG();
    //画边框
    DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
    glLineWidth(10);
    
    Vec2 vertices[] = {p1, p2};
    DrawPrimitives::drawPoly(vertices, 2, true);
    //    CHECK_GL_ERROR_DEBUG();
    
    //绘制停止，释放
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    
}

void ToolsUtils::drawRubberband(Vec2 p1,Vec2 p2,float degrees,const Mat4 &transform,bool isUp){
    Director *director = Director::getInstance();
    //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    //    CHECK_GL_ERROR_DEBUG();
    //画边框
    DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
    glLineWidth(10);
//    const unsigned int s_ = vcs.size();
//    Vec2 *vertices = new Vec2[s_];
//    int i = 0;
    
//    for (auto ite = vcs.begin(); ite != vcs.end(); ++ite) {
//        vertices[i] = Vec2((*ite).origin.x,(*ite).origin.y - (13) *(sin(CC_DEGREES_TO_RADIANS(i))));
//        i++;
//    }
//    DrawPrimitives::drawPoly(vertices, vcs.size(), true);
    //    CHECK_GL_ERROR_DEBUG();
    
//    DrawPrimitives::drawQuadBezier(p1, Vec2(abs(p1.x -p2.x)/2,abs(p1.y -p2.y)/2), Vec2(abs(p1.x -p2.x),abs(p1.y -p2.y)), 10);
    
    
    std::vector<Vec2> vecs = getArcPosition(p1,p2,degrees,isUp);
    const unsigned int s_ = (const unsigned int)vecs.size();
    Vec2 *vertices = new Vec2[s_];
    int i = 0;
    
    for (auto ite = vecs.begin(); ite != vecs.end(); ++ite) {
        vertices[i] = (*ite);
        i++;
    }
    DrawPrimitives::drawPoly(vertices, s_, false);
    //绘制停止，释放
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    
}

std::vector<Vec2> ToolsUtils::getArcPosition(Vec2 p1,Vec2 p2,float degrees,bool isUp){
    double der = cos(CC_DEGREES_TO_RADIANS(degrees));
    std::vector<Vec2> vecs;
    /**
     *  求出边的长度
     */
    float width_ = abs(abs(p1.x - p2.x)/der);
    /**
     *  先按照30°差值去做
     */
    int _i = segementLines;
    float w_ = width_ /_i;
    float wdsin_ = w_*(sin(CC_DEGREES_TO_RADIANS(degrees)));
    float wdcos =  w_*(cos(CC_DEGREES_TO_RADIANS(degrees)));
    Vec2 vc;
    if (degrees > 90) {
        vc = p1.x > p2.x ? Vec2(p1.x, p1.y):Vec2(p2.x, p2.y);
    } else {
        vc = p1.x < p2.x ? Vec2(p1.x, p1.y):Vec2(p2.x, p2.y);
    }
    
    bool flag = true;
    for (int i = 0; i<=_i; i++) {
        float wdSin = (width_/18)*((sin(CC_DEGREES_TO_RADIANS(i))));
//        log("sin(CC_DEGREES_TO_RADIANS(i))= %.2f",sin(CC_DEGREES_TO_RADIANS(i)));
        if (sin(CC_DEGREES_TO_RADIANS(i)) == 1) {
            flag = false;
        }
        float y1 = isUp ? (vc.y + wdsin_) + wdSin:(vc.y + wdsin_) - wdSin;
        float x1 = vc.x + wdcos;
        vc = Vec2(x1, (vc.y + wdsin_));
        vecs.push_back(Vec2(x1,y1));
    }
    return vecs;
}