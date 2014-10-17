//
//  TowerOptBtn.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__TowerOptBtn__
#define __CarrotFantasy__TowerOptBtn__

#include "cocos2d.h"
class TowerBase;
using namespace cocos2d;

class TowerOptBtn: public Node
{
public:
    
    CREATE_FUNC(TowerOptBtn);
    
    TowerOptBtn();
    
    virtual ~TowerOptBtn();
    
    virtual void hideTowerOpt();
    
    virtual void showTowerOpt();

	virtual void setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney);

	virtual void createTowerMenu();

	virtual void gradeTowerMenu(TowerBase* touchTower);

	virtual void showCreateMenu();

	virtual void hideCreateMenu();
protected:
    
    virtual bool init();
    
    virtual void createMenuAndItems();
    
	virtual void ChangingItem(float dt);

protected:
	bool _bKeySpVisible;
	Sprite* _pKeySp;
	Menu* _pCreateMenu1;
	Menu* _pCreateMenu2;
	Menu* _pGradeMenu;
	Sprite* _pTowerRangeSp;

	std::function<int()> _funcCheckMoney;
    
	Vector<MenuItemSprite *> *_pCreateTowerItemSpVec = nullptr;
	Vector<MenuItemSprite *> *_pGradeTowerItemSpVec = nullptr;
};


#endif /* defined(__CarrotFantasy__TowerOptBtn__) */
