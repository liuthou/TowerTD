#ifndef __EXORBSCENE_R_
#define __EXORBSCENE_R_


#include "cocos2d.h"
#include <sqlite3.h>
using namespace cocos2d;

//存储数据库文件
int fileCopy(const char *sreFileName,const char * path);

class ExorbitanceScene : Layer
{
private:
	//数据库
	sqlite3 * _pdb;
public:
	virtual bool init();
	static Scene * createScene();
	CREATE_FUNC(ExorbitanceScene);
private:
	//打开数据库
	void opendb();
	//查询数据库并将猪脚数据提取
	void queryHeroDb();
	//查询数据库并将技能的数据提取
	void querySkillDb();
	//查询数据库中装备的数据提取
	void queryGearDb();
	//加载音效
	void onEnter();
};

#endif