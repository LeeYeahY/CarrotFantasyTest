#include "VictimEntityBase.h"
#include"TowerManager.h"
#include "SoundUtil.h"

VictimEntityBase::~VictimEntityBase()
{
    CC_SAFE_RELEASE_NULL(pAtkTarget);
    CC_SAFE_RELEASE_NULL(pHp);
    CC_SAFE_RELEASE_NULL(pTargetAnimate);
}

bool VictimEntityBase::Init(const int& _Id, const std::string& SCsvFileName)
{
    bool Ret = false;
    do
    {
        CC_BREAK_IF(!Entity::Initiate(_Id, SCsvFileName));
        myHp = CsvUtil::GetInstance()->GetInt(Id, en_Hp, SCsvFileName);
        myState = en_Normal;
        mySlowTime = 0;
        myStopTime = 0;
        myPoisonTime = 0;
        Position = getPosition();
        Size = getContentSize();
        this->schedule(schedule_selector(VictimEntityBase::CheckAtkTarget));
        Ret = true;
    } while (0);

    return Ret;
}

void VictimEntityBase::Hurt(const AtkProperty HurtValue)
{
    if (this->getIsDead())return;//���� �������
    myState |= HurtValue._enAtkState;//����״̬
    myBulletStateType = HurtValue.ButtltType;//����״̬�ӵ�����
    switch (HurtValue._enAtkState)//�������˳���״̬
    {
    case en_Slow: mySlowTime = HurtValue.Duration; break;//����
    case en_Stop:myStopTime = HurtValue.Duration; break;//ֹͣ
    case en_Poison: myPoisonTime = HurtValue.Duration; break;//�ж�
    default:
        break;
    }
    auto nowHp = getMyHp() - HurtValue.Atk;//����Ѫ��
    if (nowHp > 0)
    {
        unschedule(schedule_selector(VictimEntityBase::CloseHp));//���˺�����Ѫ���ɼ�
        if (!HpExsist)
        {
            HpVisible(!HpExsist);
            HpExsist = true;
        }
        pHp->setVisible(true);
        schedule(schedule_selector(VictimEntityBase::CloseHp), HpCloseTime);
        setMyHp(nowHp);//����Ѫ����ʾѪ��
        pHp->SetHp(getMyHp());
        HurtMove();
    }
    else if (nowHp <= 0)//����
    {
        DeadMove();
    }
}

void VictimEntityBase::DeadMove(const std::string& DeadImageFile)
{
    auto _value = std::make_tuple(getPosition(), Value);//
    NOTIFY->postNotification("monsterDeadMoney", reinterpret_cast<Ref*>(&_value));
    if (pHp) pHp->removeFromParent();//�Ƴ�Ѫ��
    if (pAtkTarget) pAtkTarget->removeFromParent();//�Ƴ����
    Entity::DeadMove();//
}

void VictimEntityBase::CreateHpSprite()
{
    pHp = Hp::Create(this);//����Ѫ������
    pHp->retain();//��������
    auto Pos = getPosition();//��ȡλ�úͳߴ�
    auto SpriteSize = getContentSize();
    auto HpSize = pHp->getContentSize();
    pHp->setPosition(Vec2(HpSize.width / 2 - 3, SpriteSize.height / 2 - 12));//����λ��
    addChild(pHp);//��ӵ�ʵ����
}

void VictimEntityBase::CreateAtkSprite()
{
    CreateTargetAnimate();//����Ŀ��Ķ���
    pAtkTarget = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("xxxxx"));//ʹ�þ���֡������������Ŀ�����
    CC_SAFE_RETAIN(pAtkTarget);//��������Ŀ�������
    pAtkTarget->setPosition(Vec2(0, Position.y + Size.height / 2 + 12)); //������������Ŀ���λ��
    addChild(pAtkTarget, 2); //���ʵ��ڵ�
}

void VictimEntityBase::CreateTargetAnimate()
{
    auto pAnimation = Animation::create();//������������ 
    auto pSpriteFrameCache = SpriteFrameCache::getInstance(); //��ȡ����֡����������Ӿ���֡������
    for (int i = 1; i <= 3; ++i)
        pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("xxxxx", i)));//
    pAnimation->setLoops(-1); //���ö���ѭ����֡���
    pAnimation->setDelayPerUnit(0.1f);
    pTargetAnimate = Animate::create(pAnimation); //�����������Ŷ���
    pTargetAnimate->retain(); //�����������Ŷ��������
}

void VictimEntityBase::SetAtkTarget(const bool& _IsAtkTarget)
{
    IsAtkTarget = _IsAtkTarget;
    if (IsAtkTarget)//�ǹ���Ŀ��
    {
        if (!pAtkTarget)CreateAtkSprite(); //�����������Ŀ�꾫�鲻���ڣ������ CreateLockAtkSprite ����������
        pAtkTarget->runAction(pTargetAnimate); //������������Ŀ�궯��
        pAtkTarget->setVisible(IsAtkTarget);//������������Ŀ�꾫��ɼ�
        SoundUtil::getInstance()->PlayEffect(SELECTVICTIMENTITYBASE);//��Ч
    }
    else//���ǹ���Ŀ��
    {
        if (!pAtkTarget) return;//�����������Ŀ�꾫�鲻���ڣ���ֱ�ӷ���
        pAtkTarget->stopAllActions(); //ֹͣ��������Ŀ�꾫���ϵ����ж���
        pAtkTarget->setVisible(IsAtkTarget);//������������Ŀ�꾫�鲻�ɼ�
    }
}

void VictimEntityBase::CloseHp(float dt)
{
    pHp->setVisible(false);//�ر���ʾ
}

void VictimEntityBase::HpVisible(const bool& IsHpVisible)
{
    if //��ʾ
        (IsHpVisible) CreateHpSprite();
    else 
        pHp->setVisible(IsHpVisible);
}

void VictimEntityBase::CheckAtkTarget(float dt)
{
    auto TowerVec = TowerManager::getInstance()->GetTowerVec();
    if (IsAtkTarget) {
        for (auto& towerItem : TowerVec)
        {
            if (towerItem->IsInAttackRange(this->getPosition())) {
                towerItem->SetTarget(this);
                towerItem->setHaveTarget(true);
            }
        }
    }
}

