#ifndef __SHOWLAYER_H_
#define __SHOWLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class SuspendLayer;
class GameOverLayer;
class Role;

class ShowLayer : public Layer{
public:
	CREATE_FUNC(ShowLayer);
	//暂停层
	CC_SYNTHESIZE(SuspendLayer *, suLayer, M_suLayer);
	//结束层
	CC_SYNTHESIZE_READONLY(GameOverLayer *, gameOverLayer, M_gameOverLayer);
protected:
	//将成员变量suLayer置为空
	void setLayerNull(Ref * sender);
	//增加右侧双倍积分提示
	void addBostZone();
	//增加双倍积分标示
	void addDoubleScoreIcon();
	//增加帮助层
	void addHelpLayerByOneGame();
	//增加任务层
	void addTastLayer();
	//增加暂停按钮
	void addPauseIcon();
	//增加顶部图标
	void addTopIcon();
	//添加分数值及条件值
	void addScoreLabel();
	//增加木条
	void addTopbar();
	//增加当前分数
	void increaseCurScore(float t);
	virtual bool init();
	//注册通知，接收通知
	void addNotification();
	//增加当前分数50
	void addCurScore(Ref * sender);
	//100分
	void addMoreCurScore(Ref * sender);
	//增加双倍积分时间
	void doubleScore(Ref * sender);
	//金牌双倍积分时间
	void glodDoubleScore(Ref * sender);
	//近距离双倍积分
	void bostZoneDoubleScore(Ref * sender);
	//取消近距离双倍积分
	void deleteBostZoneDoubleScore(Ref * sender);
	//创建结束层
	void createGameOverLayer(Ref * sender);
	//双倍积分时间计时
	void doubleScoreUpdate(float t);
	void onEnter();
	~ShowLayer();

protected:
	//双倍积分标示
	Sprite * douScore;
	//音效开关
	int audioFlag;
	//当前分数及最高分Label
	Label * curScoreLabel;
	Label * maxScoreLabel;
	//当前分数及最高分数
	int curScore;
	int maxScore;
	//当前分数增量
	int timeScore;
	int fiftyScore;
	//双倍积分计时
	int doubleScoreCount;
	Role *role;
	bool flag;
};

#endif // !__SHOWLAYER_H_
