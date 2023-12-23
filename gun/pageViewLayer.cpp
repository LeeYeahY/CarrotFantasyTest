#include "pageViewLayer.h"
#include "sceneManager.h"
#include "ui/UIButton.h"
#include "soundUtil.h"
#include "publicSourceDefine.h"

PageViewLayer::~PageViewLayer()
{
    CC_SAFE_RELEASE_NULL(pPageView);
    CC_SAFE_DELETE(pPageFlagVec);
}

bool PageViewLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        iPageIndex = SceneManager::getInstance()->getCurPageIndex();
        pPageFlagVec = new Vector<MenuItemSprite*>;

        loadBg();
        createThemePageView();
        createThemeFlags();

        bRet = true;
    } while (0);
    return bRet;
}

void PageViewLayer::pageTurn(const bool& rBLeft)
{
    if (rBLeft)
    {
        if (pPageView->getCurPageIndex() == 0) return;
        pPageView->scrollToPage(pPageView->getCurPageIndex() - 1);
    }
    else
    {
        //if(_pPageView->getCurPageIndex() + 1 == _pPageView->getPageCount()) return;
        pPageView->scrollToPage(pPageView->getCurPageIndex() + 1);
    }
}

void PageViewLayer::setPageFlag(const int& rIIndex)
{
    int tIndex = -1;
    for (auto& flagIter : *pPageFlagVec)
    {
        if (rIIndex == ++tIndex)
        {
            flagIter->selected();
            continue;
        }
        flagIter->unselected();
    }
}


void PageViewLayer::loadBg()
{
    auto pBg = Sprite::createWithSpriteFrameName(BG);
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    auto pTitle = Label::createWithSystemFont("Ñ¡Ôñ¹Ø¿¨", "Arial", 30);
    pTitle->setPosition(Vec2(480, 615));
    addChild(pTitle);
}

void PageViewLayer::createThemeFlags()
{
    auto pPageFlagMenu = Menu::create();
    auto tFlagCount = 5;//_pPageView->getPageCount();
    for (int i = 0; i < tFlagCount; ++i)
    {
        auto pPageFlagItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pos_normal.png"), Sprite::createWithSpriteFrameName("theme_pos_active.png"));
        pPageFlagItem->setPosition(Vec2(430 + 20 * i, 30));
        pPageFlagVec->pushBack(pPageFlagItem);
        pPageFlagMenu->addChild(pPageFlagItem);
    }
    pPageFlagVec->at(iPageIndex)->selected();
    addChild(pPageFlagMenu);
}

void PageViewLayer::createThemePageView()
{
    pPageView = PageView::create();
    pPageView->retain();
    pPageView->setContentSize(Size(960.0f, 640.0f));

    Size tBackgroundSize = this->getContentSize();
    Layout* pLayout = nullptr;
    int i = -1;
    for (auto& iterThemeName : PAGESOURCE)
    {
        pLayout = Layout::create();
        auto pButton = Button::create(iterThemeName, iterThemeName, iterThemeName, cocos2d::ui::Layout::TextureResType::PLIST);
        pButton->setPosition(Vec2(tBackgroundSize.width / 2, tBackgroundSize.height / 2 - 20));
        pButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType event)
            {
                if (event == Widget::TouchEventType::ENDED)
                {
                    int tCurPageIndex = pPageView->getCurPageIndex();
                    auto tEnSceneType = std::make_tuple(en_LevelSelectScene, tCurPageIndex);
                    NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnSceneType));
                }
            });
        pLayout->addChild(pButton);
        auto pThemeFlag = Sprite::createWithSpriteFrameName(StringUtils::format("theme_pack0%d_CN.png", i + 2));
        pThemeFlag->setScale(1.3f);
        pThemeFlag->setPosition(490, 320);
        pLayout->addChild(pThemeFlag);

        auto pThemeMark = Sprite::createWithSpriteFrameName(StringUtils::format("bookmark_10-12.png"));
        pThemeMark->setScale(1.5f);
        pThemeMark->setPosition(Vec2(710, 70));
        pLayout->addChild(pThemeMark);
        pPageView->insertPage(pLayout, ++i);

    }
    pPageView->setPassFocusToChild(true);
    pPageView->scrollToPage(iPageIndex);
    pPageView->addEventListener([&](Ref* pSender, PageView::EventType event)
        {
            if (PageView::EventType::TURNING == event)
            {
                this->setPageFlag(pPageView->getCurPageIndex());
            }
        });
    addChild(pPageView, 14);
}