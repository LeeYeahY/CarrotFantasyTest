#include"BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager* BarrierManager::Instance;

BarrierManager::BarrierManager()
{
}

BarrierManager::~BarrierManager()
{
    CC_SAFE_DELETE(MyBarrierVec);
}


bool BarrierManager::Initiate()
{

    MyBarrierVec = new Vector<BarrierBase*>();//���������ϰ����vector
    RecordBarrierDeadEvent();//������¼�ϰ��������Ĺ۲���
    return true;
}

BarrierVec& BarrierManager::GetBarrierVec()
{
    return *MyBarrierVec;//��ȡ�洢�ϰ����vector�Ľӿں���
}

void BarrierManager::AddBarrier(BarrierBase* MyBarrier)//����ϰ���
{
    if (MyBarrierVec) //������ϰ����ָ�벻Ϊ��
        MyBarrierVec->pushBack(MyBarrier);//������ӵ�vector��
    AddBarrierToLayer(MyBarrier);//��������ϰ��ﵽͼ��ĺ���
}

void BarrierManager::SetFuncAddBarrierToLayer(const std::function<void(Entity*)>& FuncAddBarrierToLayer)
{
    AddBarrierToLayer = FuncAddBarrierToLayer;//��������ϰ��ﵽͼ��ĺ���
}

void BarrierManager::RecordBarrierDeadEvent()//������¼�ϰ��������Ĺ۲���
{
    NOTIFY->addObserver(this, callfuncO_selector(BarrierManager::RemoveBarrierFromManager), "BarrierDead", nullptr);
}

void BarrierManager::RemoveBarrierFromManager(Ref* Barrier)
{
    if (!(MyBarrierVec && MyBarrierVec->size())) //�����ǰ�ϰ���Ϊ��
        return;//ֱ�ӷ���
    MyBarrierVec->eraseObject(static_cast<BarrierBase*>(Barrier));//���򽫶�Ӧ���ϰ����vector���Ƴ�

    if (!MyBarrierVec->size())//���vector�л����ϰ���
    {
        auto ThemeIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
        auto LevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
        auto LevelData = std::make_tuple(1, 1, ThemeIndex, LevelIndex);
        NOTIFY->postNotification(LEVELDATACHANGE, static_cast<Ref*>(&LevelData));
    }
}

void BarrierManager::ClearManager()
{
    MyBarrierVec->clear();//��մ洢��������Vector
}

void BarrierManager::ClearBeAtkLockState()
{
    for (auto& IterBarrier : *MyBarrierVec)
        IterBarrier->setAtkTarget(false);//����vector�������������ϰ���ı�����״̬����Ϊ��
}

