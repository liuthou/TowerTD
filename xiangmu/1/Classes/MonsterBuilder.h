#ifndef __CarrotFantasy__MonsterBuilder__
#define __CarrotFantasy__MonsterBuilder__
#include "cocos2d.h"
using namespace cocos2d;
class MonsterBuilder :public Node{

protected:
    
	virtual bool init();

	float _fDelayTime;

	int _MonsterCount;

	int _MonsterBuilderNumber;

	int _iReadFileMonsterCount;

	bool _bDelay;

	const int _iConstDelayTime = 8;

	int _iNumber;

	int _iBatch;

	virtual void onEnter();

	void createMonsterUpdate(float t);

	void MonsterFactoryController();

	Animation * _createMonsterAnimation;

	~MonsterBuilder();

public:

	int getBatch();

	CREATE_FUNC(MonsterBuilder);
	
	CC_SYNTHESIZE_PASS_BY_REF(int,_iBuildNumber,IBuildNumber);
};
#endif