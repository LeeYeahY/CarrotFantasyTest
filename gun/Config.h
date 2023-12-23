#ifndef _Config_
#define _Config_

#include "publicDefine.h"

class SoundUtil;

class Config :public Ref
{
public:

    CREATE_INSTANCE_FUNC(Config);

    DESTROY_INSTANCE_FUNC();
   
    CC_SYNTHESIZE_PASS_BY_REF(bool, bIsLoadSource, IsLoadSource);

    virtual void saveSoundConfig();

    virtual void setSoundConfig();

protected:

    virtual bool init();

    virtual void checkBuildLevelData();

    virtual void createLevelDataFile();
private:

    std::string sConfigFileName = "";

    std::string sLevelDataFileName = "";

    ValueMap configValueMap;

private:

    Config();

    virtual ~Config();

    Config& operator=(const Config&) = delete;

    Config(const Config&) = delete;
};

#endif
