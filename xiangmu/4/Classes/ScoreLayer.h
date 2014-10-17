#ifndef __SCORELAYER_H
#define __SCORELAYER_H

#include "cocos2d.h"
/************************************************************************/
/* 积分层 放置积分以及暂停按钮                                                                     */
/************************************************************************/
class ScoreLayer : public cocos2d::Layer
{
	~ScoreLayer();
protected:
	cocos2d::Label * label ;
	//积分显示
	void viewScore(Ref *);
	//道具显示
	void viewprops(Ref *);
	//创建暂停按钮
	void createPause();
	void deleteProps(Ref *);
	std::vector<cocos2d::Sprite *>nowTools;
public:
	CC_SYNTHESIZE(int,_isScore,nowScore);
	void onEnter();
    int getvectornumber();
	virtual bool init();

	CREATE_FUNC(ScoreLayer);
};

#endif // __HELLOWORLD_SCENE_H__