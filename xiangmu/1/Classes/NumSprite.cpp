//
//  NumSprite.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-26.
//
//

#include "NumSprite.h"

Node *NumSprite::createNum(const std::string &rSNum, const std::string &rSImage)
{
    auto tSize = Sprite::create(rSImage)->getContentSize();
    auto tINumSize = rSNum.size();
    
    auto pNumNode = Node::create();
    pNumNode->retain();

    for(int i = 0; i < tINumSize; ++i)
    {
        auto tINum = atoi(StringUtils::format("%c", rSNum.at(i)).c_str());
        auto pNum = Sprite::create(rSImage, Rect(tSize.width / 12 * (tINum + 2), 0, tSize.width / 12, tSize.height));
        auto tPos = Vec2(pNum->getContentSize().width * i, 0);
        pNum->setPosition(tPos);
        pNumNode->addChild(pNum);
    }

    
    
//    auto tempNum = rINum;
//    for(int i = 1; i <= tINumSize; ++i)
//    {
//        auto tINum = 0;
//        if(1 == i)
//        {
//            tINum = tempNum % 10;
//        }
//        else
//        {
//            auto tNum = [&](){int num = 1; for(int count = 0; count < i; ++count) num *= 10; return num;}();
//
//            tempNum = rINum % tNum;
//            tINum = tempNum / (tNum / 10);
//            log("%d, %d, %d", tNum, tempNum, tINum);
//        }
//        
//        auto pNum = Sprite::create(rSImage, Rect(tSize.width / 12 * (tINum + 2), 0, tSize.width / 12, tSize.height));
//        int t = tINumSize - i - tINumSize / 2;
//        auto tPos = Vec2(pNum->getContentSize().width * t, 0);
//        pNum->setPosition(tPos);
//        pNumNode->addChild(pNum);
//    }
    return pNumNode;
}





