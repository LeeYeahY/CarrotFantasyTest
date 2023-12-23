#ifndef _localDataUtil_
#define _localDataUtil_

#include "publicDefine.h"

class LocalDataUtil : public Ref
{
public:

    CREATE_INSTANCE_FUNC(LocalDataUtil);

    DESTROY_INSTANCE_FUNC();

    virtual ValueMap& getLevelData();

    virtual void setLevelData(const ValueMap& rValueMap);

protected:

    virtual bool init();

    virtual void registerLevelDataChangeEvent();

    virtual void levelDataChange(Ref* pData);

private:

    ValueMap levelData;

    std::string sLevelDataFileName = "";

private:

    LocalDataUtil() {}

    virtual ~LocalDataUtil();

    LocalDataUtil(const LocalDataUtil&) = delete;

    LocalDataUtil& operator=(const LocalDataUtil&) = delete;



};

#endif