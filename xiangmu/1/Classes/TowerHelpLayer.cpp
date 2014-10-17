//
//  TowerHelpLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#include "TowerHelpLayer.h"
#include "NumSprite.h"

TowerHelpLayer::~TowerHelpLayer()
{

}

bool TowerHelpLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        bRet = true;
    }
    while (0);

	bottomSprite = Sprite::createWithSpriteFrameName("bottom.png");
	bottomSprite->setPosition(480, 50);
	addChild(bottomSprite);

	auto frame = SpriteFrame::create("Themes/Items/numwhite-hd.png", Rect(20, 0, 20, 40));
	auto _Num = Sprite::createWithSpriteFrame(frame);
	auto eighthNum = NumSprite::createNum("18", "Themes/Items/numwhite-hd.png");
	_Num->setPosition(480, 55);
	eighthNum->setPosition(498, 55);

	addChild(eighthNum);
	addChild(_Num);

	PPageView();
    return bRet;
}
void TowerHelpLayer::PPageView()
{

	_pPageView = PageView::create();
	_pPageView->setContentSize(Size(960.0f, 640.0f));
	Layout *pLayout = nullptr;

	for (int i = 1; i < 19; ++i)
	{
		pLayout = Layout::create();

		auto pLayoutSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d.png", i));
		auto pLayoutSpriteName = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d_CN.png", i));
	
		pLayoutSprite->setPosition(Vec2(480, 310));
		pLayoutSpriteName->setPosition(Vec2(480, 310));

		pLayout->addChild(pLayoutSprite);
		pLayout->addChild(pLayoutSpriteName);
		_pPageView->insertPage(pLayout, i);
		
	}
	_pPageView->setPassFocusToChild(true);
	_pPageView->scrollToPage(_iCurLevelIndex);
	_pPageView->addEventListener([=](Ref *pSender, PageView::EventType event)
	{
		if (PageView::EventType::TURNING == event)
		{
			_iCurLevelIndex = _pPageView->getCurPageIndex();
			std::string num = StringUtils::format("%d", _iCurLevelIndex + 1);
			bottomSprite->removeAllChildren();
			auto layoutNum = NumSprite::createNum(num, "Themes/Items/numwhite-hd.png");
			if (_iCurLevelIndex + 1 >= 10)
			{
				layoutNum->setPosition(447, 40);
			}else{
				layoutNum->setPosition(463, 40);
			}
			
			bottomSprite->addChild(layoutNum, 80);
		}
	});

	addChild(_pPageView);

}
