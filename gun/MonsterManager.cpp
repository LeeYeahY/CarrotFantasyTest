#include "MonsterManager.h"
#include "MonsterBase.h"
#include "GameManager.h"

MonsterManager* MonsterManager::gInstance;

MonsterManager::MonsterManager()
{
}

void MonsterManager::ClearAtkLockState()
{
    for (auto& IterMonster : *pMonsterVec)
    {
        IterMonster->SetAtkTarget(false);
    }
}

MonsterManager::~MonsterManager()
{
    CC_SAFE_DELETE(pMonsterVec);
}

bool MonsterManager::Init()
{
    bool Ret = false;
    do
    {
        pMonsterVec = new Vector<MonsterBase*>;
        RegisterDeadEvent();// ע����������¼�
        Ret = true;
    } while (0);

    return Ret;
}

Vector<MonsterBase*>& MonsterManager::GetMonsterVec()
{
    return *pMonsterVec;
}

void MonsterManager::AddMonster(MonsterBase* pMonster)
{
    if (pMonsterVec) pMonsterVec->pushBack(pMonster);
    funcAddMonsterToLayer(pMonster);
}

void MonsterManager::SetFuncAddMonsterToLayer(const std::function<void(Entity*)>& FuncAddMonsterToLayer)
{
    funcAddMonsterToLayer = FuncAddMonsterToLayer;
}

void MonsterManager::RegisterDeadEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::RemoveMonsterFromManager), "MonsterDead", nullptr);// ע����������¼��ļ�����
    NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::OpenCheckGameEnd), "openCheckGameEnd", nullptr);// ע��򿪼����Ϸ�����¼��ļ�����
}

void MonsterManager::RemoveMonsterFromManager(Ref* Monster)
{
    if (!(pMonsterVec && pMonsterVec->size())) return;// �����������Ƿ�Ϊ��
    pMonsterVec->eraseObject(reinterpret_cast<MonsterBase*>(Monster));// �ӹ����������Ƴ�ָ���Ĺ������

    if (IsOpenCheckGameEnd)
    {
        if (!pMonsterVec->size())
        {
            auto tEnGameWin = en_GameWin;// ������Ϸʤ��״̬
            if (GameManager::getInstance()->getMyCarrotHp() >= 1)// ������ܲ�����ֵ���ڵ���1��������Ϸ�����¼�
                NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tEnGameWin));
            IsOpenCheckGameEnd = false;
        }
    }
}

void MonsterManager::ClearManager()
{
    pMonsterVec->clear();
}

void MonsterManager::OpenCheckGameEnd(cocos2d::Ref* pSender)
{
    IsOpenCheckGameEnd = true;
}