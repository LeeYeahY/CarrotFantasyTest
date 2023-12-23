#include "sceneFactory.h"
#include "welcomeScene.h"
#include "pageSelectScene.h"
#include "levelSelectScene.h"
#include "gameSettingScene.h"
#include "loadingScene.h"
#include "helpScene.h"
Scene* SceneFactory::createScene(const SceneType& rEnSceneType)
{
    Scene* pScene = nullptr;

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
