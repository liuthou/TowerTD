#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class ScoreLayer :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(ScoreLayer);

	void addLivesAmount(float t);
	void addScore(Ref * obj);


protected:

	Label * nowScore;
    CC_SYNTHESIZE(int,curScore,CurScore);
	int maxScore;
	Size vsize;


	Sprite *lives1;
	Sprite *lives2;
	Sprite *lives3;
	Sprite *lives4;


	bool bg_music;
	bool ef_music;


	void update(float t);

private:
	~ScoreLayer(){
		__NotificationCenter::getInstance()->removeAllObservers(this);
	}

};