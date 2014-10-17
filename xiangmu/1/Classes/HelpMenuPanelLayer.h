//
//  HelpMenuPanelLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#ifndef __CarrotFantasy__HelpMenuPanelLayer__
#define __CarrotFantasy__HelpMenuPanelLayer__

#include "PublicDefine.h"

class HelpMenuPanelLayer:public Layer
{
public:
	
    CREATE_FUNC(HelpMenuPanelLayer);
    
protected:
	
    virtual bool init()override;
    
    virtual void createMenuPanel();
    
private:
	MenuItemToggle * pHelpBtn;
	MenuItemToggle * pMonsterHelpBtn;
	MenuItemToggle * pTowerHelpBtn;
    LayerMultiplex *_pLayers = nullptr;
};

#endif /* defined(__CarrotFantasy__HelpMenuPanelLayer__) */
