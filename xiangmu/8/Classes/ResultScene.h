#pragma once

#include "AppMacro.h"

class ResultScene : public Layer {
private:
	Text *m_scoreTxt;

	Text *m_maxScoreTxt;
protected:
	bool init(float score);

	void initUi();
public:
	static ResultScene *create(float score);

	static Scene *createScene(float score);
};