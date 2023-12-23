#include "localDataUtil.h"

LocalDataUtil* LocalDataUtil::gInstance;

bool LocalDataUtil::init()
{
    bool bRet = false;
    do
    {
        auto pFileUtil = FileUtils::getInstance();
        sLevelDataFileName = pFileUtil->getWritablePath() + DATAFILE;
        levelData = pFileUtil->getValueMapFromFile(sLevelDataFileName);

        registerLevelDataChangeEvent();
        bRet = true;
    } while (0);

    return  bRet;
}

LocalDataUtil::~LocalDataUtil()
{
    NOTIFY->removeAllObservers(this);
}

ValueMap& LocalDataUtil::getLevelData()
{
    return levelData;
}

void LocalDataUtil::setLevelData(const ValueMap& rValueMap)
{
    levelData = rValueMap;
    FileUtils::getInstance()->writeToFile(levelData, sLevelDataFileName);
}

void LocalDataUtil::registerLevelDataChangeEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(LocalDataUtil::levelDataChange), LEVELDATACHANGE, nullptr);
}

void LocalDataUtil::levelDataChange(Ref* pData)
{
    auto tLevelData = *(reinterpret_cast<std::tuple<int, int, int, int>*>(pData));
    auto tLevelType = std::get<0>(tLevelData);
    auto tData = std::get<1>(tLevelData);
    auto tThemeIndex = std::get<2>(tLevelData);
    auto tLevelIndex = std::get<3>(tLevelData);
    auto tLevelKey = StringUtils::format(LEVELKEY, tThemeIndex, tLevelIndex);
    auto tCurLevelData = levelData[tLevelKey].asInt();
    auto tCarrotType = tCurLevelData / 10;
    auto tBarrierCleanFlag = tCurLevelData % 10;

    if (!tLevelType)
    {
        if (tCarrotType < tData) levelData[tLevelKey] = StringUtils::format("%d%d", tData, tBarrierCleanFlag);
    }
    else
    {
        levelData[tLevelKey] = StringUtils::format("%d%d", tCarrotType, tData);
    }

    FileUtils::getInstance()->writeToFile(levelData, sLevelDataFileName);
}