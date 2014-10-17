#pragma once

#include "AppMacro.h"

class ScoreLayer;
class ControlLayer;
class GameLayer;
class MainPlane;

typedef enum {
	GAME_LAYER = 0,
	CONTROL_LAYER,
	SCORE_LAYER
} LayerZorders;

class MainScene : public Scene {
protected:
	ScoreLayer *m_scoreLayer;

	ControlLayer *m_controlLayer;

	GameLayer *m_gameLayer;
protected:
	virtual bool init();

	virtual void onEnter();
public:
	CREATE_FUNC(MainScene);

	void start();
	
private:
	void initLayers();

	/* ×¢²áÅö×²´¦Àíº¯Êý */
	void registerCollisionHandlers();
};