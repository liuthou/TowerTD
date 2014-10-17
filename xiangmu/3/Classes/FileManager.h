/**

* 类名：FileManager

* 作者：

* 日期：

* 作用 : 负责生成接受正常文件,收集足够文件,过关以及被病毒攻击时扣血,血量扣光,游戏失败.

**/ 
#ifndef __FILEMANAGER_H_
#define __FILEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
class FileManager:public Node{
public:
	CREATE_FUNC(FileManager);
	virtual bool init();
	//需要的总文件数量
	CC_SYNTHESIZE(int,fileneed,FileNeed);
	//当前收到的文件数量
	CC_SYNTHESIZE(int,filereceived,FileReceived);
protected:
	//按固定时间(或者随着怪物波次)出现文件
	void createFile(float dt);
	Vec2 monsterCreatePosition();
};
#endif