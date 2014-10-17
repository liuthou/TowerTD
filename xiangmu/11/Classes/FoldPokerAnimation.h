#ifndef _FOLDPOKERANIMATION_H_
#define _FOLDPOKERANIMATION_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "PokerAnimation.h"
#include "Player.h"

class  FoldPokerAnimation :public PokerAnimation
{
public:
	/**
	*弃牌动画
	*完成动画后，结束动画
	*/
	void fold(int index);
    
	virtual void End();

	static FoldPokerAnimation* create(ProcessControl *processControl);

	//玩家弃牌动画开始位置
	CC_SYNTHESIZE(Vec2, startPoint, StartPoint);

private:

	virtual bool init(ProcessControl *processControl);
    
	/**
	*定义 开始 结束成员变量
	*定义 精灵图片
	*传进万家
	*/

	Vec2 endPoint;
	MenuItemSprite * playerItem;
	Player * player;

	Sprite * foldSprite;
	MoveTo * dealMoveTo;
	ScaleTo* st;
	TintTo* tt;
    
    virtual void initUI();
};
#endif