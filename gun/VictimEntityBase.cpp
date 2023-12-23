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
    if (this->getIsDead())return;//死亡 条件检查
    myState |= HurtValue._enAtkState;//更新状态
    myBulletStateType = HurtValue.ButtltType;//更新状态子弹类型
    switch (HurtValue._enAtkState)//更新受伤持续状态
    {
    case en_Slow: mySlowTime = HurtValue.Duration; break;//减速
    case en_Stop:myStopTime = HurtValue.Duration; break;//停止
    case en_Poison: myPoisonTime = HurtValue.Duration; break;//中毒
    default:
        break;
    }
    auto nowHp = getMyHp() - HurtValue.Atk;//更新血量
    if (nowHp > 0)
    {
        unschedule(schedule_selector(VictimEntityBase::CloseHp));//受伤后设置血条可见
        if (!HpExsist)
        {
            HpVisible(!HpExsist);
            HpExsist = true;
        }
        pHp->setVisible(true);
        schedule(schedule_selector(VictimEntityBase::CloseHp), HpCloseTime);
        setMyHp(nowHp);//更新血条显示血量
        pHp->SetHp(getMyHp());
        HurtMove();
    }
    else if (nowHp <= 0)//死亡
    {
        DeadMove();
    }
}

void VictimEntityBase::DeadMove(const std::string& DeadImageFile)
{
    auto _value = std::make_tuple(getPosition(), Value);//
    NOTIFY->postNotification("monsterDeadMoney", reinterpret_cast<Ref*>(&_value));
    if (pHp) pHp->removeFromParent();//移除血条
    if (pAtkTarget) pAtkTarget->removeFromParent();//移除结点
    Entity::DeadMove();//
}

void VictimEntityBase::CreateHpSprite()
{
    pHp = Hp::Create(this);//创建血条对象
    pHp->retain();//保留对象
    auto Pos = getPosition();//获取位置和尺寸
    auto SpriteSize = getContentSize();
    auto HpSize = pHp->getContentSize();
    pHp->setPosition(Vec2(HpSize.width / 2 - 3, SpriteSize.height / 2 - 12));//设置位置
    addChild(pHp);//添加到实体结点
}

void VictimEntityBase::CreateAtkSprite()
{
    CreateTargetAnimate();//创建目标的动画
    pAtkTarget = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("xxxxx"));//使用精灵帧创建锁定攻击目标对象：
    CC_SAFE_RETAIN(pAtkTarget);//保留攻击目标的引用
    pAtkTarget->setPosition(Vec2(0, Position.y + Size.height / 2 + 12)); //设置锁定攻击目标的位置
    addChild(pAtkTarget, 2); //添加实体节点
}

void VictimEntityBase::CreateTargetAnimate()
{
    auto pAnimation = Animation::create();//创建动画对象 
    auto pSpriteFrameCache = SpriteFrameCache::getInstance(); //获取精灵帧缓存对象和添加精灵帧到动画
    for (int i = 1; i <= 3; ++i)
        pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("xxxxx", i)));//
    pAnimation->setLoops(-1); //设置动画循环和帧间隔
    pAnimation->setDelayPerUnit(0.1f);
    pTargetAnimate = Animate::create(pAnimation); //创建动画播放对象
    pTargetAnimate->retain(); //保留动画播放对象的引用
}

void VictimEntityBase::SetAtkTarget(const bool& _IsAtkTarget)
{
    IsAtkTarget = _IsAtkTarget;
    if (IsAtkTarget)//是攻击目标
    {
        if (!pAtkTarget)CreateAtkSprite(); //如果锁定攻击目标精灵不存在，则调用 CreateLockAtkSprite 函数创建它
        pAtkTarget->runAction(pTargetAnimate); //运行锁定攻击目标动画
        pAtkTarget->setVisible(IsAtkTarget);//设置锁定攻击目标精灵可见
        SoundUtil::getInstance()->PlayEffect(SELECTVICTIMENTITYBASE);//音效
    }
    else//不是攻击目标
    {
        if (!pAtkTarget) return;//如果锁定攻击目标精灵不存在，则直接返回
        pAtkTarget->stopAllActions(); //停止锁定攻击目标精灵上的所有动作
        pAtkTarget->setVisible(IsAtkTarget);//设置锁定攻击目标精灵不可见
    }
}

void VictimEntityBase::CloseHp(float dt)
{
    pHp->setVisible(false);//关闭显示
}

void VictimEntityBase::HpVisible(const bool& IsHpVisible)
{
    if //显示
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

