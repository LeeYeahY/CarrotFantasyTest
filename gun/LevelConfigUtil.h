#ifndef _levelConfigUtil_
#define _levelConfigUtil_

#include "PublicDefine.h"

class LevelConfigUtil :public Ref
{
public:

    CREATE_INSTANCE_FUNC(LevelConfigUtil);

    DESTROY_INSTANCE_FUNC();

    virtual void loadLevelConfig();

    virtual std::tuple<int, int, int, std::vector<std::string>> getLevelConfig()const;

    virtual std::vector<std::string> getCurLevelTowersInfo()const;

    virtual int getCurLevelMonsterBatchCount()const;

    virtual void buildLevelConfig();

    virtual int getCurLevelMoney()const;

protected:

    virtual bool init();

protected:

    int iCurPageIndex = 0;

    int iCurLevelIndex = 0;

    int iCurLevelMoney = 0;

    int iMonsterBatchCount = 0;

    std::vector<std::string>* pEffectTowers = nullptr;

private:

    LevelConfigUtil();

    virtual ~LevelConfigUtil();

    LevelConfigUtil(const LevelConfigUtil&) = delete;

    LevelConfigUtil& operator=(const LevelConfigUtil&) = delete;
};

#endif
