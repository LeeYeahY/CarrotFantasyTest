#include"EntityLayerBase.h"
#include "Entity.h"

void EntityLayerBase::AddEntity(Entity* NewEntity)
{
    addChild(NewEntity);//����µ�ʵ��Ϊ�½��
}