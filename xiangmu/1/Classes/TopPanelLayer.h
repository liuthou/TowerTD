//
//  TopPanelLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-21.
//
//

#ifndef __CarrotFantasy__TopPanelLayer__
#define __CarrotFantasy__TopPanelLayer__

#include "PublicDefine.h"


class TopPanelLayer:public Layer
{
public:
    
    CREATE_FUNC(TopPanelLayer);
    
    virtual ~TopPanelLayer();
    
protected:
    
    virtual bool init();
    
    virtual void createMenuPanel();
    
    virtual void createMultiplexLayer();
    
private:
    
    LayerMultiplex *_pLayerMultiplex = nullptr;
};

#endif /* defined(__CarrotFantasy__TopPanelLayer__) */
