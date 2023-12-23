#include "mapUtil.h"

MapUtil* MapUtil::gInstance;

MapUtil::~MapUtil()
{
    CC_SAFE_DELETE(pMovePosMap);
    CC_SAFE_DELETE(pBarrierPosMap);
    CC_SAFE_DELETE(pEffectTowerRectVec);
    CC_SAFE_RELEASE_NULL(pTildeMap);
}

bool MapUtil::init()
{
    bool bRet = false;

    do
    {
        pBarrierPosMap = new std::vector<std::pair<std::string, Rect>>;
        pEffectTowerRectVec = new std::vector<Rect>;
        pMovePosMap = new std::map<int, Vec2>;

        bRet = true;
    } while (0);

    return bRet;
}

void MapUtil::setCurrentLevelTiledMap(cocos2d::TMXTiledMap* pTiledMap)
{
    clearMap();
    CC_SAFE_RELEASE_NULL(pTildeMap);
    CC_SAFE_RETAIN(pTiledMap);
    pTildeMap = pTiledMap;
    gridSize = pTildeMap->getTileSize();
    mapSize = Size(pTildeMap->getMapSize().width * gridSize.width, pTildeMap->getMapSize().height * gridSize.height);

    auto tMapGroup = pTildeMap->getObjectGroup("PATH");
    auto tObjs = tMapGroup->getObjects();

    for (auto& iter : tObjs)
    {
        auto tObjMap = iter.asValueMap();
        auto tObjName = tObjMap.at("name").asString();
        auto tX = tObjMap.at("x").asFloat();
        auto tY = tObjMap.at("y").asFloat();
        auto tPos = Vec2(tX, tY);
        auto tWidth = tObjMap.at("width").asFloat();
        auto tHeight = tObjMap.at("height").asFloat();
        auto tRect = Rect(tX, tY, tWidth, tHeight);

        if (tObjName.find("PT") != std::string::npos)
        {
            pMovePosMap->insert(std::make_pair(atoi(tObjName.substr(2).c_str()), tPos));
            continue;
        }
        if (tObjName.find("Obj") != std::string::npos)
        {
            rectTransVec(tRect);
            continue;
        }

        auto tIndex = tObjName.find("Ob");
        if (std::string::npos != tIndex)
        {
            pBarrierPosMap->push_back(std::make_pair(tObjName.substr(0, tIndex + 2), tRect));
            continue;
        }

        pEffectTowerRectVec->push_back(tRect);
    }
}

void MapUtil::clearMap()
{
    pEffectTowerRectVec->clear();
    pBarrierPosMap->clear();
    pMovePosMap->clear();
}

void MapUtil::rectTransVec(const Rect& rRect)
{
    auto tWidth = rRect.size.width;
    auto tHeight = rRect.size.height;
    auto tX = rRect.origin.x;
    auto tY = rRect.origin.y;
    if (TILESIZE == tWidth && TILESIZE == tHeight)
    {
        pEffectTowerRectVec->push_back(Rect(tX, tY, gridSize.width, gridSize.height));
        return;
    }
    if (tWidth > TILESIZE && tHeight > TILESIZE)
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i)
        {
            for (int j = 0; j < tHeight / TILESIZE; ++j)
            {
                pEffectTowerRectVec->push_back(Rect(tX + TILESIZE * i, tY + TILESIZE * j, TILESIZE, TILESIZE));
            }
        }
        return;
    }

    if (tWidth > TILESIZE)
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i)
        {
            pEffectTowerRectVec->push_back(Rect(tX + i * TILESIZE, tY, gridSize.width, gridSize.height));
        }
    }

    if (tHeight > TILESIZE)
    {
        for (int i = 0; i < tHeight / TILESIZE; ++i)
        {
            pEffectTowerRectVec->push_back(Rect(tX, tY + i * TILESIZE, gridSize.width, gridSize.height));
        }
    }
}

std::vector<Vec2> MapUtil::getMovePoses()
{
    std::vector<Vec2> tRetMovePosVec;
    for (auto& iter : *pMovePosMap)
        tRetMovePosVec.push_back(iter.second);

    return tRetMovePosVec;
}

std::vector<Rect> MapUtil::getEffectTowerPoses()
{
    return *pEffectTowerRectVec;
}

std::vector<std::pair<std::string, Rect>> MapUtil::getBarrierPoses()
{
    return *pBarrierPosMap;
}

void MapUtil::removeBarrierRect(const Vec2& rPos)
{
    for (auto barrierIter = pBarrierPosMap->begin(); barrierIter != pBarrierPosMap->end(); ++barrierIter)
    {
        auto tBarrier = *barrierIter;
        if (tBarrier.second.containsPoint(rPos))
        {
            rectTransVec(tBarrier.second);
            pBarrierPosMap->erase(barrierIter);
            break;
        }
    }
}




