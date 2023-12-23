#include "levelSelectScene.h"
#include "levelSelectLayer.h"
#include "sceneManager.h"

LevelSelectScene::~LevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(pLevelSelectLayer);
    sourceManager(std::vector<std::string>{THEMESSOURCE[iThemeIndex]}, false);

}

bool LevelSelectScene::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Scene::init());
        iThemeIndex = SceneManager::getInstance()->getCurPageIndex();
        sourceManager(std::vector<std::string>{THEMESSOURCE[iThemeIndex]}, true);

        pLevelSelectLayer = LevelSelectLayer::create();
        pLevelSelectLayer->retain();
        bRet = true;
    } while (0);

    return bRet;
}

void LevelSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(pLevelSelectLayer);
}