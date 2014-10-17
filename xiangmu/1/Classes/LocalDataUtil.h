//
//  LocalDataUtil.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-8.
//
//

#ifndef __CarrotFantasy__LocalDataUtil__
#define __CarrotFantasy__LocalDataUtil__

#include "PublicDefine.h"

class LocalDataUtil: public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(LocalDataUtil);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual ValueMap &getLevelData();
    
    virtual void setLevelData(const ValueMap &rValueMap);
    
protected:
    
    virtual bool init();
    
    virtual void registerLevelDataChangeEvent();
    
    virtual void levelDataChange(Ref *pData);
    
private:
    
    ValueMap _levelData;
    
    std::string _sLevelDataFileName = "";
    
private:
    
    LocalDataUtil(){}
    
    virtual ~LocalDataUtil();
    
    LocalDataUtil(const LocalDataUtil &) = delete;
    
    LocalDataUtil &operator=(const LocalDataUtil &) = delete;
    
    
    
};

#endif /* defined(__CarrotFantasy__LocalDataUtil__) */
