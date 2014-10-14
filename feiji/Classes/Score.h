#ifndef __SCORE_H
#define __SCORE_H
#include "cocos2d.h"
using namespace cocos2d;
class Score:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(Score);
protected:
	int curScore;
	int maxScore;
	void boundingTest(float t);
};
#endif