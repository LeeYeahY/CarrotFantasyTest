#include"EntityLayerBase.h"
#include "Entity.h"

void EntityLayerBase::AddEntity(Entity* NewEntity)
{
    addChild(NewEntity);//添加新的实体为新结点
}