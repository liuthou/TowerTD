//
//  LoadingSourceLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-27.
//
//

#ifndef __CarrotFantasy__LoadingSourceLayer__
#define __CarrotFantasy__LoadingSourceLayer__

#include "PublicDefine.h"

class LoadingSourceLayer: public Layer
{
public:
    
    CREATE_FUNC(LoadingSourceLayer);
    
    virtual void setFuncShowMenuPanel(const std::function<void ()> &rFuncShowMenuPanel);
    
protected:
    
    virtual void onEnter()override;
    
    virtual bool init();
    
    virtual void loadSource();

protected:
    
    std::function<void ()> _funShowMenuPanel;
    
    Label *_pLoadingTitle = nullptr;
};

#endif /* defined(__CarrotFantasy__LoadingSourceLayer__) */
