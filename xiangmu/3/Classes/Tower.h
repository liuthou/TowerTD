#ifndef __TOWER_H_
#define __TOWER_H_
#include "cocos2d.h"
#include "Tower.h"
#include "TowerAI.h"
#include "GlobalInfo.h"
using namespace cocos2d;
class Tower:public Sprite{
public:
	virtual bool init(int id);
	static Tower*create(int id);
	CC_SYNTHESIZE(int, hp,Hp);//塔的血量
	CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线
	CC_SYNTHESIZE(float, attack, Attack);   // 杀伤力
	CC_SYNTHESIZE(bool,isdie,Isdie);
	CC_SYNTHESIZE(float,firespeed,FireSpeed);//开火速度
	//子弹移动速度
	CC_SYNTHESIZE(int,buspeed,BuSpeed);
	//子弹攻击力
	CC_SYNTHESIZE(int,buattackValue,BuattackValue);
	//子弹名
	CC_SYNTHESIZE(std::string,buName,BuName );
	//塔的防御力
	CC_SYNTHESIZE(int,def ,Def);
	//塔价格
	CC_SYNTHESIZE(int,price,Price);
	//攻击特效
	CC_SYNTHESIZE(attackEffect,atteffect,AttEffect);
	virtual void fire(Sprite* monster);//塔的开火方法
	void towerhurt(int monsterAttack);
	void remove();
	virtual  void die();
	void onEnter();
	
protected:
	
	TowerAI* ai;
	 Tower(){
		 hp =0;
		 scope = 0;
		 attack =0;		
		 isdie = false;
		 ai=nullptr;
		atteffect.firetime = 0;
		atteffect.frozentime = 0;
		atteffect.lowspeedtime = 0;
	 }
    virtual~Tower(){
	}
};
#endif