#include "sceneManager.h"
#include "sceneFactory.h"
#include "soundUtil.h"

SceneManager* SceneManager::gInstance;

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent();

        bRet = true;
    } while (0);
    return bRet;
}

void SceneManager::initWelComeScene()
{
    auto enCurScene = std::make_tuple(enCurSceneR, 0);
    changeScene(enCurScene);
}

void SceneManager::unRegisterAllEvent()
{
    NOTIFY->removeAllObservers(this);
}

void SceneManager::changeScene(const std::tuple<SceneType, int>& rEnSceneType)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);

    auto tSceneType = std::get<0>(rEnSceneType);

    if (en_GameScene == tSceneType) iCurLevelIndex = std::get<1>(rEnSceneType);

    if (en_LevelSelectScene == tSceneType) iCurPageIndex = std::get<1>(rEnSceneType);

    if (en_GameScene != tSceneType) SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());

    checkCurPageAndLevel();

    auto pScene = SceneFactory::createScene(tSceneType);

    auto pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();

    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);
}

void SceneManager::checkCurPageAndLevel()
{
    auto tCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[iCurPageIndex];
    if (tCurPageLevelCount == iCurLevelIndex)
    {
        ++iCurPageIndex;
        iCurLevelIndex = 0;
    }
}

void SceneManager::notifyChangeScene(Ref* pData)
{
    auto enSceneType = *(reinterpret_cast<std::tuple<SceneType, int> *>(pData));
    changeScene(enSceneType);
}

void SceneManager::registerChangeSceneEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(SceneManager::notifyChangeScene), "changeScene", nullptr);
}

int SceneManager::getCurPageIndex()const
{
    return iCurPageIndex;
}

int SceneManager::getCurLevelIndex()const
{
    return iCurLevelIndex;
}