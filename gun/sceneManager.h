#ifndef _sceneManager_
#define _sceneManager_

#include "publicDefine.h"

class SceneManager :public Node
{
public:

    CREATE_INSTANCE_FUNC(SceneManager);

    DESTROY_INSTANCE_FUNC();

    virtual void initWelComeScene();

    virtual int getCurPageIndex()const;

    virtual int getCurLevelIndex()const;

protected:

    virtual void changeScene(const std::tuple<SceneType, int>& rEnSceneType);

    virtual void notifyChangeScene(Ref* pData);

    virtual void registerChangeSceneEvent();

    virtual void unRegisterAllEvent();

    virtual void checkCurPageAndLevel();

    virtual bool init();

protected:

    enum SceneType enCurSceneR = SceneType(0);//SceneType(0)Ϊen_WelcomeScene

private:

    int iCurPageIndex = 0;

    int iCurLevelIndex = 0;

private:

    SceneManager() {}

    virtual ~SceneManager() {}

    SceneManager(const SceneManager&) = delete;

    SceneManager& operator=(const SceneManager&) = delete;

};

#endif