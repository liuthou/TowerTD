//
//  Config.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//	 继尚  2014.9.19 修改 const static float versions = 1.0;
//
//

#ifndef __TexasPoker__Config__
#define __TexasPoker__Config__

#include <iostream>
#include <string.h>
#include <cocos2d.h>

namespace TexasPoker {

    namespace Config {
        static const bool DEBUG = true;
        
#ifndef TexasPoker_Config
#define TexasPoker_Config
class LANGUAGE{
public:
    static LANGUAGE * getInstance();
    cocos2d::Value AT(std::string value);
    cocos2d::ValueMap getValueMap();
private:
    static LANGUAGE * instance;
    cocos2d::ValueMap language;
};
#endif
        
        namespace APP {
            static const std::string name  = "TexasPoker";
            static const float versions = 1.0;
        }
        
        namespace DB{
            static const std::string ip = "127.0.0.1";
            static const int port = 8080;
        }
        
        static const float betTime = 10.0f;
    }
    
    
    
    
}


#endif /* defined(__TexasPoker__Config__) */
