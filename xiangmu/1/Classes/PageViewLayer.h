//
//  PageViewLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#ifndef __CarrotFantasy__PageViewLayer__
#define __CarrotFantasy__PageViewLayer__

#include "PublicDefine.h"
#include "ui/UIPageView.h"
using namespace ui;

class PageViewLayer: public Layer
{
public:
    
    virtual ~PageViewLayer();
    
    CREATE_FUNC(PageViewLayer);
    
    virtual void pageTurn(const bool &rBLeft);
    
protected:
    
    virtual bool init();
    
    virtual void setPageFlag(const int &rIIndex);
    
    virtual void createThemePageView();
    
    virtual void createThemeFlags();
    
    virtual void loadBg();
    
private:
    
    PageView *_pPageView = nullptr;
    
    int _iPageIndex = 0;
    
    Vector<MenuItemSprite*> *_pPageFlagVec = nullptr;
};
#endif /* defined(__CarrotFantasy__PageViewLayer__) */
