#ifndef __FORWARDLAYER_H_
#define __FORWARDLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class ForwardLayer:public Layer{
private:
	Label *label;
private:
	LabelTTF * m_pLabelLoading;
	LabelTTF * m_PlabelPerCent;
	//要下载的总数
	int m_nNumbers;
	//下载了的数量
	int m_NumberLoaded;
	ProgressTimer * loadProgress;
	~ForwardLayer();
public:
	CREATE_FUNC(ForwardLayer);
	virtual bool init();
public:
	//每下载一个文件 回调一次 增长进度条
	//percent应该位于(0,1)之间;
	void loadingCallBack(float percent);
	//减分 /判断分是否可以创建塔 cutsorce是
	 bool cutScore(int sorce);
	//加分
	 void plusScore(int sorce);
	 //初始分数
	 CC_SYNTHESIZE(int,cursorce,curSorce);
	 void onEnter();
	 //获取计分Label位置
	 Vec2 getScoreLabelPosition();
protected:
//     int A;
// 	int sumA;
// 	int sumB;
// 	int B;
	int showsorce;
	void stateSelecterA();
	void stateSelecterB();
	void resetScoreA(float t);
	void resetScoreB(float t);
};
#endif