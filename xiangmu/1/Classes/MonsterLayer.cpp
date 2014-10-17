//
//  MonsterLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "MonsterLayer.h"
#include "MapUtil.h"

bool MonsterLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());

		auto pStart = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start01.png"));
		pStart->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));
		addChild(pStart);

        registerMonsterDeadEvent();
        bRet = true;
    }
    while (0);
    
    return bRet;
}


void MonsterLayer::registerMonsterDeadEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(MonsterLayer::monsterDead), "monsterDeadMoney", nullptr);
}

void MonsterLayer::monsterDead(Ref *pData)
{
    auto tValue = *(reinterpret_cast<std::tuple<Vec2, int>*>(pData));
    auto tMoney = std::get<1>(tValue);
    auto pMoney = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png", tMoney));
    auto pVec2 = std::get<0>(tValue);
    pMoney->setPosition(pVec2);
    addChild(pMoney);
    pMoney->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, 100)), DelayTime::create(0.4), FadeOut::create(0.4f), CallFunc::create([=](){pMoney->removeFromParent();}) ,  NULL));

}

void MonsterLayer::onExit()
{
    Layer::onExit();
    NOTIFY->removeAllObservers(this);
}

