//
//  GameSettingScene.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__GameSettingScene__
#define __CarrotFantasy__GameSettingScene__

#include "PublicDefine.h"

class GameSettingScene:public Scene
{
public:
    
    CREATE_FUNC(GameSettingScene);
    
    virtual ~GameSettingScene();
    
protected:
    
    virtual bool init();
    
    virtual void onEnter()override;
    
private:
    
    Layer *_pPanelLayer = nullptr;
};

#endif /* defined(__CarrotFantasy__GameSettingScene__) */
