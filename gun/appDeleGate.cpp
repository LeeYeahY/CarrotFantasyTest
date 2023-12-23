#include "appDeleGate.h"
#include "sceneManager.h"
#include "csvUtil.h"
#include "config.h"
#include "gameScene.h"
#include "SoundUtil.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SceneManager::destroyInstance();
    Config::getInstance()->saveSoundConfig();
    Config::destroyInstance();
    SoundUtil::destroyInstance();
    unLoadSource();
}

bool AppDelegate::applicationDidFinishLaunching() {
    //初始化director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::EXACT_FIT);

    // 设置帧率 默认值为  1.0/60 
    director->setAnimationInterval(1.0 / 60);
    preLoadSource();
    Config::getInstance()->setSoundConfig();

    SceneManager::getInstance()->initWelComeScene();

    return true;
}
//这个函数会被调用当此应用中途停止
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
//这个函数会被调用当此应用中途停止以后再次开启
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    auto pCurScene = Director::getInstance()->getRunningScene();
    if ((pCurScene != NULL) && pCurScene->getName() == "GameScene")
    {
        auto pGameScene = dynamic_cast<GameScene*>(pCurScene);
        if (!pGameScene->getChildByName("CoundDown") && !pGameScene->getChildByName("GameEnd"))
            dynamic_cast<GameScene*>(pCurScene)->clickChooseItem();
    }
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::preLoadSource()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Themes/scene/mainscene1-hd.plist", "Themes/scene/mainscene1-hd.png");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Themes/scene/themescene1-hd.plist", "Themes/scene/themescene1-hd.png");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Themes/Items/Items00-hd.plist", "Themes/Items/Items00-hd.png");
    auto pCsvUtil = CsvUtil::getInstance();
    pCsvUtil->addFileData(BARRIERCSVFILE);
    pCsvUtil->addFileData(TOWERCSVFILE);
    pCsvUtil->addFileData(MONSTERCSVFILE);
    pCsvUtil->addFileData(BULLETCSVFILE);
    pCsvUtil->addFileData(LEVELCSVFILE);
}


void AppDelegate::unLoadSource()
{
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    CsvUtil::destroyInstance();
}






