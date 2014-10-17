//
//  HelpLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#ifndef __CarrotFantasy__HelpLayer__
#define __CarrotFantasy__HelpLayer__

#include "PublicDefine.h"
#include "ui/CocosGUI.h"
using namespace ui;
//const static unsigned int THEME_PAGEVIEW_ARRAY[] = { 1, 2, 3, 4 };
class HelpLayer:public Layer
{
public:
    
    CREATE_FUNC(HelpLayer);
    
    virtual ~HelpLayer();
    
protected:
    
    virtual bool init()override;

	virtual void PPageView();
    
private:
	Sprite * bottomSprite;

	int _iCurLevelIndex = 0;
	
	PageView *_pPageView = nullptr;
	
};

#endif /* defined(__CarrotFantasy__HelpLayer__) */
