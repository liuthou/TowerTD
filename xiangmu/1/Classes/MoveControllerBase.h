//
//  MoveControllerBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-16.
//
//

#ifndef CarrotFantasy_MoveControllerBase_h
#define CarrotFantasy_MoveControllerBase_h

#include "MonsterBase.h"

class MoveControllerBase: public Node
{
	friend class MonsterBase;
public:
    
    virtual ~MoveControllerBase();
   /**
	* control the monster action
	*/
    virtual void listenerMonster(float t);

    
private:
   /**
	* set the move monster
	*/
	void setMonster(MonsterBase * pMomster);
   /**
    * erase the vector's Point
	*/
	void erasePoint();

	virtual bool init(MonsterBase * pMomster);

	static MoveControllerBase * create(MonsterBase * pMomster);

	CC_SYNTHESIZE_PASS_BY_REF(int,_iMonsterSpeed,IMonsterSpeed);

	Animation * AnimationMaker(int iBulletType,float t);

	MoveControllerBase(){}
private:

	MonsterBase *_pMonster = nullptr;

	std::vector<Vec2> * _pMapPonits;

};


#endif
