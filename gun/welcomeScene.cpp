#include "welcomeScene.h"
#include "spritesLayer.h"
#include "menusLayer.h"
#include "loadingSourceLayer.h"
#include "Config.h"

WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(pMenusLayer);
    CC_SAFE_RELEASE_NULL(pSpritesLayer);
}

bool WelcomeScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        pSpritesLayer = SpritesLayer::create();
        pSpritesLayer->retain();

        pMenusLayer = MenusLayer::create();
        pMenusLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(pSpritesLayer);

    if (!Config::getInstance()->getIsLoadSource())
    {
        auto pLoadingLayer = LoadingSourceLayer::create();
        pLoadingLayer->setFuncShowMenuPanel(CC_CALLBACK_0(WelcomeScene::showMenu, this));
        pLoadingLayer->setName("loadingLayer");
        addChild(pLoadingLayer);
    }
    else
    {
        addChild(pMenusLayer);
    }
}


void WelcomeScene::showMenu()
{
    getChildByName("loadingLayer")->removeFromParent();
    addChild(pMenusLayer);
    Config::getInstance()->setIsLoadSource(true);
}