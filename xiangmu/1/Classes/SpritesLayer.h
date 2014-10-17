//
//  SpritesLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#ifndef __CarrotFantasy__SpritesLayer__
#define __CarrotFantasy__SpritesLayer__

#include "PublicDefine.h"

class SpritesLayer: public Layer
{
public:
    
    CREATE_FUNC(SpritesLayer);
    
    virtual ~SpritesLayer();
    
protected:
    
    virtual bool init();
    
    virtual void createStaticSprites();
    
    virtual void createDynamicSprites();
    
    virtual void createCarrot();
    
    virtual void leafAction(float dt);
    
private:
    
    Node *_pCarrotAll = nullptr;
    
    const Size _VisibleSize = Director::getInstance()->getVisibleSize();
    
};


#endif /* defined(__CarrotFantasy__SpriteLayer__) */
