//
//  MenuPanelLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#ifndef __CarrotFantasy__MenuPanelLayer__
#define __CarrotFantasy__MenuPanelLayer__

#include "PublicDefine.h"

class PageViewLayer;

class MenuPanelLayer:public Layer
{
public:
    
    CREATE_FUNC(MenuPanelLayer);
    
    virtual void setPageTurnFunc(const std::function<void (const bool &)> &rFuncPageTurn);
    
protected:
    
    virtual bool init();
    
    virtual void createItemPanel();
    
private:

    std::function<void (const bool &)> _funcPageTurn;

};


#endif /* defined(__CarrotFantasy__MenuPanelLayer__) */
