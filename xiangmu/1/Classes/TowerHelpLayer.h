//
//  TowerHelpLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#ifndef __CarrotFantasy__TowerHelpLayer__
#define __CarrotFantasy__TowerHelpLayer__

#include "PublicDefine.h"
#include "ui/CocosGUI.h"
using namespace ui;

class TowerHelpLayer:public Layer
{
public:
    
    CREATE_FUNC(TowerHelpLayer);
    
    virtual ~TowerHelpLayer();
    
protected:
    
    virtual bool init()override;

	virtual void PPageView();
    
private:
    
    PageView *_pPageView = nullptr;

	Sprite * bottomSprite;

	int _iCurLevelIndex = 0;

	

    
    
};

#endif /* defined(__CarrotFantasy__TowerHelpLayer__) */
