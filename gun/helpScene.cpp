#include "helpScene.h"
#include "helpMenuPanelLayer.h"

HelpScene::~HelpScene()
{
    CC_SAFE_RELEASE_NULL(pMenuPanelLayer);
}

bool HelpScene::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Scene::init());

        pMenuPanelLayer = HelpMenuPanelLayer::create();
        pMenuPanelLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void HelpScene::onEnter()
{
    Scene::onEnter();
    addChild(pMenuPanelLayer);
}