#pragma once

#include "AppMacro.h"

class Prop;

class MainPlane : public Sprite {
	CC_SYNTHESIZE(bool, m_normalState, NormalState);

	CC_SYNTHESIZE_READONLY(Size, m_originalPos, OriginalPos);

	CC_SYNTHESIZE_READONLY(Action*, m_move, MoveAction);
private:
	FiniteTimeAction *m_delay;
private:
	/* Move���� */
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
protected:
	virtual bool init();

	void initPhysicsBody();
public:
	CREATE_FUNC(MainPlane);
	
	// ע�ᶯ��
	void registerMainPlaneFuncs();

	//�Ե���
	void eatProp(Prop *prop);

	//��������
	void die();
	
	//���ú���
	void reset();

	void onEnter();
};
