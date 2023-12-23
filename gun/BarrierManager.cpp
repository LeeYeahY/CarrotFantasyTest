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

    MyBarrierVec = new Vector<BarrierBase*>();//创建保存障碍物的vector
    RecordBarrierDeadEvent();//创建记录障碍物死亡的观察者
    return true;
}

BarrierVec& BarrierManager::GetBarrierVec()
{
    return *MyBarrierVec;//获取存储障碍物的vector的接口函数
}

void BarrierManager::AddBarrier(BarrierBase* MyBarrier)//添加障碍物
{
    if (MyBarrierVec) //如果该障碍物的指针不为空
        MyBarrierVec->pushBack(MyBarrier);//将其添加到vector中
    AddBarrierToLayer(MyBarrier);//调用添加障碍物到图层的函数
}

void BarrierManager::SetFuncAddBarrierToLayer(const std::function<void(Entity*)>& FuncAddBarrierToLayer)
{
    AddBarrierToLayer = FuncAddBarrierToLayer;//设置添加障碍物到图层的函数
}

void BarrierManager::RecordBarrierDeadEvent()//创建记录障碍物死亡的观察者
{
    NOTIFY->addObserver(this, callfuncO_selector(BarrierManager::RemoveBarrierFromManager), "BarrierDead", nullptr);
}

void BarrierManager::RemoveBarrierFromManager(Ref* Barrier)
{
    if (!(MyBarrierVec && MyBarrierVec->size())) //如果当前障碍物为空
        return;//直接返回
    MyBarrierVec->eraseObject(static_cast<BarrierBase*>(Barrier));//否则将对应的障碍物从vector中移除

    if (!MyBarrierVec->size())//如果vector中还有障碍物
    {
        auto ThemeIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
        auto LevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
        auto LevelData = std::make_tuple(1, 1, ThemeIndex, LevelIndex);
        NOTIFY->postNotification(LEVELDATACHANGE, static_cast<Ref*>(&LevelData));
    }
}

void BarrierManager::ClearManager()
{
    MyBarrierVec->clear();//清空存储防御塔的Vector
}

void BarrierManager::ClearBeAtkLockState()
{
    for (auto& IterBarrier : *MyBarrierVec)
        IterBarrier->setAtkTarget(false);//遍历vector，将其中所有障碍物的被攻击状态都设为否
}

