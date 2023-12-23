#include "tiledMapLayer.h"
#include "sceneManager.h"
#include "mapUtil.h"

bool TiledMapLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        loadSource();

        bRet = true;
    } while (0);

    return bRet;
}

void TiledMapLayer::loadSource()
{
    auto pSceneManager = SceneManager::getInstance();

    auto pageLevelStr = StringUtils::format(GAMESCENEMAP, pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1) + "BGPath.tmx";
    pTiledMap = TMXTiledMap::create(pageLevelStr);
    addChild(pTiledMap);

    MapUtil::getInstance()->setCurrentLevelTiledMap(pTiledMap);

    auto pBg = Sprite::createWithSpriteFrameName("BG1.png");
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    auto pMapImage = Sprite::createWithSpriteFrameName("Path.png");
    pMapImage->setPosition(VisibleRect::center());
    addChild(pMapImage);
}