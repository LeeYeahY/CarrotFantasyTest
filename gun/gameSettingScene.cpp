#include "gameSettingScene.h"
#include "topPanelLayer.h"

GameSettingScene::~GameSettingScene()
{
    CC_SAFE_RELEASE_NULL(pPanelLayer);
}

bool GameSettingScene::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Scene::init());

        pPanelLayer = TopPanelLayer::create();
        pPanelLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void GameSettingScene::onEnter()
{
    Scene::onEnter();

    addChild(pPanelLayer);
}