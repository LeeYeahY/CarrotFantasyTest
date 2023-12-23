#include "GameScene.h"
#include "SceneManager.h"
#include "OptLayer.h"
#include "MonsterLayer.h"
#include "ScoreAndControlLayer.h"
#include "TiledMapLayer.h"
#include "TowersLayer.h"
#include "BarriersLayer.h"
#include "BulletsLayer.h"
#include "BulletManager.h"
#include "TowerManager.h"
#include "BarrierManager.h"
#include "MonsterManager.h"
#include "MapUtil.h"
#include "BarrierBase.h"
#include "CollisionManager.h"
#include "MonsterBuilder.h"
#include "TowerFactory.h"
#include "Carrot.h"
#include "TowerOptBtn.h"
#include "CountDownLayer.h"
#include "GameEndLayer.h"
#include "SoundUtil.h"
#include "LevelConfigUtil.h"

GameScene::~GameScene()
{
    CC_SAFE_RELEASE_NULL(pOptLayer);
    CC_SAFE_RELEASE_NULL(pScoreAndControllerLayer);
    CC_SAFE_RELEASE_NULL(pTowersLayer);
    CC_SAFE_RELEASE_NULL(pMonsterLayer);
    CC_SAFE_RELEASE_NULL(pBarriersLayer);
    CC_SAFE_RELEASE_NULL(pBulletsLayer);
    CC_SAFE_RELEASE_NULL(pTiledMapLayer);
    CC_SAFE_RELEASE_NULL(pCarrot);
    clearAllManager();
    CC_SAFE_DELETE(_pSourceVec);
}

bool GameScene::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Scene::init());

        _pSourceVec = new std::vector<std::string>;
        this->setName("GameScene");
        preLoadSource();

        bRet = true;

    } while (0);
    return bRet;
}

void GameScene::createLayers()
{
    pTiledMapLayer = TiledMapLayer::create();
    pTiledMapLayer->retain();

    pBarriersLayer = BarriersLayer::create();
    pBarriersLayer->retain();
    BarrierManager::getInstance()->setFuncAddBarrierToLayer(CC_CALLBACK_1(BarriersLayer::addEntity, pBarriersLayer));

    pMonsterLayer = MonsterLayer::create();
    pMonsterLayer->setName("monsterLayer");
    pMonsterLayer->retain();
    MonsterManager::getInstance()->setFuncAddMonsterToLayer(CC_CALLBACK_1(MonsterLayer::addEntity, pMonsterLayer));

    pTowersLayer = TowersLayer::create();
    pTowersLayer->retain();

    TowerManager::getInstance()->setFuncAddTowerLayer(CC_CALLBACK_1(TowersLayer::addEntity, pTowersLayer));

    pBulletsLayer = BulletsLayer::create();
    pBulletsLayer->setTag(1);
    pBulletsLayer->retain();
    BulletManager::getInstance()->setFuncAddBulletLayer(CC_CALLBACK_1(BulletsLayer::addEntity, pBulletsLayer));

    pScoreAndControllerLayer = ScoreAndControllerLayer::create();
    pScoreAndControllerLayer->retain();
    TowerManager::getInstance()->setFuncCheckMoney(CC_CALLBACK_0(ScoreAndControllerLayer::getCurMoney, dynamic_cast<ScoreAndControllerLayer*>(pScoreAndControllerLayer)));

    pOptLayer = OptLayer::create();
    pOptLayer->retain();
    dynamic_cast<TowerOptBtn*>(pOptLayer->getChildByName("towerOptBtn"))->setFuncCheckMoney(CC_CALLBACK_0(ScoreAndControllerLayer::getCurMoney, dynamic_cast<ScoreAndControllerLayer*>(_pScoreAndControllerLayer)));

    pCarrot = Carrot::create();
    pCarrot->retain();
}

void GameScene::preLoadSource()
{

    auto tICurPageIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
    auto tICurLevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
    auto tSSourceBg1Str = StringUtils::format(GAMESCENEBG1, tICurPageIndex);

    LevelConfigUtil::getInstance()->loadLevelConfig();

    _pSourceVec->push_back(StringUtils::format(GAMESCENEBG1, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMAP, tICurPageIndex, tICurLevelIndex) + "BG-hd");
    _pSourceVec->push_back(StringUtils::format(GAMESCENEBARRIER, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER1, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER2, tICurPageIndex));

    for (auto& iterSourceName : *_pSourceVec)
        Director::getInstance()->getTextureCache()->addImageAsync(iterSourceName + PHOTOPOSTFIX, [&](Texture2D* pTexture)
            {
                ++iSourceCount;
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, pTexture);
                if (iSourceCount == _pSourceVec->size())
                {
                    createLayers();
                    NOTIFY->postNotification("loadFinish", static_cast<Ref*>(this));
                }
            });
}

void GameScene::unLoadSource()
{
    sourceManager(*_pSourceVec, false);
}

void GameScene::addLayers()
{
    auto pCountDownLayer = CountDownLayer::create();
    pCountDownLayer->setName("CoundDown");

    addChild(pCountDownLayer, 100);

    addChild(pTiledMapLayer);

    addChild(pBarriersLayer);

    addChild(pTowersLayer);

    addChild(pMonsterLayer);

    addChild(pBulletsLayer);

    addChild(pOptLayer);

    addChild(pScoreAndControllerLayer);
}

void GameScene::onEnter()
{
    Scene::onEnter();

    addLayers();

    createBarriers();

    pMonsterLayer->addEntity(pCarrot);

    registerGameEvent();

    SoundUtil::getInstance()->playBackgroundSound(StringUtils::format(THEMEBACKGROUNDMUSIC, SceneManager::getInstance()->getCurPageIndex() + 1).c_str());

    schedule(schedule_selector(GameScene::collisionUpDate), 0.2);
}

void GameScene::onExit()
{
    NOTIFY->removeAllObservers(this);
    unLoadSource();
    Scene::onExit();
}

void GameScene::collisionUpDate(float dt)
{
    CollisionManager::collision(BarrierManager::getInstance()->getBarrierVec(), MonsterManager::getInstance()->getMonsterVec(), BulletManager::getInstance()->getBulletVec());
}

void GameScene::createBarriers()
{
    auto barriers = MapUtil::getInstance()->getBarrierPoses();
    CsvUtil* pCsvUtil = CsvUtil::getInstance();
    for (auto& iter : barriers)
    {
        int iLine = pCsvUtil->findValueInWithLine(iter.first, 1, BARRIERCSVFILE);
        Vec2 tPos = iter.second.origin;
        Size tSize = iter.second.size;
        auto pBarrier = BarrierBase::create(iLine);
        pBarrier->setPosition(Vec2(tPos.x + tSize.width / 2, tPos.y + tSize.height / 2));
    }
}

void GameScene::clearAllManager()
{
    BarrierManager::getInstance()->clearManager();
    MonsterManager::getInstance()->clearManager();
    TowerManager::getInstance()->clearManager();
    BulletManager::getInstance()->clearManager();
}

void GameScene::registerGameEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(GameScene::showGameEndLayer), "gameEnd", nullptr);
    NOTIFY->addObserver(this, callfuncO_selector(GameScene::startBuildMonster), "startBuildMonster", nullptr);
}

void GameScene::showGameEndLayer(Ref* pDate)
{
    auto tGameEndType = *(reinterpret_cast<GameEndType*>(pDate));
    auto pGameEndLayer = GameEndLayer::create(tGameEndType);
    pGameEndLayer->setName("GameEnd");
    addChild(pGameEndLayer, 1);
}

void GameScene::startBuildMonster(Ref* pData)
{
    addChild(MonsterBuilder::create());
    auto pScheduler = Director::getInstance()->getScheduler();
    pScheduler->setTimeScale(1.6);
}

Carrot* GameScene::getCarrot() {
    return pCarrot;
}

void GameScene::clickChooseItem()
{
    dynamic_cast<ScoreAndControllerLayer*>(pScoreAndControllerLayer)->clickChooseItem();
}

