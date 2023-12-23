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
		CC_BREAK_IF(!Layer::Init());//��ͼ����г�ʼ��

		Ret = true;
	} while (0);

	BottomSprite = Sprite::createWithSpriteFrameName("bottom.png");//��ͼƬ��������
	BottomSprite->setPosition(480, 50);//����λ��
	addChild(BottomSprite);//������ӵ����ӽ����

	auto Frame = SpriteFrame::create("Themes/Items/numwhite-hd.png", Rect(20, 0, 20, 40));//��������֡����ͼƬ�н�ȡһ��������
	auto Num = Sprite::createWithSpriteFrame(Frame);//ʹ�þ���֡��������
	auto EighthNum = NumSprite::CreateNum("18", "Themes/Items/numwhite-hd.png");//�������־��飬��������ӵ�
	Num->setPosition(480, 55);//���þ����λ��
	EighthNum->setPosition(498, 55);//�������־����λ��

	//�����������Ϊ���ӽ��
	addChild(EighthNum);
	addChild(Num);

	//�����ͳ�ʼ��һ��ҳ����ͼ
	PPageView();
	return Ret;
}
void TowerHelpLayer::PPageView()
{

	MyPageView = PageView::create();//����ͼ��
	MyPageView->setContentSize(Size(960.0f, 640.0f));//����ͼ��Ĵ�С
	Layout* MyLayout = nullptr;//��������ָ��

	for (int i = 1; i < 19; ++i)
	{
		MyLayout = Layout::create();//���ȴ�������ָ��

		//����������������һ���������
		auto LayoutSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d.png", i));
		//������ʾ�������Ƶľ������
		auto LayoutSpriteName = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d_CN.png", i));

		//����λ��
		LayoutSprite->setPosition(Vec2(480, 310));
		LayoutSpriteName->setPosition(Vec2(480, 310));

		//��ӽ��
		MyLayout->addChild(LayoutSprite);
		MyLayout->addChild(LayoutSpriteName);
		MyPageView->insertPage(MyLayout, i);//�����ֶ������ҳ����ͼ

	}
	MyPageView->setPassFocusToChild(true); //����ҳ����ͼ���ݽ�����ӽڵ�
	MyPageView->scrollToPage(CurLevelIndex);//��������Ӧ�ؿ���ҳ��
	MyPageView->addEventListener([=](Ref* Sender, PageView::EventType event)//Lambdas���ʽ��Ϊҳ����ͼ��Ӽ���������ҳ���л�ʱִ��
		{
			//��ҳ�淢���л�ʱ
			if (PageView::EventType::TURNING == event)
			{
				//��ȡҳ������
				CurLevelIndex = MyPageView->getCurPageIndex();
				std::string Num = StringUtils::format("%d", CurLevelIndex + 1);//���ؿ�����+1��ת��Ϊ�ַ���
				BottomSprite->removeAllChildren();//�Ƴ��ײ�����������ӽ��
				auto LayoutNum = NumSprite::createNum(Num, "Themes/Items/numwhite-hd.png");//�������־���
				if (CurLevelIndex + 1 >= 10)//���ݹؿ�������ֵ����λ��
					LayoutNum->setPosition(447, 40);
				else
					LayoutNum->setPosition(463, 40);

				BottomSprite->addChild(LayoutNum, 80);//��ӽ��
			}
		});

	addChild(MyPageView);//���ҳ����ͼ����ǰͼ��

}