//
//  BarrierBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BarrierBase__
#define __CarrotFantasy__BarrierBase__


#include "VictimEntityBase.h"

class BarrierBase:public VictimEntityBase
{

public:
    
    static BarrierBase * create(const int &rId);
    
    friend class BarrierFactory;
    
protected:

    virtual bool init(const int &rId);
    
    virtual void deadAction(const std::string &rSDeadImageFile = "");
    
    virtual void behurtAction();
    
};

#endif /* defined(__CarrotFantasy__BarrierBase__) */
