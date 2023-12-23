#include "MonsterBase.h"
#include "MonsterManager.h"
#include "MoveControllerBase.h"
#include "SoundUtil.h"

bool MonsterBase::Init(const int& IId)
{
    bool Ret = false;

    do
    {
        CC_BREAK_IF(!VictimEntityBase::Init(IId, MONSTERCSVFILE));// ���ø���ĳ�ʼ������
        CC_BREAK_IF(!DynamicPropertyInterFace::Init(IId, MONSTERCSVFILE));// ���ýӿ���ĳ�ʼ������
        myIsLeft = true;
        CreateAnimation();// ��������
        DoAction(0.15f);// ִ�ж���
        pMoveController = MoveControllerBase::Create(this);// �����ƶ�������
        MonsterManager::getInstance()->addMonster(this);// �����ƶ�������
        Ret = true;
    } while (0);
    return  Ret;
}

MonsterBase* MonsterBase::Create(const int& IId)
{
    auto pMonster = new MonsterBase();
    if (pMonster && pMonster->Init(IId)) {
        pMonster->autorelease();
        return pMonster;
    }
    CC_SAFE_DELETE(pMonster);
    return nullptr;
}

void MonsterBase::HurtMove()
{

}

void MonsterBase::CreateAnimation()
{
    std::vector<std::string> AniamtionFiles;
    for (int i = 1; i <= _IAnimationFrameCount; i++)//
        AniamtionFiles.push_back(_sModelName + StringUtils::format("%d.png", i));
    CreateDynamicEntityAnimation(AniamtionFiles);
}

void MonsterBase::DoAction(const float& Dt)
{
    pAnimation->setDelayPerUnit(Dt);// ���ö������ӳ�ʱ��
    getSprite()->runAction(Animate::create(pAnimation));//����
}

void MonsterBase::DeadMove(const std::string& SDeadImageFile)
{
    MonsterSound();// ���Ź���������Ч
    NOTIFY->postNotification("MonsterDead", this);// ���͹�������֪ͨ
    getSprite()->removeAllChildrenWithCleanup(true);
    pMoveController->stopAllActions();// ֹͣ�ƶ������������ж���
    VictimEntityBase::DeadMove();
}

void MonsterBase::MonsterSound()
{
    int fFigure = rand() % 3 + 1;
    if (Name.find("land") != std::string::npos)
    {
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Land11%d.mp3", fFigure));
    }
    else if (_sName.find("fly") != std::string::npos)
    {
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    else if (_sName.find("fat") != std::string::npos)
    {
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    else
    {
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + "BigBoss.mp3");
    }
}

void MonsterBase::SetMaxSpeed(const int& Speed)
{
    setMySpeed(Speed);
    pMoveController->setMyMonsterSpeed(Speed);
}
