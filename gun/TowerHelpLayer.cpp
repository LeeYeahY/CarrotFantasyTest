#include "TowerHelpLayer.h"
#include "NumSprite.h"

TowerHelpLayer::~TowerHelpLayer()
{

}

bool TowerHelpLayer::Initiate()
{
	bool Ret = false;

	do
	{
		CC_BREAK_IF(!Layer::Init());//对图层进行初始化

		Ret = true;
	} while (0);

	BottomSprite = Sprite::createWithSpriteFrameName("bottom.png");//用图片创建精灵
	BottomSprite->setPosition(480, 50);//设置位置
	addChild(BottomSprite);//将其添加到孩子结点中

	auto Frame = SpriteFrame::create("Themes/Items/numwhite-hd.png", Rect(20, 0, 20, 40));//创建精灵帧，从图片中截取一部分区域
	auto Num = Sprite::createWithSpriteFrame(Frame);//使用精灵帧创建精灵
	auto EighthNum = NumSprite::CreateNum("18", "Themes/Items/numwhite-hd.png");//创建数字精灵，并将其添加到
	Num->setPosition(480, 55);//设置精灵的位置
	EighthNum->setPosition(498, 55);//设置数字精灵的位置

	//添加两个精灵为孩子结点
	addChild(EighthNum);
	addChild(Num);

	//创建和初始化一个页面视图
	PPageView();
	return Ret;
}
void TowerHelpLayer::PPageView()
{

	MyPageView = PageView::create();//创建图层
	MyPageView->setContentSize(Size(960.0f, 640.0f));//设置图层的大小
	Layout* MyLayout = nullptr;//声明布局指针

	for (int i = 1; i < 19; ++i)
	{
		MyLayout = Layout::create();//首先创建布局指针

		//根据塔的索引创建一个精灵对象
		auto LayoutSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d.png", i));
		//创建显示中文名称的精灵对象
		auto LayoutSpriteName = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d_CN.png", i));

		//设置位置
		LayoutSprite->setPosition(Vec2(480, 310));
		LayoutSpriteName->setPosition(Vec2(480, 310));

		//添加结点
		MyLayout->addChild(LayoutSprite);
		MyLayout->addChild(LayoutSpriteName);
		MyPageView->insertPage(MyLayout, i);//将布局对象插入页面视图

	}
	MyPageView->setPassFocusToChild(true); //允许页面视图传递焦点给子节点
	MyPageView->scrollToPage(CurLevelIndex);//滚动到对应关卡的页面
	MyPageView->addEventListener([=](Ref* Sender, PageView::EventType event)//Lambdas表达式，为页面视图添加监视器，当页面切换时执行
		{
			//当页面发生切换时
			if (PageView::EventType::TURNING == event)
			{
				//获取页面索引
				CurLevelIndex = MyPageView->getCurPageIndex();
				std::string Num = StringUtils::format("%d", CurLevelIndex + 1);//将关卡索引+1并转换为字符串
				BottomSprite->removeAllChildren();//移除底部精灵的所有子结点
				auto LayoutNum = NumSprite::createNum(Num, "Themes/Items/numwhite-hd.png");//创建数字精灵
				if (CurLevelIndex + 1 >= 10)//根据关卡索引的值设置位置
					LayoutNum->setPosition(447, 40);
				else
					LayoutNum->setPosition(463, 40);

				BottomSprite->addChild(LayoutNum, 80);//添加结点
			}
		});

	addChild(MyPageView);//添加页面视图到当前图层

}