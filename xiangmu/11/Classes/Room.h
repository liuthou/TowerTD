//
//  Room.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//  袁文龙 2014年9约18日 更新
//

#ifndef __TexasPoker__Room__
#define __TexasPoker__Room__


#include <iostream>

#include <cocos2d.h>
using namespace cocos2d;

#include "Player.h"
#include "Poker.h"

#include <cocostudio/CocoStudio.h>
using namespace cocostudio;

#include <ui/CocosGUI.h>
using namespace ui;

namespace TexasPoker {

    class ProcessControl;
    class Hall;
    
    
    /**房间*/
    class Room : public Layer{
    public:
        void initUI();
        void intiAudio();
        virtual void onEnter();
        
        /**
         荷官
         */
        void initDila();
        
			/**创建 Room 场景*/
			static Scene * createScene(int id,int ScoreMax,int ScoreMin);

			/**创建 Room*/
			static Room * create(int _id,int ScoreMax,int ScoreMin);

			/**重写 Room 的 init 方法*/
			virtual bool init(int _id,int ScoreMax,int ScoreMin);

			/**onEnterTransitionDidFinish 方法*/
			void onEnterTransitionDidFinish();

		public:
			/**获得房间ID*/
			int getID();
        
			/**获得流程控制器*/
			//ProcessControl * getProcessControl();
        
			/**获得最多可携带最高金额*/
			int getScoreMax();
        
			/**获得最低下注金额*/
			int getScoreMin();
        
			/**获得座位 1-9*/
			//Map<int, Player *> getChairs(); 修改如下
			Map<int, Player *> getChairs_Players();

			//void setChairs(int chairId, Player *player);
        
        
			/**获得玩家数量*/
			int getPlayerCount();
        
			/**坐在椅子上
			 1. 当坐1个玩家以上触发 
			 processControl->Start();
			 */
			bool Site(Player * player);
        
			/**获得奖池*/
			int getPot();
        
			/**
			 *  获取庄家椅子编号
			 *
			 *  @return 返回一个1-9内的数字
			 */
			int getDealerPlayerChair();
        
			/**
			 *  设置庄家的椅子编号
			 */
			void setDealerPlayerChair();
        
        /**
         *  让荷官做tip动画
         */
        void startDilaTip();
        
        /**
         *  停止荷官动画
         */
        void stopDilaTip();
        
        
        /**
         *  根据椅子号
         *
         *  @param chairNumber 椅子号
         *
         *  @return 返回玩家在桌面上的ITEM
         */
        MenuItemSprite * & getPlayerItemByChairNumber(int chairNumber);
        
        
        Player * getPlayerByChairNumber(int chairNumber);
        
        
		protected:
			/**房间ID*/
			int ID;
        
			/**最多可携带最高金额*/
			int ScoreMax;
        
			/**最低下注金额*/
			int ScoreMin;
        
			/**座位 1-9*/
			Map<int, Player *> Chairs_Players;
        
			/**庄家的椅子编号 (0)*/
			int DealerPlayerChair;
        
			/**玩家数量*/
			int PlayerCount;
        
			/**流程控制*/
			ProcessControl *processControl;
            
			/**奖池*/
			int Pot;
        
        /**
         *  用来展示桌面上的玩家
         */
        Menu * playerMenu;
        MenuItemSprite* playerItem1;
        MenuItemSprite* playerItem2;
        MenuItemSprite* playerItem3;
        MenuItemSprite* playerItem4;
        MenuItemSprite* playerItem5;
        MenuItemSprite* playerItem6;
        MenuItemSprite* playerItem7;
        MenuItemSprite* playerItem8;
        MenuItemSprite* playerItem9;
        
        /**
         初始化菜单
         */
        void initPlayerMenu();

        

        
        Armature * Dila;
        
        /**游客数组*/
        Vector<Player *> Guests;
    
        /**河牌;最大有5张*/
        Vector<Poker *> riverPokers;
        
    private:
        /**
         *  设置玩家的item在屏幕上的坐标
         *
         *  @param chairNumber 椅子号
         */
        void setPlayerItemPositionByChairNumber(int chairNumber);
        
        /**
         *  Site()函数的工具函数,给予玩家一个MenuItem
         *
         *  @param player 传入一个需要左下的玩家
         */
        void setPlayerMenu(Player* player);
    
    private:
        /**
         *  语音按钮
         */
        Button * VoiceButton;
        void onTouchVoiceButton(Ref*ref,ui::Widget::TouchEventType type);
    };
}

#endif /* defined(__TexasPoker__Room__) */
