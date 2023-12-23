#include "BarrierBase.h"
#include "BarrierManager.h"
#include "PublicDefine.h"
#include "MapUtil.h"

bool BarrierBase::Initiate(const int Id)
{
    bool Ret = false;

    do {
        CC_BREAK_IF(!VictimEntityBase::Init(Id, BARRIERCSVFILE));
        BarrierManager::getInstance()->AddBarrier(this);//�����ϰ�����ӵ��ϰ����vector��
        Ret = true;
    } while (0);

    return Ret;

}

BarrierBase* BarrierBase::Create(const int Id) {

    BarrierBase* Barriers = new BarrierBase();

    if (Barriers &&Barriers->Initiate(Id))//��������ɹ��ҳ�ʼ���ɹ�
    {
        Barriers->autorelease();//��Barrier���뵽�Զ��ͷų���
        return Barriers;//���ش������ϰ����ָ��
    }
    CC_SAFE_DELETE(Barriers);//�����ͷŸ�ָ�룬��֤��ΪNULL
    return nullptr;
}

void BarrierBase::DeadMove(const std::string& DeadImageFile)
{
    NOTIFY->postNotification("BarrierDead", this);//����ϰ��ﱻ����������۲��߷�����Ϣ
    MapUtil::getInstance()->RemoveBarrierRect(getPosition());//�ڵ�ͼ���Ƴ����ϰ���
    VictimEntityBase::DeadMove();//���������Ķ���
}

void BarrierBase::BeHurtAction()
{

}