#include "BarrierFactory.h"
#include "BarrierBase.h"
BarrierBase* BarrierFactory::CreateBarrier(const BarrierType& MyBarrierType)
{
    //���ݴ�����ϰ������ͳ�ʼ���ϰ����ָ��
    BarrierBase* Barrier = nullptr;

    switch (MyBarrierType) {
    case BALLON:
        break;
    case CLOUD:
        break;
    case STONE:
        break;
    case TREE:
        break;
    default:
        break;
    }
    return Barrier;
}