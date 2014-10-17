#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_
#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer : public Layer
{
protected:
	//添加精灵，参数为：图片文件名，位置，缩放比例
	void addSprite(std::string fileName, Vec2 spritePos, float scaleValue);
	//添加按钮，参数为：显示图片，选择图片，位置，是否是开关，回调函数
	void addMenu(std::string norName, std::string selName, Vec2 itemPos, bool toggleFlag, std::function<void(Ref *)> menuCallback);
	//回到开始界面按钮回调函数
	void toStartScene(Ref * sender);
	//再玩一次按钮的回调函数
	void onceGame(Ref * sender);
	virtual bool init();
protected:
	//判断音效的开关
	int audioFlag;
public:
	//增加分数显示
	void addScoreLabel(int curScore, int maxScore);
	CREATE_FUNC(GameOverLayer);
};

#endif // !_GAMEOVERLAYER_H_
