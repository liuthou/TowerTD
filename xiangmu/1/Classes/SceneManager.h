//
//  SceneManager.h
//  newCardDefence
//
//  Created by Yan on 14-8-27.
//
//

#ifndef __newCardDefence__SceneManager__
#define __newCardDefence__SceneManager__

#include "PublicDefine.h"

class SceneManager:public Node
{
public:
    
    CREATE_INSTANCE_FUNC(SceneManager);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual void initWelComeScene();
    
    virtual int getCurPageIndex()const;
    
    virtual int getCurLevelIndex()const;
    
protected:
    
    virtual void changeScene(const std::tuple<SceneType, int> &rEnSceneType);
    
    virtual void notifyChangeScene(Ref *pData);
    
    virtual void registerChangeSceneEvent();
    
    virtual void unRegisterAllEvent();
    
    virtual void checkCurPageAndLevel();
    
    virtual bool init();
    
protected:
    
    SceneType _enCurScene = en_WelcomeScene;
    
private:
    
    int _iCurPageIndex = 0;
    
    int _iCurLevelIndex = 0;
    
private:
    
    SceneManager(){}
    
    virtual ~SceneManager(){}
    
    SceneManager(const SceneManager &) = delete;
    
    SceneManager &operator=(const SceneManager &) = delete;
    
};

#endif /* defined(__newCardDefence__SceneManager__) */
