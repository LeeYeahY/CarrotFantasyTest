#include "helpLayer.h"
#include"numSprite.h"
#include "sceneManager.h"
HelpLayer::~HelpLayer() {
}
bool HelpLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Layer::init());

		PageViewR();

		bRet = true;
	} while (0);

	bottomSprite = Sprite::createWithSpriteFrameName("bottom.png");
	bottomSprite->setPosition(480, 50);
	addChild(bottomSprite);

	auto frame = SpriteFrame::create("Themes/Items/numwhite-hd.png", Rect(20, 0, 20, 40));
	auto _Num = Sprite::createWithSpriteFrame(frame);
	auto fourNum = NumSprite::createNum("4", "Themes/Items/numwhite-hd.png");
	_Num->setPosition(480, 55);
	fourNum->setPosition(498, 55);

	addChild(fourNum);
	addChild(_Num);

	PageViewR();

	return bRet;
}
void HelpLayer::PageViewR()
{

	pPageView = PageView::create();
	pPageView->setContentSize(Size(960.0f, 640.0f));

	Layout* pLayout = nullptr;

	for (int i = 1; i < 5; ++i)
	{
		pLayout = Layout::create();

		auto pLayoutSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tips_%d.png", i));
		auto tipsText = Sprite::createWithSpriteFrameName(StringUtils::format("tips_text_%d_CN.png", i));
		std::string num = StringUtils::format("%d", i);

		tipsText->setPosition(480, 160);
		pLayoutSprite->setPosition(Vec2(480, 370));

		pLayout->addChild(tipsText);
		pLayout->addChild(pLayoutSprite);
		pPageView->insertPage(pLayout, i);


	}
	addChild(pPageView);
	pPageView->setPassFocusToChild(true);
	pPageView->scrollToPage(iCurLevelIndex);
	pPageView->addEventListener([=](Ref* pSender, PageView::EventType event)
		{
			if (PageView::EventType::TURNING == event)
			{
				iCurLevelIndex = pPageView->getCurPageIndex();
				std::string num = StringUtils::format("%d", iCurLevelIndex + 1);
				bottomSprite->removeAllChildren();
				auto layoutNum = NumSprite::createNum(num, "Themes/Items/numwhite-hd.png");
				layoutNum->setPosition(465, 40);
				bottomSprite->addChild(layoutNum, 80);

			}
		});
}
