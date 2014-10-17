//
//  LevelConfigUtil.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-26.
//
//

#ifndef __CarrotFantasy__LevelConfigUtil__
#define __CarrotFantasy__LevelConfigUtil__

#include "PublicDefine.h"

class LevelConfigUtil:public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(LevelConfigUtil);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual void loadLevelConfig();
    
    virtual std::tuple<int, int, int, std::vector<std::string>> getLevelConfig()const;
    
    virtual std::vector<std::string> getCurLevelTowersInfo()const;
    
    virtual int getCurLevelMonsterBatchCount()const;
    
    virtual void buildLevelConfig();
    
    virtual int getCurLevelMoney()const;
    
protected:
    
    virtual bool init();
    
protected:
    
    int _iCurPageIndex = 0;
    
    int _iCurLevelIndex = 0;
    
    int _iCurLevelMoney = 0;
    
    int _iMonsterBatchCount = 0;
    
    std::vector<std::string> *_pEffectTowers = nullptr;
    
private:
    
    LevelConfigUtil();
    
    virtual ~LevelConfigUtil();
    
    LevelConfigUtil(const LevelConfigUtil &) = delete;
    
    LevelConfigUtil &operator=(const LevelConfigUtil &) = delete;
};

#endif /* defined(__CarrotFantasy__LevelConfigUtil__) */
