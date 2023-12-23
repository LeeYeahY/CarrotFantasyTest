#include "Hp.h"
#include "VictimEntityBase.h"

Hp::~Hp()
{
    CC_SAFE_RELEASE_NULL(pVictimEntity);
    CC_SAFE_RELEASE_NULL(pHp);
}

Hp* Hp::Create(VictimEntityBase* _VictimEntity)
{
    auto pHp = new Hp(); // ����Ѫ��ʾ��
    if (pHp && pHp->Init(_VictimEntity))//��������ڴ�ɹ��ҳ�ʼ���ɹ�, �Զ��ͷ��ڴ�
        pHp->autorelease(); 
    else CC_SAFE_DELETE(pHp); //����ȫɾ�� HpSlot ����
    return pHp;
}

bool Hp::Init(VictimEntityBase* _VictimEntity)
{
    bool Ret = false;//��ʾ��ʼ���Ƿ�ɹ�

    do
    {
        CC_SAFE_RETAIN(_VictimEntity);//�Դ���� _VictimEntity�������ü������ӣ�Ȼ���丳ֵ��pVictimEntity
        pVictimEntity = _VictimEntity;
        HpMax = pVictimEntity->getMyHp();//��ȡĿ��ʵ����������ֵ

        auto pHpBg = Sprite::createWithSpriteFrameName("MonsterHP01.png");//����Ѫ���������� pHpBg��������ê��Ϊ���е㣬��������ӵ� HpSlot �����С�
        pHpBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        addChild(pHpBg);
        //����Ѫ��,����Ѫ������
        pHp = ProgressTimer::create(Sprite::createWithSpriteFrameName("MonsterHP02.png"));
        pHp->setType(ProgressTimer::Type::BAR);
        pHp->setMidpoint(Vec2::ANCHOR_MIDDLE_RIGHT);
        pHp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        pHp->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
        pHp->setPercentage(0);
        pHp->setPositionX(2);

        addChild(pHp); //��Ѫ����ӵ� Hp �����У�
        Ret = true;
    } while (0);

    return Ret;
}

void Hp::SetHp(const int& rIHp)
{
    pHp->setPercentage(100 - pVictimEntity->getMyHp() * 1.0f / HpMax * 100);
}

const Size& Hp::GetSize()const
{
    return pHp->getContentSize();
}