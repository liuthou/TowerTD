//
//  Hall.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__Hall__
#define __TexasPoker__Hall__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Macros.h"
#include "Room.h"

namespace TexasPoker {
    
    /**大厅*/
    class Hall:public Layer{
    public:
        enum class HallType{
            CHINA
        };
	protected:
		/**大厅ID*/
		int ID;

		/**房间列表*/
		Map<int, Room *> Rooms;
        
		/**大厅类型====================???????????????????????*/
		/**最多可携带最高金额*/
		int ScoreLimit;
        
		/**最低下注金额*/
		int ScoreMin;

    public:
		
        /**创建房间*/
		static void createRoom();
        static void createRoom(HallType hType);
        
        /**随机大厅内的加入房间*/
		virtual  void joinRoom();
        /**根据房间ID加入房间*/
		virtual  void joinRoom(int roomID);
        
        
        CREATE_SCENE(Hall)
        CREATE_FUNC(Hall);
    private:
        virtual bool init();
        
        ~Hall();
    };
}
#endif /* defined(__TexasPoker__Hall__) */
