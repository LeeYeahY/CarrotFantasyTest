#include "levelSelectLayer.h"
#include "ui/CocosGUI.h"
#include "sceneManager.h"
#include "soundUtil.h"
#include "localDataUtil.h"

using namespace ui;
LevelSelectLayer::~LevelSelectLayer()
{
}

bool LevelSelectLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        iPageIndex = SceneManager::getInstance()->getCurPageIndex();

        loadData();
        loadSource();
        bRet = true;
    } while (0);
    return bRet;
}

void LevelSelectLayer::loadSource()
{
    auto pBg = Sprite::createWithSpriteFrameName("ss_bg.png");
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    auto pTitle = Label::createWithSystemFont("Ñ¡Ôñ¹Ø¿¨", "Arial", 30);
    pTitle->setPosition(Vec2(480, 615));
    addChild(pTitle);

    auto pCloud = Sprite::createWithSpriteFrameName("ss_cloud.png");
    pCloud->setPosition(VisibleRect::center());
    addChild(pCloud);

    loadLevel();
    loadMenuItem();
}

void LevelSelectLayer::loadData()
{
    dataValueMap = LocalDataUtil::getInstance()->getLevelData();
}

void LevelSelectLayer::loadMenuItem()
{
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
        {
            auto enPageSelectScene = std::make_tuple(en_PageSelectScene, iPageIndex);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enPageSelectScene));
        });
    pBtnBack->setPosition(Vec2(30, 615));

    auto pBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref* pSender)
        {
            auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnHelpScene));
        });
    pBtnHelp->setPosition(Vec2(930, 615));

    pStartBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_play_normal_CN.png"), Sprite::createWithSpriteFrameName("ss_play_pressed_CN.png"), [&](Ref* pSender)
        {
            this->changeToGameScene();
        });
    pStartBtn->setPosition(Vec2(480, 75));
    addChild(Menu::create(pBtnBack, pBtnHelp, pStartBtn, nullptr));

    pLockSprite = Sprite::createWithSpriteFrameName("ss_locked_CN.png");
    pLockSprite->setPosition(Vec2(480, 75));
    addChild(pLockSprite);
    pLockSprite->setVisible(!pLockSprite->isVisible());

}

std::tuple<int, bool> LevelSelectLayer::checkLevelIsLockAndBarrierIsClean(const int& rILevelIndex)
{
    auto tKey = StringUtils::format(LEVELKEY, iPageIndex + 1, rILevelIndex);
    auto value = dataValueMap[tKey].asInt();

    auto tCarrotType = value / 10;
    auto tBarrierClean = value % 10;
    return std::make_tuple(tCarrotType, tBarrierClean);
}

void LevelSelectLayer::changeToGameScene()
{
    if (!std::get<0>(checkLevelIsLockAndBarrierIsClean(iCurLevelIndex + 1))) return;
    auto enGameScene = std::make_tuple(en_GameScene, iCurLevelIndex);
    NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameScene));
}

void LevelSelectLayer::loadLevel()
{
    auto pageView = PageView::create();
    pageView->setContentSize(Size(960.0f, 640.0f));
    Size backgroundSize = this->getContentSize();
    Layout* pLayout = nullptr;

    std::string tMapImageName = "";
    for (int i = 0; i < THEME_LEVELCOUNT_ARRAY[iPageIndex]; ++i)
    {
        tMapImageName = MAPNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX;
        pLayout = Layout::create();

        auto tTotalMonsterBatchCount = CsvUtil::getInstance()->getInt(1 + SceneManager::getInstance()->getCurPageIndex() * 12 + i, 3, LEVELCSVFILE);
        auto pTotalMonsterBatch = Sprite::createWithSpriteFrameName(StringUtils::format("ss_waves_%d.png", tTotalMonsterBatchCount));
        pTotalMonsterBatch->setPosition(Vec2(500, 535));
        pLayout->addChild(pTotalMonsterBatch);

        auto pButton = Button::create(tMapImageName, tMapImageName, tMapImageName, TextureResType::PLIST);
        pButton->setPosition(Vec2(backgroundSize.width / 2, backgroundSize.height / 2 + 35));
        pButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType event)
            {
                if (event == Widget::TouchEventType::ENDED)
                {
                    this->changeToGameScene();
                }
            });

        auto pTowerFlag = Sprite::createWithSpriteFrameName(TOWERNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX);
        pTowerFlag->setPosition(Vec2(backgroundSize.width / 2, backgroundSize.height / 2 - pButton->getContentSize().height / 2 - pTowerFlag->getContentSize().height / 2 + 35));
        pLayout->addChild(pButton);
        pLayout->addChild(pTowerFlag);

        auto tLevelData = this->checkLevelIsLockAndBarrierIsClean(i + 1);

        auto tCarrotType = std::get<0>(tLevelData);
        auto tBarrierCleanFlag = std::get<1>(tLevelData);

        if (!tCarrotType)
        {
            auto pLock = Sprite::createWithSpriteFrameName("ss_locked_icon.png");
            pLock->setPosition(Vec2(620, 255));
            pLayout->addChild(pLock);
        }
        else
        {
            std::string sCarrotType = "";
            if (tCarrotType == 4)
                sCarrotType = GOLDCARROT;
            if (tCarrotType == 3)
                sCarrotType = SILVERCARROT;
            if (tCarrotType == 2)
                sCarrotType = NORMALCARROT;

            if (tCarrotType > 1)
            {
                auto pCarrot = Sprite::createWithSpriteFrameName(sCarrotType);
                pLayout->addChild(pCarrot);
                pCarrot->setPosition(620, 255);
            }

            if (tBarrierCleanFlag)
            {
                auto pBarrierClean = Sprite::createWithSpriteFrameName(BARRIERCLEAN);
                pLayout->addChild(pBarrierClean);
                pBarrierClean->setPosition(500, 255);
            }

        }
        pageView->insertPage(pLayout, i);

    }
    pageView->setPassFocusToChild(true);
    pageView->scrollToPage(iCurLevelIndex);
    pageView->addEventListener([=](Ref* pSender, PageView::EventType event)
        {
            if (PageView::EventType::TURNING == event)
            {
                iCurLevelIndex = pageView->getCurPageIndex();
                auto tLockFlag = std::get<0>(this->checkLevelIsLockAndBarrierIsClean(iCurLevelIndex + 1));
                pStartBtn->setEnabled(tLockFlag);
                pLockSprite->setVisible(!tLockFlag);

            }
        });
    addChild(pageView);

}


