#ifndef  __EXPERIENCELAYER_H
#define  __EXPERIENCELAYER_H

#include "cocos2d.h"
using namespace cocos2d;

class ExperienceLayer :public Layer
{
public:
	virtual bool init();
	void setFill(ProgressTimer* fill){ _fill = fill; }
	void setProgress(float percentage){ _fill->setPercentage(percentage); }
	CREATE_FUNC(ExperienceLayer);
	ExperienceLayer(){}
	~ExperienceLayer();
private:
	void heroChangeExp(Ref * obj);
private:
	ProgressTimer* _fillExperience;
	ProgressTimer* _fill;
	Sprite * _heroExperience;
};

#endif