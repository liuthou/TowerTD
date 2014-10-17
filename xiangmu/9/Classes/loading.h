#ifndef __LOADING_H
#define __LOADING_H
#include "cocos2d.h"
using namespace cocos2d;
class Loading:public Layer
{
private:
	LabelTTF* loading;
	std::string _xmlName;
	bool _IsOk;
	int _count;
	Size vSize;
protected:
	void update(float t);
	void addCat();
	void addPlist();
      void onEnter();
public:
	static Scene * createScene(std::string xmlName);
	static Loading * create(std::string xmlName);
	virtual bool init(std::string xmlName);
};
#endif