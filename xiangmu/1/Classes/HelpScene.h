//
//  HelpScene.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#ifndef __CarrotFantasy__HelpScene__
#define __CarrotFantasy__HelpScene__

#include "PublicDefine.h"

class HelpScene: public Scene
{
public:
    
    CREATE_FUNC(HelpScene);
    
    virtual ~HelpScene();
    
protected:
    
    virtual bool init()override;
    
    virtual void onEnter()override;
    
private:
    
    Layer *_pMenuPanelLayer = nullptr;
    
};

#endif /* defined(__CarrotFantasy__HelpScene__) */
