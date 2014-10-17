#ifndef __HELPSCENE_H_
#define __HELPSCENE_H_

#include "Conf.h"

class HelpScene : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(HelpScene);
	static Scene *createScene();
protected:
	virtual void onEnter();
	void addHero();
	void addMonster();
	void addBoss();
	void addMenu();
	Size vSize;
	Sprite *hero;
	Sprite *monster;
	Sprite *boss;
	Label *label;
	Label *label2;
	Label *label3;
};

#endif