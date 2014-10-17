//
//  HelpLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#include "HelpLayer.h"
#include"NumSprite.h"
#include "SceneManager.h"
HelpLayer::~HelpLayer(){
}
bool HelpLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());

		PageView();

        bRet = true;
    }
    while (0);
	
	bottomSprite = Sprite::createWithSpriteFrameName("bottom.png");
	bottomSprite->setPosition(480, 50);
	addChild(bottomSprite);

	auto frame = SpriteFrame::create("Themes/Items/numwhite-hd.png", Rect(20, 0, 20, 40));
	auto _Num = Sprite::createWithSpriteFrame(frame);
	auto fourNum = NumSprite::createNum("4", "Themes/Items/numwhite-hd.png");
	_Num->setPosition(480, 55);
	fourNum->setPosition(498, 55);
	
	addChild(fourNum);
	addChild(_Num);

	PPageView();

    return bRet;
}
void HelpLayer::PPageView()
{
	
	_pPageView = PageView::create();
	_pPageView->setContentSize(Size(960.0f, 640.0f));

	Layout *pLayout = nullptr;

	for (int i = 1; i < 5; ++i)
	{
		pLayout = Layout::create();

		auto pLayoutSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tips_%d.png", i));
		auto tipsText = Sprite::createWithSpriteFrameName(StringUtils::format("tips_text_%d_CN.png", i));
		std::string num = StringUtils::format("%d", i);
		 
		tipsText->setPosition(480, 160);	
		pLayoutSprite->setPosition(Vec2(480, 370));
		
		pLayout->addChild(tipsText);
		pLayout->addChild(pLayoutSprite);
		_pPageView->insertPage(pLayout, i);
		

	}
	addChild(_pPageView);
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
			layoutNum->setPosition(465, 40);
			bottomSprite->addChild(layoutNum, 80);
				
		}
	});

	
	

}
