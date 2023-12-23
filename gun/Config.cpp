#include "Config.h"
#include "soundUtil.h"


Config* Config::gInstance;

Config::~Config()
{
}

Config::Config()
{

}

bool Config::init()
{
    bool bRet = false;
    do
    {
        sConfigFileName = FileUtils::getInstance()->getWritablePath() + CONFIGFILE;

        configValueMap = FileUtils::getInstance()->getValueMapFromFile(sConfigFileName);

        bIsLoadSource = false;

        checkBuildLevelData();

        bRet = true;
    } while (0);

    return bRet;
}

void Config::checkBuildLevelData()
{
    auto tRet = configValueMap[BUILDLEVELDATAKEY].asString();
    auto tIsBuildLevelData = 0;
    if (tRet.size()) tIsBuildLevelData = configValueMap[BUILDLEVELDATAKEY].asInt();
    if (!tRet.size() && !tIsBuildLevelData)
    {
        log("123");
        configValueMap[BUILDLEVELDATAKEY] = "1";
        FileUtils::getInstance()->writeToFile(configValueMap, sConfigFileName);
        createLevelDataFile();
    }
}

void Config::createLevelDataFile()
{
    auto tLevelDataFileName = FileUtils::getInstance()->getWritablePath() + DATAFILE;

    auto pCsvUtil = CsvUtil::getInstance();
    auto tColumnRow = pCsvUtil->getFileRowColNum(LEVELCSVFILE);

    auto tColumn = std::get<0>(tColumnRow);
    auto tRow = std::get<1>(tColumnRow);
    auto tValue = FileUtils::getInstance()->getValueMapFromFile(tLevelDataFileName);

    for (int i = 1; i < tRow; ++i)
    {
        auto tThemeIndex = pCsvUtil->getInt(i, 0, LEVELCSVFILE);
        auto tLevelIndex = pCsvUtil->getInt(i, 1, LEVELCSVFILE);
        auto tCarrotType = pCsvUtil->getInt(i, tColumn - 2, LEVELCSVFILE);
        auto tBarrierClean = pCsvUtil->getInt(i, tColumn - 1, LEVELCSVFILE);

        tValue[StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex)] = StringUtils::format("%d%d", tCarrotType, tBarrierClean);
    }

    FileUtils::getInstance()->writeToFile(tValue, tLevelDataFileName);
    saveSoundConfig();
}

void Config::saveSoundConfig()
{

    auto tBackGroundSoundFlag = SoundUtil::getInstance()->getIsBackGroundSound() ? 1 : 0;
    configValueMap[CONFIGBACKGROUND] = tBackGroundSoundFlag;

    auto tEffectSoundFlag = SoundUtil::getInstance()->getIsEffectSound() ? 1 : 0;
    configValueMap[CONFIGEFFECTSOUND] = tEffectSoundFlag;
    FileUtils::getInstance()->writeToFile(configValueMap, sConfigFileName);
}

void Config::setSoundConfig()
{
    SoundUtil::getInstance()->setIsBackGroundSound(configValueMap[CONFIGBACKGROUND].asBool());
    SoundUtil::getInstance()->setIsEffectSound(configValueMap[CONFIGEFFECTSOUND].asBool());
}