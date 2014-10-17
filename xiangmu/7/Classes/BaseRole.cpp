#include "BaseRole.h"


BaseRole *BaseRole::create(std::string fileName){
	BaseRole *baserole = new BaseRole();
	if (baserole && baserole->initWithSpriteFrameName(fileName))
	{
		baserole->autorelease();
		return baserole;
	}

	CC_SAFE_DELETE(baserole);
	return NULL;
}

bool BaseRole::initWithSpriteFrameName(std::string fileName){
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	
	m_hp = 0;					//血量
	
	m_speed = 0;				//速度
	
	
	m_attack = 0;					//攻击了（主角的攻击力为0）

	m_state = false;			//设置状态

	return true;
}

void BaseRole::move(){					//移动   虚函数

}

void BaseRole::jump(){						//跳  虚函数

}

void BaseRole::hurt(){					// 虚函数

}

void BaseRole::die(){					  //死亡  虚函数

}

void BaseRole::bornAnimate(){				// 出生动画  虚函数

}

//死亡动画   通过子类传过给基类照片来做死亡动画
void BaseRole::dieRunAnimation(const char *fileNames,...){	

	Animation *ani = Animation::create();			//创建动画
	
	this->stopAllActions();		//停止当前对象的所有的动画

	//播放死亡动画

	va_list args;			//存放照片的集合的对象

	va_start(args,fileNames);				//将传过来的照片放在集合 args 中

	if (!fileNames)			//如果图片为空
	{
		return;
	}

	SpriteFrame *frame;
	const char *fileStr;
	fileStr = va_arg(args,const char *);		//fileName是首地址（即第一个元素）

	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileStr);		
	ani->addSpriteFrame(frame);

	while (!fileStr){
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileStr);
		ani->addSpriteFrame(frame);
		fileStr = va_arg(args,const char *);

	}

	va_end(args);

	//运行动画

	ani->setDelayPerUnit(0.1);
	ani->setLoops(1);
	auto fun = CCCallFunc::create(std::bind(&BaseRole::remove,this));

	this->runAction(Sequence::create(Animate::create(ani),fun,NULL));		//串行动画

}

//移除方法
void BaseRole::remove(){
	this->removeFromParentAndCleanup(true);
}
