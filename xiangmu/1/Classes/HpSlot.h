//
//  HpSlot.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__HpSlot__
#define __CarrotFantasy__HpSlot__

#include "PublicDefine.h"
class VictimEntityBase;

class HpSlot: public Node
{
public:
    
    virtual ~HpSlot();
    
    static HpSlot *create(VictimEntityBase *pVictimEntity);
    
    virtual void setHp(const int &rIHp);
    
    virtual const Size &getContentSize()const;

    
protected:
    
    virtual bool init(VictimEntityBase *pVictimEntity);
    
private:
    
    VictimEntityBase *_pVictimEntity = nullptr;
    
public:
    
    ProgressTimer *_pHpSlot = nullptr;
    
    int _iHpMax = 0;
};

#endif /* defined(__CarrotFantasy__HpSlot__) */
