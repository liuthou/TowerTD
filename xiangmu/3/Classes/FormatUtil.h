#ifndef __FORMATUTIL_H_
#define __FORMATUTIL_H_
#include "cocos2d.h"
#define FORMATUTILATTRANGE 300
#define FORMATUTILPRICE 50
USING_NS_CC;
class FormatUtil:public Sprite{
public:
	CREATE_FUNC(FormatUtil);
	virtual bool init();
	CC_SYNTHESIZE(int,attrange,AttRange);
	CC_SYNTHESIZE(bool,isdie,Isdie);
	//爆炸动画
	CC_SYNTHESIZE_RETAIN(Animation*,animation,Animation);
	//价格
	CC_SYNTHESIZE(int,price,Price);
	//爆炸时回调函数
	void setExplodeFunc(std::function<void(FormatUtil* formatutil)>explode);
	virtual void onEnter();
protected:
	void remove();
	void explodeFunc();
	std::function<void(FormatUtil*)>explode;
	FormatUtil(){
		animation = nullptr;
	}
	~FormatUtil(){
		CC_SAFE_RELEASE_NULL(animation);
	}
};
#endif