//
//  ScoreAndControlLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__ScoreAndControlLayer__
#define __CarrotFantasy__ScoreAndControlLayer__

#include "PublicDefine.h"
/**
 *  ScoreAndControllerLayer use show money,control pause game,back to theme and select level
 */

class ScoreAndControllerLayer: public Layer
{
public:
    
    CREATE_FUNC(ScoreAndControllerLayer);
    
    virtual void setPauseFlagIsClose();
    
    virtual void clickChooseItem();
    
protected:
    
    virtual bool init();
    
    virtual void createTopPanel();
    
    virtual void loadBg();
    
    CC_SYNTHESIZE(int, _iMoney, CurMoney);
    
    virtual void registerNotifyEvent();
    
    virtual void unRegisterNotifyEvent();
    
    virtual void moneyChange(Ref *pData);
    
    virtual void monsterBatchChange(Ref *pData);
    
    virtual void setMonsterBatchCount(const int &rIMonsterBatchIndex);
    
    virtual void setMoneyNum(const int &rIMoneyNum);
    
    virtual void onExit()override;
    
private:
    
    Node *_pMonsterBatchIndex = nullptr;
    
    Node *_pMoneyLabel = nullptr;
    
    bool _bIsOpenChooceMenu = false;
    
    bool _bIsOpenSpeedUp = false;
    
    bool _bIsPause = false;
    
    MenuItemSprite *_pChooseItem = nullptr;

};

#endif /* defined(__CarrotFantasy__ScoreAndControlLayer__) */
