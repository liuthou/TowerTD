//
//  SceneFactory.cpp
//  newCardDefence
//
//  Created by Yan on 14-8-28.
//
//

#include "SceneFactory.h"
#include "WelcomeScene.h"
#include "PageSelectScene.h"
#include "LevelSelectScene.h"
#include "GameSettingScene.h"
#include "LoadingScene.h"
#include "HelpScene.h"
Scene *SceneFactory::createScene(const SceneType &rEnSceneType)
{
    Scene *pScene = nullptr;
    
    switch (rEnSceneType)
    {
        case en_WelcomeScene:
            pScene = WelcomeScene::create();
            break;
        case en_GameHelpScene:
            pScene = HelpScene::create();
            break;
        case en_PageSelectScene:
            pScene = PageSelectScene::create();
            break;
        case en_LevelSelectScene:
            pScene = LevelSelectScene::create();
            break;
        case en_GameSettingScene:
            pScene = GameSettingScene::create();
            break;
        case en_GameScene:
            pScene = LoadingScene::create();
            break;
        default:
            break;
    }
    return pScene;
}
