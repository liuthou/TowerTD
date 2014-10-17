#pragma once

#include "AppMacro.h"

/*
可以重置的层
*/
class BaseLayer : public Layer {
	CC_SYNTHESIZE(bool, started, Started);
public:
	/* 
	层的重置函数
	#参数1 arg: 重置时附带的参数，可以默认是NULL
	*/
	virtual void reset() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
};

