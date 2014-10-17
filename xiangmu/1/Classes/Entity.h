//
//  Entity.h
//  newCardDefence
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __newCardDefence__Entity__
#define __newCardDefence__Entity__

#include "PublicDefine.h"

class Entity:public Node
{
public:
    
    virtual ~Entity();

public:
	static unsigned long ID;

	unsigned int getmID();

    virtual bool init(const int &rId, const std::string &rSCsvFileName);
    
    virtual const Size &getContentSize()const;
    /**
     *  run doDead() which Entity is dead
     */
    virtual void doDead()final;
    
    //bind sprite and get bind sprite
    /**
     *  everyone Entity need bind a Sprite, use for show
     *
     *  @param pSprite is bind sprite
     */
    virtual void bindSprite(Sprite *pSprite);
    virtual Sprite *getSprite();
    
    /**
     *  get sprite size and origin
     *
     *  @return Rect
     */
    virtual Rect getBoundingBox()const;
    
//    virtual void 
    
protected:
    /**
     *  deadAction func
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "");

    /**
     init Entity property
     
     :param: std csv file Name
     
     :returns: null
     */
    virtual void initProperty(const int &rId, const std::string &rSCsvFileName);
    /**
     *  Entity id
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iId, IId);
    /**
     *  Entity name
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sName, SName);
    /**
     *  Entity bind sprite Model image file name
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sModelName, SModelName);
    /**
     *  Entity values
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iValue, IValue);
    /**
     *  flag Entity is dead
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsDead, IsDead);
    /**
     *  Animation frame count
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _IAnimationFrameCount, AnimationFrameCount);
    /**
     *  Entity level
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iLevel, ILevel);
private:
    /**
     *  image sprite, use bindSprite and getSprite
     */
    Sprite *_pSprite = nullptr;

	unsigned long _myID;
    
};

#endif /* defined(__newCardDefence__Entity__) */
