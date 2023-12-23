#include "pageSelectScene.h"
#include "pageViewLayer.h"
#include "menuPanelLayer.h"

PageSelectScene::~PageSelectScene()
{
    CC_SAFE_RELEASE_NULL(pPageViewLayer);
    CC_SAFE_RELEASE_NULL(pMenuPanelLayerR);
}

bool PageSelectScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        pPageViewLayer = PageViewLayer::create();
        pPageViewLayer->retain();

        pMenuPanelLayerR = MenuPanelLayer::create();
        pMenuPanelLayerR->retain();

        auto pMenuPanelLayer = dynamic_cast<MenuPanelLayer*>(pMenuPanelLayerR);
        pMenuPanelLayer->setPageTurnFunc(CC_CALLBACK_1(PageViewLayer::pageTurn, dynamic_cast<PageViewLayer*>(pPageViewLayer)));

        bRet = true;
    } while (0);

    return bRet;
}

void PageSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(pPageViewLayer);
    addChild(pMenuPanelLayerR);
}