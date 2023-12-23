#ifndef _mapUtil_
#define _mapUtil_

#include "publicDefine.h"

class MapUtil : public Ref
{
public:

    CREATE_INSTANCE_FUNC(MapUtil);

    DESTROY_INSTANCE_FUNC();

    virtual void setCurrentLevelTiledMap(TMXTiledMap* pTiledMap);

    virtual std::vector<Vec2> getMovePoses();

    virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses();

    virtual std::vector<Rect> getEffectTowerPoses();

    virtual void removeBarrierRect(const Vec2& rPos);

protected:

    virtual bool init();

    virtual void clearMap();

    virtual void rectTransVec(const Rect& rRect);

private:

    TMXTiledMap* pTildeMap = nullptr;

    std::map<int, Vec2>* pMovePosMap = nullptr;

    std::vector<std::pair<std::string, Rect>>* pBarrierPosMap = nullptr;

    std::vector<Rect>* pEffectTowerRectVec = nullptr;

private:

    Size gridSize;
    Size mapSize;

private:

    virtual ~MapUtil();

};

#endif
