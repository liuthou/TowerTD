//
//  Config.cpp
//  TexasPoker
//
//  Created by Ô¬ÎÄÁú on 14-9-13.
//
//

#include "Config.h"
#include <cocos2d.h>
using namespace cocos2d;
using namespace TexasPoker;
using namespace TexasPoker::Config;

LANGUAGE * LANGUAGE::instance = nullptr;
LANGUAGE * LANGUAGE::getInstance(){
    if(instance == nullptr){
        instance = new LANGUAGE();
        std::string fullFileName ;
        
//        if(cocos2d::Application::getInstance()->getCurrentLanguage()
//           == cocos2d::LanguageType::CHINESE
//           ){
            fullFileName = FileUtils::getInstance()->fullPathForFilename("LANGUAGE/zh.plist");
//        }
        
        instance->language = FileUtils::getInstance()->getValueMapFromFile(fullFileName);
    }
    return instance;
}

cocos2d::Value LANGUAGE::AT(std::string value){
    return language.at(value);
}

cocos2d::ValueMap LANGUAGE::getValueMap(){
    return language;
}