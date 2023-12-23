#include "BarrierBase.h"
#include "BarrierManager.h"
#include "PublicDefine.h"
#include "MapUtil.h"

bool BarrierBase::Initiate(const int Id)
{
    bool Ret = false;

    do {
        CC_BREAK_IF(!VictimEntityBase::Init(Id, BARRIERCSVFILE));
        BarrierManager::getInstance()->AddBarrier(this);//将该障碍物添加到障碍物的vector中
        Ret = true;
    } while (0);

    return Ret;

}

BarrierBase* BarrierBase::Create(const int Id) {

    BarrierBase* Barriers = new BarrierBase();

    if (Barriers &&Barriers->Initiate(Id))//如果创建成功且初始化成功
    {
        Barriers->autorelease();//将Barrier加入到自动释放池中
        return Barriers;//返回创建的障碍物的指针
    }
    CC_SAFE_DELETE(Barriers);//否则释放该指针，保证其为NULL
    return nullptr;
}

void BarrierBase::DeadMove(const std::string& DeadImageFile)
{
    NOTIFY->postNotification("BarrierDead", this);//如果障碍物被打死，则给观察者发送消息
    MapUtil::getInstance()->RemoveBarrierRect(getPosition());//在地图中移除该障碍物
    VictimEntityBase::DeadMove();//进行死亡的动作
}

void BarrierBase::BeHurtAction()
{

}